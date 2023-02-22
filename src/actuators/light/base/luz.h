#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include <ctime>

class Luz{

    public:

        //~ Constructors
        Luz(void);
        Luz(int plot_number, int height, bool init_status = false);

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
        const int MINUTOS = 60;

};


#endif // LUZ_H_INCLUDED
