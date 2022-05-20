/**
 * @file Sensor.h
 * @brief Provides simple methods and variables for a sensor object that inherits from it
 * @date 03/12/2021
 */

#ifndef SENSOR_H_INCLUDED
#define SENSOR_H_INCLUDED

// From this class inherits each sensor

class Sensor{

	public:

		//~Constructors
		Sensor(void);
		Sensor(int plot_num){ plot_ident = plot_num; }

		//~Basics functions
		void reset_cont(){ cont = 0; }
		void increment_cont() { cont++; }

		//~Getters
		float get_value(){ return value; }
		int get_cont(){ return cont; }
		int get_plot_ident(){ return plot_ident; }

	protected:
    // Al sensors have to implement this function
		virtual void update_value() = 0;

		//~Setters
		void set_value(float newvalue) { value = newvalue; }

	private:
    float value = 0; // Current measured value
	  double cont = 0; // Measured values after start
    int plot_ident = 0;  // Number of plot
		bool status = true; // true --> on, False --> off(Not implemented yet)
};

#endif
