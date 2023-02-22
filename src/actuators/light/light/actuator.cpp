#include "actuator.h"
#include "Arduino.h"


Actuator::Actuator(int plot_number, int height,int gpio,bool init_status){

    ident[0] = plot_number;
    ident[1] = height;

    gpio_out = gpio; 
    status = init_status;
    last_switch_time = clock();
}

void Actuator::set_status(bool newstatus){

    // Switch off/on(new real status)
    if(status != newstatus){
        last_switch_time = clock(); // Time refresh
        switch_status(newstatus);
    }

    status = newstatus;
}

double Actuator::get_time(){

    clock_t final_time;

    if(last_switch_time == 0){final_time = 0;}
    else{final_time = clock() - last_switch_time;}

    double time = (double)final_time / CLOCKS_PER_SEC;

    return (time / MINS);
}

void Actuator::switch_status(bool newstatus){

  if(newstatus){digitalWrite(gpio_out, HIGH);}
  else{digitalWrite(gpio_out, LOW);}
    
    }
