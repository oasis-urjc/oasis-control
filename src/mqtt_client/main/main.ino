
#include <Adafruit_SleepyDog.h>

#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <ArduinoJson.h>

#include <Thread.h>
#include <StaticThreadController.h>
#include <ThreadController.h>

#include "sensor.h"
#include "dht.h"
#include "Ph.h"
#include "Photoresistance.h"


//Pins that may be changed
#define DHT_IN 33
#define MOIST_IN 32
#define PH_IN 0
#define PHR_IN 35

//Types that may be changed
#define HUM 1
#define LIGHT 2
#define TEMP 3

//controller
ThreadController controller = ThreadController();

void send_data(double val, int type, int node, int plot);

//DHT
class DHT_Thread: public Thread {

public:
  DHT *dht;
  const int PLOT_NUM = 1; 
  const int HEIGHT = 1; 
  //initialize
  DHT_Thread(int _pin): Thread() {
   dht = new DHT(PLOT_NUM, HEIGHT, _pin);
  }
  //run it periodically
  bool shouldRun(unsigned long time){
    return Thread::shouldRun(time);
  }
 
  void run() {
    Thread::run();
    dht->update_value();
    send_data(dht->get_temp(), TEMP, PLOT_NUM, HEIGHT);
    send_data(dht->get_hum(), HUM, PLOT_NUM, HEIGHT);
  }

  float get_tmp() {
    return dht->get_temp();
  }

  float get_hum() {
    return dht->get_hum();
  }
};

DHT_Thread* dht_Thread = new DHT_Thread(DHT_IN);


//PH
class PH_Thread: public Thread {

public:
  PH *ph;
  const int PLOT_NUM = 1; 
  const int HEIGHT = 1; 
  //initialize
  PH_Thread(int _pin): Thread() {
   ph = new PH(PLOT_NUM, HEIGHT, _pin);
  }
  //run it periodically
  bool shouldRun(unsigned long time){
    return Thread::shouldRun(time);
  }
 
  void run() {
    Thread::run();
    ph->update_value();
    //NOT TYPE DEFINED
    //send_data(phr->get_value(), PH)
  }

  float get_value() {
    return ph->get_value();
  }

};

PH_Thread* ph_Thread = new PH_Thread(PH_IN);


//PHR
class PHR_Thread: public Thread {

public:
  Photoresistance *phr;
  const int PLOT_NUM = 1; 
  const int HEIGHT = 1; 
  //initialize
  PHR_Thread(int _pin): Thread() {
   phr = new Photoresistance(PLOT_NUM, HEIGHT, _pin);
  }
  //run it periodically
  bool shouldRun(unsigned long time){
    return Thread::shouldRun(time);
  }
 
  void run() {
    Thread::run();
    phr->update_value();
    send_data(phr->get_value(), LIGHT, PLOT_NUM, HEIGHT);
  }

  float get_value() {
    return phr->get_value();
  }

};

PHR_Thread* phr_Thread = new PHR_Thread(PH_IN);



//Variables to connect to WiFi
const char* ssid = "Livebox6-6677";
const char* password = "74RZdskS3Ft9";

//Variables to connect to the MQTT server
const char* server_ip = "192.168.1.32";
uint16_t server_port = 1883;

// WiFiFlientfor SSL/TLS support
WiFiClient client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, server_ip, server_port);

Adafruit_MQTT_Publish message = Adafruit_MQTT_Publish(&mqtt, "node1/temp");

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
void send_data(double val, int type, int node, int plot) {
  DynamicJsonDocument doc(1024);

  doc["value"] = val;
  doc["sensor"]  = String(1);
  
  char json[1024];
  serializeJson(doc, json);

  publish(json);
  Serial.println("SEND");
}


void setup() {

  Serial.begin(115200);
  
  dht_Thread->setInterval(2500);
  controller.add(dht_Thread);

  ph_Thread->setInterval(2500*8);
  controller.add(ph_Thread);

  phr_Thread->setInterval(2500);
  controller.add(phr_Thread);
  
  initWiFi();

  Serial.println("COMENZANDO");
}


void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  controller.run();
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