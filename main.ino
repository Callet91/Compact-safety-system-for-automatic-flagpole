/* Filename:        main.ino
 * Project Name:    Compact Safety system for automatic flagpole 
 * Contributors:    Carl Jensen and David Strom
 * Programme:       Design and Product Realisation (CDEPR)
 * Date:            28-05-2019
 * University:      KTH Royal Institute of Technology
 * Course:          MF133X Degree Project in Mechatronics
 * 
 * Purpose: 
 *   This scripts contains the main functionality for the safety system 
 *   prototype for Hotswaps automatic flagpole. 
 * 
 *   First, the code conducts a scan for the wind current and aligns the 
 *   FS5 sensor accordingly to the wind current. 
 * 
 *   It then records the wind velocity in intervalls and stores all 
 *   recorded values in an array. The array is then sorted and the 
 *   median wind velocity, which represent the current wind 
 *   velocity, can be determined by the middle element of the sorted array.
 * 
 *   If the current wind velocity exceeds the maxiumum allowed wind 
 *   velocity a JSON array is created and printed to the serial monitor 
 *   with a status to lower the flag. 
 * 
 *   Else, if the current wind velocity is in the allowed span, a JSON 
 *   array is created and printed to the serial monitor with a status to 
 *   not lower the flag. 
 * 
 * Hardware:      
 *    MCU:          ATmega328 
 *    Clock Speed:  16 MHz
 *    Board:        Arduino Nano 3.x
 *    Used pins:    A0, 7, 8, 9, 10, 12
 *    
 * Notes: 
 *   - The values U0, U50 and v50 are measured values and can vary. 
 *   - See Controller.cpp and FS5.cpp for a more thorough 
 *     understanding of the logic behind the scan- and 
 *     wind measuring procedure.
*/
 
 
 
 
 
//Include libraries.
#include "Controller.h"
#include "FS5.h"
#include "CheapStepper.h"
#include "quickSort.h"
#include <ArduinoJson.h>

//The input pin for the FS5 sensor.
int pinFS5 = A0;

//The measured value for the voltage output from the FS5 sensor at wind speed 0%  [V].
double U0 = 2.24;   

//The measured value for the voltage output from the FS5 sensor at wind speed 50% [V].
double U50 = 3.33;  

//The measured value for the  wind speed at 50% [m/s].
double v50 = 8;     

//The constant to the FS5 calibrartion. 
double nFS5 = 0.51; 

//Pins for the stepper motor.
int IN1 = 10;
int IN2 = 9;
int IN3 = 8;
int IN4 = 7;

//Pin for the limit switch input.
int pinLS = 12;

//Initialize the quicksort algorithm.
Sorting qs; 

//Initialize the FS5.
FS5sensor FS5(pinFS5, U0, U50, v50, nFS5);      
            
//Intialize the controlling unit.
Control controller(pinLS,IN1,IN2,IN3,IN4,pinFS5,U0,U50,v50,nFS5);     

//Declaring the variables.
double currentWindSpeed;          //The current wind speed. 
double allowedWindSpeed = 2;     //The allowed wind speed. 
double FS5ValArray[11] = {0};   //Array for storing FS5 data.
int N = sizeof(FS5ValArray)/sizeof(FS5ValArray[0]); //The number of elements in the array


void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("//////////////////////////////////////////////////////////");
  
  //Scans the area for the highest wind speed,
  controller.scan(); 

  Serial.println("Start wind measuring sequence...");

  //Recording the wind speed at the the given point and stores the values in a array. 
  for(int k = 0; k < N; k++) {         
    FS5ValArray[k] = FS5.velocity();  
    Serial.println(FS5ValArray[k]); 
    delay(100); 
  }
  
  Serial.println("Measuring sequence complete");
  
  Serial.println("Determine the median value of the measuring sequence...");
  
  //Sorting the array.
  qs.quickSorting(FS5ValArray, 0, N-1); 

  //Declares the current wind speed as the median value from the recorded session.
  currentWindSpeed = FS5ValArray[(N-1)/2+1];  
  
  Serial.println("Create and print JSON array...");
  Serial.println("");

  //Creates a JSON array with information about the current 
  //windspeed and prints it to the Serial monitor.
  if ( currentWindSpeed > allowedWindSpeed){    
    StaticJsonDocument<200> doc;
    doc["Sensor"] = "FS5"; 
    doc["Wind Speed"] = currentWindSpeed; 
    doc["Status"] = "True"; 
    doc["Info"] = "Wind speed is NOT in the allowed span. Lower the flag."; 
    serializeJson(doc,Serial);  
  }
  
  
  
  else{
    StaticJsonDocument<200> doc;
    doc["Sensor"] = "FS5"; 
    doc["Wind Speed"] = currentWindSpeed; 
    doc["Status"] = "False"; 
    doc["Info"] = "Wind speed is in the allowed span. "; 
    serializeJson(doc,Serial); 
  }
  Serial.println(" ");
  Serial.println(" ");
  Serial.println("Program complete");
}
