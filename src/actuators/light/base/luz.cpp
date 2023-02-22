#include "luz.h"


Luz::Luz(int plot_number, int height, bool init_status){

    ident[0] = plot_number;
    ident[1] = height;
    status = init_status;
    last_switch_time = clock();
}

void Luz::set_status(bool newstatus){

    // Switch off/on(new real status)
    if(status != newstatus){
        last_switch_time = clock(); // Time refresh
    }

    status = newstatus;
}

double Luz::get_time(){

    clock_t final_time;

    if(last_switch_time == 0){final_time = 0;}
    else{final_time = clock() - last_switch_time;}

    double time = (double)final_time / CLOCKS_PER_SEC;

    return (time / MINUTOS);
}
