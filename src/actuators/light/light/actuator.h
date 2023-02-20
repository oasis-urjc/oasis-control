#ifndef ACTUATOR_H_INCLUDED
#define ACTUATOR_H_INCLUDED

#include <ctime>

class Actuator{

    public:

        //~ Constructors
        Actuator(void);
        Actuator(int plot_number, int height, int gpio,bool init_status = false);

        // Getters
        void get_ident(int identifier[]){identifier[0] = ident[0]; identifier[1] = ident[1];}
        bool get_status(){return status;}
        double get_time();

        //Setters
        void set_status(bool newstatus);


    private:

        int ident[2];  // Identifier -> [plot_number, height]
        bool status;        // On/of status
        clock_t last_switch_time;  // Save the last switch time
        int gpio_out; 
        
        const int MINS = 60;
        void switch_status(bool newstatus); // Private function to switch the light 

};


#endif // ACTUATOR_H_INCLUDED
