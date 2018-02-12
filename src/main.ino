#include <Adafruit_NeoPixel.h>
#include <math.h>
#define ARM_MATH_CM4 //for fourier 
#include <arm_math.h> //for fourier 
#include "rgbhsv.h"
#include "strands.h"
#include "led7Segment.h"
#include "fourier.h"
#include <PWMServo.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
//PIN DEFINITIONS

#define POWER_LED_PIN 13 // Heart beat
#define  KEYB      12
#define  SERVOCONTROLPIN 	22
#define  SERVO     19
#define  STRANDPIN 20 
#define  AUDIOINPIN 21 
//reserved for segment
int segmentArr[8] = {6,7,2,1,0,5,4,3};
//const int POTPIN1 = A0;
//const int POTPIN2 = A3;
//const int POTPIN3 = A1;


//int potPin1Val;
//int potPin2Val;
//int potPin3Val;

int counter =0;
bool on=false;
int mode;
int oldMode =0;

static const int SAMPLE_RATE_HZ = 9000; 
bool boolBoxCartel [30];
IntervalTimer samplingTimer; //must be gloval as per teenseys suggestion 
int timeoutCounter = 0;//for timing out music 

bool powerLEDstate = 0;

LEDStrand *strandy;
audioSampler *sampler;
LEDSegment *segmenty = new LEDSegment(segmentArr);
PWMServo myServo;

void setup() {
	segmenty->setup();
	segmenty->turnOff();
	pinMode(POWER_LED_PIN, OUTPUT); // Heartbeat
	pinMode(SERVOCONTROLPIN, OUTPUT);
	strandy = new LEDStrand(STRANDPIN, 30); 
	sampler = new audioSampler(AUDIOINPIN, 30); 
	samplingTimer.begin(samplingCallback, 1000000/SAMPLE_RATE_HZ);

	Serial.begin(9600);    
	pinMode(KEYB, INPUT); 
	myServo.attach(SERVO);
	
	strandy->color(32);
	strandy->staticRainbow();
	strandy->setBrightness(255);
	strandy->turnOn();
	strandy->updateLEDS();
	mode = 5;
}


void loop() {

	//-------------------
	//Input Portion
	//-------------------

    //This is for being on
    if(counter%1==0){
    	if(digitalRead(KEYB)!=HIGH){
    		//RUN WHEN OFF
    		on=false;
    		strandy->setBrightness(0);
    		segmenty->turnOff();
   			strandy->updateLEDS();
   			digitalWrite(SERVO, LOW);
   			digitalWrite(SERVOCONTROLPIN, LOW);
		}
		else{
			//RUN WHEN ON
			heartbeat();
			digitalWrite(SERVOCONTROLPIN, HIGH);
    		on=true;
    	}
    }
	
    //This reads in multiple Pot values
    if(counter%1==0 && on){
	    //potPin1Val = analogRead(POTPIN1);
	    //potPin2Val = analogRead(POTPIN2);
	    //potPin3Val = analogRead(POTPIN3);
    }
    
    //General info
  	//int mode = map(potPin1Val, 0, 1023, 1, 5);
  	//Auto switch for music playing might be removed for ui/ux reasons
  	/*
  	if(sampler->isMusicPlaying()){
      timeoutCounter--;
      if(timeoutCounter < -1){
        timeoutCounter = 0;
        mode = 5;
      }
    }
    else{
      timeoutCounter++; 
      if(timeoutCounter > 1){
        timeoutCounter = 0;
      }
      
    }
    */

    if (Serial.available()) {
    	mode = Serial.parseInt();  // will not be -1
    	// actually do something with incomingByte
  	}
  	switch(mode){
  		case 1:{
  			if(oldMode != 1){
  				strandy->setBrightness(255);
				

  			}
  			if(on){
  				segmenty->changeNum(1);
  			}
  		 	//-------------------
		  	//Mode 1: Adjust LED and Servo directly
		  	//------------------- 
    		//LED Strand Portion
		  	if(counter%1==0 && on){	
		 		strandy->turnOn();
				strandy->rainbow();
				
		 		
		  		//strandy->setBrightness(map(potPin2Val, 0, 1023, 0, 255));
			    //strandy->fillFromSource(map(potPin3Val, 0, 1023, 0, 30));	
			    //strandy->color(map(potPin4Val, 0, 1023, 0, 360));

				strandy->updateLEDS();
		    }
		    
		    //Servo
		    if(counter%1==0 && on){
		    	//myServo.write(map(potPin5Val, 0, 1023, 0, 179)); 
		    }
		    oldMode = 1;

		 } break;
		 case 2:{
		 	if(on){
		 		segmenty->changeNum(2);
		 	}
		 	//-------------------
		  	//Mode 2: Rainbow
		  	//------------------- 
		  	
		    if(counter%1==0 && on){	
		    	//strandy->setBrightness(map(potPin2Val, 0, 1023, 0, 255));
		    }
		    /*int val = map(potPin3Val, 0, 1023, 1, 10);
		    if(counter%val==0 && on){
		    	strandy->rainbow();	
		    }*/
		    strandy->updateLEDS();
		    
		    //Servo
		    if(counter%1==0 && on){
		
		    	//myServo.write(map(potPin5Val, 0, 1023, 0, 179)); 
		    	
		    }
		    oldMode = 2;

		 } break;
		 case 3:{
		 	if(on){
		 		segmenty->changeNum(3);
		 	}
		 	//-------------------
		  	//Mode 3: Flash
		  	//------------------- 
		  	
		    if(counter%1==0 && on){	
		    	//strandy->setBrightness(map(potPin2Val, 0, 1023, 0, 255));
		    	//strandy->color(map(potPin4Val, 0, 1023, 0, 360));
		    }
		    //int val = map(potPin3Val, 0, 1023, 1, 100);
		    /*
		    if(counter%(1000/val)==0 && on){
		    	strandy->flash();	
		    }
		    */
		    strandy->updateLEDS();
		    
		    //Servo
		    if(counter%1==0 && on){
		    	//myServo.write(map(potPin5Val, 0, 1023, 0, 179)); 
		    }
		    oldMode = 3;

		 } break;
		  case 4:{
		 	if(on){
		 		segmenty->changeNum(4);
		 	}
		 	//-------------------
		  	//Mode 4: Random fun things
		  	//------------------- 
		  	
		    if(counter%1==0 && on){	
		    	//strandy->setBrightness(map(potPin2Val, 0, 1023, 0, 255));
		    }
		    /*
		    int val = map(potPin4Val, 0, 1023, 1, 100);
		    if(counter%(1000/val)==0 && on){
		    	strandy->flash();	
		    }*/
		    strandy->updateLEDS();
		    
		    //Servo
		    if(counter%1==0 && on){
		    	//myServo.write(map(potPin5Val, 0, 1023, 0, 179)); 
		    }
		    oldMode = 4;

		 } break;
		 case 5:{
		 	if(on){
		 		segmenty->changeNum(5);
		 	}
		 	if(oldMode != 5){

		 	}
  		 	//-------------------
		  	//Mode 5: Dancing lights
		  	//------------------- 
    		//LED Strand Portion
		  	if(counter%1==0 && on){	

		          sampler->getBoolBox(boolBoxCartel);
		          bool temp= sampler->issaBeat();
		          //strandy->rainbow();
				strandy->danceLights(boolBoxCartel, temp);
				strandy->updateLEDS();
		    }
		    oldMode = 5;
      		}break;
  	}
  	//--------
    //Debuging
    //--------
    //Serial.write("On: ");
  	//Serial.println(on);
  	//Serial.write("Mode: ");
  	//Serial.println(mode);
  	//Serial.write("potPin1Val: ");
  	//Serial.println(potPin1Val);
    //This is run everytime esentially a clock
    if(counter == 1000){
    	counter = 0;
    }
    counter++;
    delay(1);
}
void heartbeat() {
  digitalWrite(POWER_LED_PIN, powerLEDstate); // Heartbeat
  powerLEDstate = !powerLEDstate; // Flip state
}
//Bullshit code you have to write that is limited by teensey not wanting to run too many sampling timers.
void samplingCallback() {
  sampler->samplingCallback();
}


