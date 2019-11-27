/* Filename:      FS5.cpp
 * Project Name:  Compact Safety system for automatic flagpole 
 * Contributors:  Carl Jensen and David Strom
 * Programme:     Design and Product Realisation (CDEPR)
 * Date:          28-05-2019
 * University:    KTH Royal Institute of Technology
 * Course:        MF133X Degree Project in Mechatronics
 * 
 * Purpose : 
 *    Library for the FS5 sensor.
 * 
 * Hardware:      
 *    Sensor:     FS5 Thermal Mass Flow Sensor
 *    
 * Notes: 
 *    - In order for this library to work, please install the library
 *      Filters created by hideakitai via:
 *      https://github.com/hideakitai/Filters
 *    - In order to get a signal from the FS5 sensor, the sensor has to be
 *      configured in a constant temperature setup.  
 */

//Include libraries.
#include "Arduino.h"
#include "FS5.h"
#include "Filters.h"

float filterFrequency = 0.3; //Set filter frequency.

//Initialize low pass filter.
FilterOnePole filterOneLowPass(LOWPASS, filterFrequency);      

/* Constructor:   FS5sensor::FS5sensor(int pin, double U0, double U50, double v50, double n)
 * 
 * Purpose:     Setup for the class FS5sensor. Declaring private
 *              variables. Calculate fluidic dependent constant k.
 * 
 * Input:       Pin for FS5                             (int pin)
 *              Voltage U at wind speed 0%              (double U0)
 *              Voltage U at wind speed 50%             (double U50)
 *              Wind speed v at wind speed 50%          (double v50)
 *              Value to setup FS5 for parameter n      (double n)
 *
 * Output:      None
 */
FS5sensor::FS5sensor(int pin, double U0, double U50, double v50, double n){
  _pin = pin;
  _U0 = U0; 
  _U50 = U50; 
  _v50 = v50; 
  _n = n; 
  _k = (pow(U50/U0,2)-1)/pow(v50,n);    
}

/* Function:    double FS5sensor::voltage() 
 * Purpose:     Mapping the input signal from the FS5 sensor to voltage
 *              and filter the signal.   
 * 
 * Input:       None
 * 
 * Output:      The current voltage input from the FS5 sensor. 
*/
double FS5sensor::voltage(){
  //Mapping the signal to voltage and filter out noise.
  double voltage = filterOneLowPass.input(analogRead(_pin)/_c*_maxInputVoltage);  
  return voltage; 
}

/* Function:     double FS5sensor::velocity()
 * Purpose:      Calculate the wind velocity.   
 * 
 * Input:        None
 * 
 * Output:       Wind velocity
*/
double FS5sensor::velocity(){
  double U = voltage();   //Record the current voltage.
  
  //If the recorded voltage is lower than the voltage U0 at 0% wind speed, the current voltage is set to U0. This can happen due to error margins in the measurement of U0.
  if(U<_U0){              
    U = _U0; 
  }
  
  //Calculates the wind velocity from given parameters and the recorded voltage U. 
  double vel = (pow(((U-_U0)*(U+_U0)),(1/_n)))/(pow(_k,(1/_n))*(pow(_U0,(2/_n))));  
                                                         
  return vel;                                                              
}
