/* Filename:      FS5.h
 * Project Name:  Compact Safety system for automatic flagpole 
 * Contributors:  Carl Jensen and David Strom
 * Programme:     Design and Product Realisation (CDEPR)
 * Date:          28-05-2019
 * University:    KTH Royal Institute of Technology
 * Course:        MF133X Degree Project in Mechatronics
 * 
 * Purpose : 
 *    Header for FS5 library.
 * 
 * Hardware:      
 *    Sensor:    FS5 Thermal Mass Flow Sensor
 *    
 * Notes: 
 *    - In order for this library to work, please install the library
 *      Filters created by hideakitai via:
 *      https://github.com/hideakitai/Filters
 *    - In order to get a signal from the FS5 sensor, the sensor has to be
 *      configured in a constant temperature setup.  
 */
 
#ifndef FS5_h     //Include guard.
#define FS5_h
#include "Arduino.h"
#include "Filters.h"

//Class for mapping input signal from the FS5 sensor to voltage and wind velocity.
class FS5sensor {
  public:
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
    FS5sensor(int pin, double U0, double U50, double v50, double n); 
    
    /* Function:    double FS5sensor::voltage() 
     * Purpose:     Mapping the input signal from the FS5 sensor to voltage
     *              and filter the signal.   
     * 
     * Input:       None
     * 
     * Output:      The current voltage input from the FS5 sensor. 
    */
    double voltage();

    /* Function:     double FS5sensor::velocity()
     * Purpose:      Calculate the wind velocity.   
     * 
     * Input:        None
     * 
     * Output:       Wind velocity
    */
    double velocity();

 //Private variables. 
  private: 
    int _pin;                       //Pin for input signal for the FS5.    
    double _U0;                     //Voltage U at wind speed 0%.
    double _U50;                    //Voltage U at wind speed 50%.
    double _v50;                    //Wind velocity v at wind speed 50%.
    double _n;                      //Value to setup FS5. 
    double _k;                      //Fluidic dependent constant. 
    double _c = 1023;               //Parameter to map input signal. 
    double _maxInputVoltage = 5;  //Maximum input voltage from FS5. 
};
#endif 
