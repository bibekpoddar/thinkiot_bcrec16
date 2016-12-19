/*
  Analog input, analog output, serial output
 
 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.
 
 The circuit:
 * MQ135 connected to analog pin 0.
 * LED connected from digital pin 9 to ground
 
 Copied from sample [AnaloginOutSerial]
 */

// These constants won't change.  They're used to give names
// to the pins used:
#include<Arduino.h>
#include<Wire.h>
#define MQ135_DEFAULTPPM 399 //default ppm of CO2 for calibration
#define MQ135_RO 68550 //default Ro for MQ135_DEFAULTPPM ppm of CO2
#define MQ135_SCALINGFACTOR 116.6020682 //CO2 gas value
#define MQ135_EXPONENT -2.769034857 //CO2 gas value
#define MQ135_MAXRSRO 2.428 //for CO2
#define MQ135_MINRSRO 0.358 //for CO2


const int analogInPin = A0;  // Analog input pin that the MQ135 is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

int co2ppm;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
 
  
}


void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);            
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);  
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);           

  // print the results to the serial monitor:
  Serial.print("sensor = " );                       
  Serial.print(sensorValue);      
  Serial.print("\t output = ");      
  Serial.println(outputValue);   


long resvalue=((float)22000*(1023-sensorValue)/sensorValue);

co2ppm=mq135_getppm(resvalue,MQ135_RO);

// Serial.print(mq135_getppm(resvalue,MQ135_RO));
long mq135_getro(long resvalue,long ppm);
  // wait 100 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(500);                     
}


long mq135_getro(long resvalue,long ppm) {
	return (long)(resvalue * exp( log(MQ135_SCALINGFACTOR/ppm) / MQ135_EXPONENT ));
}
double mq135_getppm(long resvalue,long default_RO) 
{
	double ret = 0;
	double validinterval = 0;
	validinterval = resvalue/(double)default_RO;
	if(validinterval<MQ135_MAXRSRO && validinterval>MQ135_MINRSRO) {
		ret = (double)MQ135_SCALINGFACTOR * pow( ((double)resvalue/default_RO), MQ135_EXPONENT);
	}
	return ret;
}

