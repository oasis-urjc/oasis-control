# APIs

## Sensores general

**Constructors**
		Sensor(void);
		Sensor(int plot_num); // Number of plot
		Sensor(Sensor sensor);

**Basics functions**
		void reset_cont(){cont = 0;}

**Getters**
		float get_value();
		int get_cont();
		int get_plot_ident();

***protected:***
		void update_value(int new_value);
		
### DHT

**Constructor**
		DHT(int plot_num, int gpio_in); //Number of plot, pin where is conected.
**Obligated funcion**
		virtual int update_value();
   
 **Basic funcitons**
    float get_hum();
    float get_temp();
	
### Moisture sensor

**Constructor**
		Moisture_sensor(int plot_num, int gpio_in); //Number of plot, pin where is conected.

  **Obligated funcion**
		virtual void update_value();
		
### Photoresistance

**Constructor**
		Photoresistance(int plot_num, int gpio_in); //Number of plot, pin where is conected.

**Obligated funcion**
		virtual void update_value();
