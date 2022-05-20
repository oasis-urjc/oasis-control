#include "dht.h"

  // Const 
  const int PLOT_NUM = 1; 
  const int HEIGHT = 1; 
  const int GPIO_IN = 33; 

  int plot_num = 1;
  DHT dht1(PLOT_NUM, HEIGHT, GPIO_IN);

void setup() 
{
   Serial.begin(9600);
}

void loop() 
{ 
  dht1.update_value();
  Serial.print( "TEMP : ");
  Serial.println(dht1.get_temp());
  Serial.print( "HUM : ");
  Serial.println(dht1.get_hum());

  delay(1000);

}
