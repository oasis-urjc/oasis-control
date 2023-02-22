/**
 * @file Ph.cpp
 * @methods for de Ph(SEN0161) sensor
 * @date 23/12/2021
 */
#include "Arduino.h"
#include "Ph.h"


 void PH::update_value()
 {
   
    for(int i = 0; i < NUM_VALUES; i++)
    {
        values[i] = analogRead(pin_in);
        delay(VALUES_WAIT_TIME);
    }

   float voltage = average(values)*5.0/1024;
   float pHValue = 3.5 * voltage + Offset;
   set_value(pHValue);
   increment_cont();
}



float PH::average(float* arr)
{
    float final_average = 0;
    int count = 0; 

    for (int i = 0; i < NUM_VALUES; i++)
    {   
        // Ignore imposible values(negative) 
        if(arr[i] >= MIN_PH)
        {
            final_average = final_average + arr[i];
            count++; 
        }
    }
    
    return final_average / count; 
}
