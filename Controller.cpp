/* Filename:      Controller.cpp
 * Project Name:  Compact Safety system for automatic flagpole 
 * Contributors:  Carl Jensen and David Strom
 * Programme:     Design and Product Realisation (CDEPR)
 * Date:          28-05-2019
 * University:    KTH Royal Institute of Technology
 * Course:        MF133X Degree Project in Mechatronics
 * 
 * Purpose: 
 *    Library for controlling the stepper motor to preform scanning
 *    procedure. 
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

//Includes necessary libraries. 
#include "Arduino.h"
#include "Controller.h"
#include "CheapStepper.h"
#include "FS5.h"

/* Constructor: Control::Control(int limitSwitch, int IN1, int IN2, int IN3, int IN4, int pin, double U0, double U50, double v50, double n)
 *
 * Purpose:     Setup for the class Control. Declaring private variables. 
 *
 * Input:       Pin for limitSwitch                     (int limitSwitch) 
 *              Pins for stepper motor                  (int IN1 - int IN4) 
 *              Pin for FS5                             (int pin)
 *              Voltage at wind speed 0%                (double U0)
 *              Voltage at wind speed 50%               (double U50)
 *              Wind velocity at wind speed 50%         (double v50)
 *              Value to setup FS5 for parameter n      (double n)
 *              
 * Output:      None
*/

Control::Control(int limitSwitch, int IN1, int IN2, int IN3, int IN4, int pin, double U0, double U50, double v50, double n){
  _limitSwitch = limitSwitch; 
  _IN1 = IN1;
  _IN2 = IN2;
  _IN3 = IN3;
  _IN4 = IN4;
  _pin = pin; 
  _U0 = U0;
  _U50 = U50;
  _v50 = v50;
  _n = n;  
  pinMode(limitSwitch,INPUT);
}

/* Function:    void Control::scan()
 * 
 * Purpose:     Find the direction of, and align the sensor to, the wind
 *              current by scanning a span of approximately 180 degrees.  
 * 
 * Input:       None
 * 
 * Output:      None
*/
void Control::scan(){
  
  //Setup for the stepper motor and the FS5 sensor.
  CheapStepper stepper (_IN1,_IN2,_IN3,_IN4);   //Initialize controller 
                                                   //for stepper motor.
  stepper.setRpm(16);                              //Set the rpm of the
                                                   //stepper motor.
  FS5sensor FS5(_pin, _U0, _U50, _v50, _n);        //Initialize FS5 sensor. 

  int stepCounter = 0;      //Counter for step rotation. 
  int state = 0;            //The state for the switch case.
  bool startFind = true;    //State variable used to find start position. 
  bool cw = true;           //The state variable for the direction.
  int Position = 0;         //Current step position.
  int scaning = true;       //State variable for the scanning process.
  double maxFS5 = 0;        //Placeholder for the maximum voltage.
  int maxPosition;          //Placeholder for the step position at maxFS5. 
  int LSSafteyStep = 400;   //The number of steps to release limit switch.
  bool safetyState;         //State variable for releasing of limit switch.
  int calibration = 300;    //Extra steps for calibration. 
  
  
  
  
  
  //While scanning is true, scan until the maximum wind speed is found and the sensor is aligned to the wind current.
  while(scaning){          
      //Switch statement for controlling logic of controller.   
      switch(state){      
        
        /* Case 0: 
         * Rotate the stepper motor cw until the limit switch is activated. 
         * Then release the limit switch. 
         */
        case 0:                                        
          Serial.println("Detecting start position...");

          while(startFind){         //While startFind is true...
            stepper.step(cw);       //Rotate steper motor one step cw.
            
            //If the limit switch is activated the start position is found, change state variable to false.
            if(digitalRead(_limitSwitch) == HIGH){      
              startFind = false;    
              
              //Rotate stepper motor ccw to release the limit switch.
              for (int p = 0; p < LSSafteyStep; p++){   
                stepper.step(!cw);  //Rotate ccw one step.
                }
              state = 1;              //Change state and go to case 1. 
            }
          }
          Serial.println("Start position detected");
        break; 

        /* Case 1: 
         * Scans the span for the maximum value of the voltage from 
         * the FS5 sensor. The scan is done when limit switch is activated. 
         * Release the limit switch. 
         */
        case 1:  
          Serial.println("Scanning...");
          
          //While limitSwitch is not activated...
          while(digitalRead(_limitSwitch) == LOW){  
            stepper.step(!cw);                     //Rotate one step ccw.
            double FS5valVolt = FS5.voltage();  //Get the current voltage.
            Position += 1;                         //Increase Position by one.
            stepCounter += 1;                      //Keep track of steps.

            //If the current voltage from the FS5 is greater than the old, update the old value to the new.
            if (FS5valVolt > maxFS5){               
              maxFS5 = FS5valVolt;              //Update the max voltage.
              maxPosition = Position;           //Update position at max FS5.
             }
            }

           //Move the stepper motor cw to release the limit switch.
           for (int p = 0; p < LSSafteyStep; p++){  
            stepper.step(cw);                   //Rotate one step cw.
           }
           
           state = 2;                           //Go to case 2. 
           Serial.println("Scanning complete");
        break; 

        /* Case 2: 
         * Rotates the stepper motor to align FS5 sensor to the wind current.
         */
        case 2:   
            Serial.println("Aligning sensor...");
            Position = 0;                   //Reset Position to zero.
            safetyState = true;             //Reset safetyState to true.

            //Rotates the stepper motor cw to the correct step to align the FS5 properly.
            while((Position < stepCounter-maxPosition+LSSafteyStep+calibration) && safetyState){    
              stepper.step(cw);             //Rotate one step cw.
              Position = Position + 1;      //Increase Position by one. 
              
              //If the limit switch is activated, move the stepper motor ccw to release the limit switch.
              if(digitalRead(_limitSwitch) == HIGH){      
                for (int p = 0; p < LSSafteyStep; p++){   
                  stepper.step(!cw);        //Rotate one step ccw. 
                }
                safetyState = false;        //Set safetyState to false. 
              }
            }
    
            //When the sensor has been aligned to the wind direction, the state varible is set to false and the scan is done. 
            scaning = false;                              
            Serial.println("Alignment complete");
            break; 
      }
  }
}
