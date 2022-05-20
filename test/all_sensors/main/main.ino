#include "dht.h"
#include "Humidity_Sensor.h"
#include "Photoresistance.h"

// Const 
const int PLOT_NUM = 1; 
const int GPIO_DHT = 33; 
const int GPIO_HS = 32;
const int GPIO_PR = 35;

dht dht1(PLOT_NUM, GPIO_DHT);
Humidity_Sensor hs1(PLOT_NUM, GPIO_HS);
Photoresistance pr1(PLOT_NUM, GPIO_PR);

void setup() 
{
   Serial.begin(9600);
}

void loop() 
{ 

      dht1.update_value();
      hs1.update_value();
      pr1.update_value();
      Serial.print( "TEMP : ");
      Serial.println(dht1.get_temp());
      Serial.print( "HUM AIRE: ");
      Serial.println(dht1.get_hum());
      Serial.print( "HUM TIERRA: ");
      Serial.println(hs1.get_value());
      Serial.print( "LUZ: ");
      Serial.println(pr1.get_value());

      delay(1000);

}
