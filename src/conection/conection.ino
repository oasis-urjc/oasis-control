#include <Adafruit_SleepyDog.h>

/***********************************************************************
  Adafruit MQTT Library ESP32 Adafruit IO SSL/TLS example
  Use the latest version of the ESP32 Arduino Core:
    https://github.com/espressif/arduino-esp32
  Works great with Adafruit Huzzah32 Feather and Breakout Board:
    https://www.adafruit.com/product/3405
    https://www.adafruit.com/products/4172
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!
  Written by Tony DiCola for Adafruit Industries.
  Modified by Brent Rubell for Adafruit Industries
  MIT license, all text above must be included in any redistribution
 **********************************************************************/
/*
* Copyright (C) 2022 by Roberto Calvo-Palomino
*
*
*  This programa is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with RTL-Spec.  If not, see <http://www.gnu.org/licenses/>.
*
*   Authors: Roberto Calvo-Palomino <roberto.calvo [at] urjc [dot] es>
*/

// Subject: Sistemas Empotrados y de Tiempo Real
// Universidad Rey Juan Carlos, Spain

#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <ArduinoJson.h>


//Variables to connect to WiFi
const char* ssid = "lo que sea";
const char* password = "la que sea";

//Variables to connect to the MQTT server
const char* server_ip = "0.0.0.0";
uint16_t server_port = 9999;

//Team data
const char* team_name = "Oasis";
const char* team_id = "no creo que usemos esto";

// WiFiFlientfor SSL/TLS support
WiFiClient client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, server_ip, server_port);

Adafruit_MQTT_Publish message = Adafruit_MQTT_Publish(&mqtt, "/SETR/2022/10/");

//connect to WiFi
void initWiFi() {

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("RRSI: ");
  Serial.println(WiFi.RSSI());
}

void publish(char *to_pub) {

  if (! message.publish(to_pub)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }
}


//publishes the action in the MQTT as a JSON
void send_data(double val, int type ) {
  DynamicJsonDocument doc(1024);

  doc["value"] = String(val, 4);
  doc["type"]  = String(type);

  char json[1024];
  serializeJson(doc, json);

  publish(json);
}


void setup() {

  Serial.begin(115200);

  initWiFi();
}


void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  //after connected the sensors start working however they are soupposed to
  //--> sensors();
  //probablemente por clases y sean objetos de clase a los que se acceda por getters.

  //with the sensors info we send the data to the MQTT server
  //--> send_data(sensor.get_value(), sensor.get_type());

}


// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }

  Serial.println("MQTT Connected!");

}
