# Docs ~ Sensor Class:

<div align="center">
<img width=100px src="https://img.shields.io/badge/status-active-brightgreen" alt="explode"></a>
<img width=200px src="https://img.shields.io/badge/Last modification-03/21/2021-blue" alt="explode"></a>
</div>


## Description: 
This class allows to create inherited sensors classes with a simple structure. 


## Variables: 

All of the variables are private and only can be modified with the setters and initial parametres.

---------------------------------------------------------------------------------------------------------------------------
- value(float): Contains the current measured value
---------------------------------------------------------------------------------------------------------------------------
- plot_ident(int): The number of the plot where the sensor is installed (default = 0)
---------------------------------------------------------------------------------------------------------------------------
- cont(double): The number of measurements since the start 
---------------------------------------------------------------------------------------------------------------------------
- status(bool): Storage the status of the sensor (on/off)(Not implemented yet) 
---------------------------------------------------------------------------------------------------------------------------


## Methods 

### Public:
**Constructors**
---------------------------------------------------------------------------------------------------------------------------
- Sensor(void): Creates a Sensor with the default values 
---------------------------------------------------------------------------------------------------------------------------
- Sensor(int plot_num): Creates a Sensor with the plot number passed as parameter
---------------------------------------------------------------------------------------------------------------------------


**Basic Methods**
---------------------------------------------------------------------------------------------------------------------------
- reset_cont(): Reset the sensor contador

  @ params: void 
  
  @ return: void 
---------------------------------------------------------------------------------------------------------------------------
- increment_cont(): Add one to the contador value 

  @ params: void 
  
  @ return: void 
---------------------------------------------------------------------------------------------------------------------------


**Getters**
---------------------------------------------------------------------------------------------------------------------------
- float get_value(): Returns the last measured value 

  @ params: void 
  
  @ return: value(float) 
---------------------------------------------------------------------------------------------------------------------------
- get_cont(): Returns the number of measurements since the start 

  @ params: void 
  
  @ return: cont(int9 
---------------------------------------------------------------------------------------------------------------------------
- get_plot_ident(): Returns the plot number 

  @ params: void 
  
  @ return: plot_ident(int) 
---------------------------------------------------------------------------------------------------------------------------

### Protected:

**Basic Virtual Methods**
---------------------------------------------------------------------------------------------------------------------------
- update_value(): Virtual method used to measure the sensor value 

  @ params: 
  
  @ return: 
---------------------------------------------------------------------------------------------------------------------------

**Setters**
---------------------------------------------------------------------------------------------------------------------------
- set_value(): Set the new measured value 

  @ params: newvalue(float) 
  
  @ return: void
---------------------------------------------------------------------------------------------------------------------------




