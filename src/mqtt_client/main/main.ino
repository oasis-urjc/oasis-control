#include <Adafruit_SleepyDog.h>

#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <ArduinoJson.h>

//Types that may be changed
#define HUM 1
#define LIGHT 2
#define TEMP 3
#define PH 4

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

Adafruit_MQTT_Publish temp = Adafruit_MQTT_Publish(&mqtt, "node1/temp");
Adafruit_MQTT_Publish hum = Adafruit_MQTT_Publish(&mqtt, "node1/hum");
Adafruit_MQTT_Publish ph = Adafruit_MQTT_Publish(&mqtt, "node1/ph");
Adafruit_MQTT_Publish phr = Adafruit_MQTT_Publish(&mqtt, "node1/phr");

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

void publish(char *to_pub, Adafruit_MQTT_Publish* topic) {

  if (! topic->publish(to_pub)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }
}


//publishes the action in the MQTT as a JSON
void send_data(double val, int sensor, Adafruit_MQTT_Publish* topic) {
  DynamicJsonDocument doc(1024);

  doc["value"] = String(val, 4);
  doc["sensor"]  = String(sensor);
  
  char json[1024];
  serializeJson(doc, json);

  Serial.println(String(json));

  publish(json, topic);
  Serial.println("SEND");
}


void setup() {

  Serial.begin(115200);
  
  initWiFi();

  Serial.println("COMENZANDO");
}

double i = -20.0;

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  i++;

  send_data(i, HUM, &hum);
  delay(1000);
  send_data(i, LIGHT, &phr);
  delay(1000);
  send_data(i, TEMP, &temp);
  delay(1000);
  send_data(i, PH, &ph);
  delay(1000);
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
  while ((ret = mqtt.connect()) != 0) 
  { // connect will return 0 for connected
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