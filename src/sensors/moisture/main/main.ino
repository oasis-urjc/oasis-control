#include "sensor.h"
#include "moisture_sensor.h"

// Const
const int PLOT_NUM = 1;
const int GPIO_IN = 32;
const int HEIGHT = 1; 

int plot_num = 1;
Moisture_sensor moisture1(PLOT_NUM, HEIGHT, GPIO_IN);

void setup()
{
 Serial.begin(9600);
}

void loop()
{

  moisture1.update_value();
  Serial.print( "VALUE : ");
  Serial.println(moisture1.get_value());
  Serial.print( "CONT : ");
  Serial.println(moisture1.get_cont());
  Serial.print( "PLOT : ");
  Serial.println(moisture1.get_plot_ident());

  delay(1000);

}
