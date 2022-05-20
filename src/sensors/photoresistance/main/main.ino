 //* @author's github : madport

#include "Sensor.h"
#include "Photoresistance.h"

  // Const 
  const int PLOT_NUM = 2; 
  const int GPIO_IN = 35; 
  const int HEIGHT = 1; 

  Photoresistance s2_photores(PLOT_NUM, HEIGHT, GPIO_IN);

void setup() 
{
   Serial.begin(9600);
}

void loop() 
{ 

      s2_photores.update_value();
      Serial.println( "VALUE : ");
      Serial.println(s2_photores.get_value());
   //   Serial.println( "CONT : ");
   //   Serial.println(s1_humedity.get_cont());
   //   Serial.println( "PLOT : ");
   //   Serial.println(s1_humedity.get_plot_ident());
      delay(1000);

}
