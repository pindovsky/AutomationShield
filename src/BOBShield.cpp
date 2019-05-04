#include "BOBShield.h"



// declaring PIN and initializing sensor library
void BOBClass::begin() {
  pinMode(POT_PIN, INPUT);			// set Potentiometer pin
}


void BOBClass::calibration()
{
	short calmeasure; 				   		// Temporary measurement value


	BOBShield.servoWrite(130);					// Tilt beam to the minimum so the ball falls towards the sensor
	delay(100);					   		// Wait for things to settle
	for (int i=1; i<=100; i++) {	    				// Perform 100 measurements
		calmeasure = BOBShield.sensorRead(); 			// Measure
		if (calmeasure < minCalibrated){ 			// If lower than already
			minCalibrated = calmeasure; 			// Save new minimum
		}
		delay(10);						// Wait between measurements
	}

	BOBShield.servoWrite(70);					// Tilt beam to the maximum so the ball falls towards the sensor
	delay(100);					   		// Wait for things to settle
	for (int i=1; i<=100; i++) {	    				// Perform 100 measurements
		calmeasure = BOBShield.sensorRead(); 			// Measure
		if (calmeasure > maxCalibrated){ 			// If lower than already
			maxCalibrated = calmeasure; 			// Save new maximum
		}
		delay(10);						// Wait between measurements
	}

	
    calibrated = 1;

}


//values from potentiometer in %
float BOBClass::referenceRead(){
   _referenceRead = analogRead(POT_PIN);
   _referenceValue = AutomationShield.mapFloat(_referenceRead,0.00,1023.00,0.00,100.00);
  return _referenceValue;
}

//values from potentiometer computed for servo
float BOBClass::actuatorWrite(){
   _referenceRead = analogRead(POT_PIN);
   _servoValue = AutomationShield.mapFloat(_referenceRead,0.00,1023.00,70.00,130.00);
  return _servoValue;
}

//values from sensor in %
void BOBClass::sensorRead(){
 range = sens.readRange();
	
    if (range < minimum) {range = minimum;}
    else if (range > maximum) {range = lastValue;}


   pos = map(range,minimum,maximum,100,0);
 return pos();
 }
 }

BOBClass BOBShield;

