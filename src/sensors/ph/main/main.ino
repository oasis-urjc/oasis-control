#include "Sensor.h"
#include "Ph.h"

// Const
const int PLOT_NUM = 1;
const int GPIO_IN = 0;
const int HEIGHT = 1; 

int plot_num = 1;
PH ph(PLOT_NUM, HEIGHT, GPIO_IN);

void setup()
{
 Serial.begin(9600);
}

void loop()
{

  ph.update_value();
  Serial.print( "VALUE : ");
  Serial.println(ph.get_value());
  Serial.print( "CONT : ");
  Serial.println(ph.get_cont());

  delay(200 * 40); // 200ms 40 measurements

}
