/**
 * @file sensor.h
 * @brief Provides simple methods and variables for a sensor object that inherits from it
 * @date 03/12/2021
 */

#ifndef SENSOR_H_INCLUDED
#define SENSOR_H_INCLUDED

// From this class inherits each sensor

class Sensor {

	public:
		//~Constructors
		Sensor(void);
		Sensor(int plot_num, int height){ident[0] = plot_num; ident[1] = height;}

		//~Basics functions
		void reset_cont(){ cont = 0; }
		void increment_cont() { cont++; }

		//~Getters
		float get_value(){ return value; }
		int get_cont(){ return cont; }
		void get_ident(int identifier[]){identifier[0] = ident[0]; identifier[1] = ident[1];}

	protected:
    	// Al sensors have to implement this function
		virtual void update_value() = 0;

		//~Setters
		void set_value(float newvalue) { value = newvalue; }

	private:
    	float value = 0; // Current measured value
	  	double cont = 0; // Measured values after start
    	int ident[2];  // Identifier -> [plot_number, height]
};

#endif
