/* Filename:      Controller.h
 * Project Name:  Compact Safety system for automatic flagpole 
 * Contributors:  Carl Jensen and David Strom
 * Programme:     Design and Product Realisation (CDEPR)
 * Date:          28-05-2019
 * University:    KTH Royal Institute of Technology
 * Course:        MF133X Degree Project in Mechatronics
 * 
 * Purpose: 
 *    Header for Controller library.
 * 
 * Hardware:      
 *    Stepper Motor:  28byj-48 12V
 *    Driver:         ULN2003 IC
 *    
 * Notes: 
 *    - In order for this library to work, please install the library
 *      CheapStepper created by tyhenry via: 
 *      https://github.com/tyhenry/CheapStepper
 */

#ifndef Controller_h        //Include guard.
#define Controller_h
#include "Arduino.h"        
#include "CheapStepper.h"
#include "FS5.h"

//Class for controlling the stepper motor.
class Control{
  public:   
      /* Constructor: Control::Control(int limitSwitch, int IN1, int IN2, int IN3, int IN4, int pin, double U0, double U50, double v50, double n)
       *
       * Purpose:     Setup for the class Control. Declaring privat
       *              variables. 
       *
       * Input:       Pin for limitSwitch               (int limitSwitch)
       *              Pins for stepper motor            (int IN1 - int IN4)
       *              Pin for FS5                       (int pin)
       *              Voltage at wind speed 0%          (double U0)
       *              Voltage at wind speed 50%         (double U50)
       *              Wind velocity at wind speed 50%   (double v50)
       *              Value to setup FS5 for parameter n (double n)
       *              
       * Output:      None
      */
      Control(int limitSwitch, int IN1, int IN2, int IN3, int IN4, int pin, double U0, double U50, double v50, double n);
    
      /* Function:    void Control::scan()
       * 
       * Purpose:     Find the direction of, and align the sensor to, the
       *              wind current by scanning a span of approximately
       *              180 degrees.  
       * 
       * Input:       None
       * 
       * Output:      None
      */
      void scan();

  private:
      int _limitSwitch;   //Pin for limit switch.
      int _IN1;           //Pin for Stepper motor.
      int _IN2;           //Pin for Stepper motor.
      int _IN3;           //Pin for Stepper motor.
      int _IN4;           //Pin for Stepper motor.
      int _pin;           //Pin for FS5.
      double _U0;         //Voltage U at wind speed 0%.
      double _U50;        //Voltage U at wind speed 50%.
      double _v50;        //Wind velocity v at wind speed 50%.
      double _n;          //Value to setup FS5 for parameter n.
};
#endif
