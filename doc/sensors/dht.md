# Doc-DHT

<div align="center">
<img width=100px src="https://img.shields.io/badge/status-active-brightgreen" alt="explode"></a>
<img width=200px src="https://img.shields.io/badge/Last modification-03/01/2022-blue" alt="explode"></a>
</div>

## Description: 

This class allows to create DHT (Digital Humidity) sensors classes with a simple structure, by inheriting from Sensor Class. 

## Variables: 

All of the variables are private and only can be modified with the setters and initial parametres.

It also inherits the varables of Sensor.

---------------------------------------------------------------------------------------------------------------------------
- pin_in(int): Contains the pin number where the sensor is sending information.
---------------------------------------------------------------------------------------------------------------------------
- hum(float): The humidity sensed.
---------------------------------------------------------------------------------------------------------------------------
- temp(double): The temperature sensed.
---------------------------------------------------------------------------------------------------------------------------
## Methods 

### Public:
**Constructor**
---------------------------------------------------------------------------------------------------------------------------
- DHT(int plot_num, int gpio_in): Creates a DHT Sensor with the plot number passed as parameter and sets the pin on the gpio_in passed.
---------------------------------------------------------------------------------------------------------------------------

**Basic Method**
---------------------------------------------------------------------------------------------------------------------------
- update_value(): Updates the variables temp and hum.

  @ params: void 
  
  @ return: void 
---------------------------------------------------------------------------------------------------------------------------

**Getters**
---------------------------------------------------------------------------------------------------------------------------
- get_hum(): Returns the last updated hum value.

  @ params: void 
  
  @ return: hum(float) 
---------------------------------------------------------------------------------------------------------------------------
- get_temp(): Returns the last updated temp value.

  @ params: void 
  
  @ return: temp(float)
---------------------------------------------------------------------------------------------------------------------------

