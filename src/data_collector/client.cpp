// Copyright Takatoshi Kondo 2015
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <iomanip>
#include <map>
#include <mariadb/conncpp.hpp>

#include <mqtt_client_cpp.hpp>

#include <rapidjson/document.h>
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

// Create a new task record
void addTask(std::unique_ptr<sql::Connection> &conn, int sensor, int value) {
    try {
        // Create a new PreparedStatement
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("insert into SensorsMeasurements (value_, sensor) values (?, ?)"));        // Bind values to SQL statement
        stmnt->setInt(1, value);
        stmnt->setInt(2, sensor);
        // Execute query
        stmnt->executeQuery();

        std::cout << "Query successful" << std::endl;
    }
    catch(sql::SQLException& e){
      std::cerr << "Query unsuccessful: " << e.what() << std::endl;
   }
}

void make_query(std::unique_ptr<sql::Connection> &conn, MQTT_NS::buffer contents) 
{
    // 1. Parse a JSON string into DOM.
    const char* json = contents.data();
    std::cout << "Extracting data from: " << json << std::endl;
    rapidjson::Document d;
    d.Parse(json);

    // Get each of the values
    rapidjson::Value& sensorv = d["sensor"];
    rapidjson::Value& valuev = d["value"];

    int sensor = sensorv.GetInt();
    int value = valuev.GetInt();

    addTask(conn, sensor, value);
}

int main(int argc, char** argv) 
{
    // Check for args
    if (argc != 3) {
        std::cout << argv[0] << " host port" << std::endl;
        return -1;
    }

    MQTT_NS::setup_log();

    boost::asio::io_context ioc;
    std::uint16_t pid_sub1;
    std::uint16_t pid_sub2;

    int count = 0;

    // Database connection
    sql::Driver* driver = sql::mariadb::get_driver_instance();

    // Configure Connection
    sql::SQLString url("jdbc:mariadb://localhost:3306/oasis");
    sql::Properties properties({{"user", "admin"}, {"password", "oasis"}});

    // Establish Connection
    std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));

    // Create no TLS client
    auto c = MQTT_NS::make_sync_client(ioc, argv[1], argv[2]);
    using packet_id_t = typename std::remove_reference_t<decltype(*c)>::packet_id_t;

    // Disconect lambda function
    auto disconnect = [&] {
        if (++count == 5) c->disconnect();
    };

    // Setup client
    c->set_client_id("collector1");
    c->set_clean_session(true);

    // Setup handlers
    c->set_connack_handler(
        [&c, &pid_sub1, &pid_sub2]
        (bool sp, MQTT_NS::connect_return_code connack_return_code){
            std::cout << "Connection with the server stablished" << std::endl;
            
            if (connack_return_code == MQTT_NS::connect_return_code::accepted) 
            {
                pid_sub1 = c->subscribe("mqtt_client_cpp/topic1", MQTT_NS::qos::at_most_once);
                pid_sub2 = c->subscribe(
                    std::vector<std::tuple<MQTT_NS::string_view, MQTT_NS::subscribe_options>>
                    {
                        { "node1/temp", MQTT_NS::qos::at_least_once },
                        { "node1/hum", MQTT_NS::qos::exactly_once }
                    }
                );
            }
            return true;
        }
    );
    
    c->set_close_handler(
        []
        (){
            std::cout << "closed." << std::endl;
        }
    );

    c->set_error_handler(
        []
        (MQTT_NS::error_code ec){
            std::cout << "error: " << ec.message() << std::endl;
        }
    );

    c->set_publish_handler(
        [&]
        (MQTT_NS::optional<packet_id_t> packet_id,
         MQTT_NS::publish_options pubopts,
         MQTT_NS::buffer topic_name,
         MQTT_NS::buffer contents){

            make_query(conn, contents);
            return true;
        }
    );

    // Connect
    c->connect();

    ioc.run();
}