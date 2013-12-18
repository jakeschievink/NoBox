/*
 * No Box
 * Written by Jake Schievink
 */
#include <CapSense.h>
#include <Servo.h>

//#define DEBUG
#define TOPSECTION  1
#define MIDSECTION  2
#define DONE  3

const int capacativeReaderPin = 4;
const int capacativeSensorPin = 2;

const int solenoidPin = 12;
const int piezoPin = 11;
const int ledPin = 10;
const int servoPin = 9;
const int potentiometerPin = A0;

//Servo Start and End Positions
const int servoStartPosition = 0;
const int servoEndPosition = 180;

//Base value for capacative touch. 
const int capPressed = 1000;

int currentLevel = TOPSECTION;
int potentiometerValue;

long capVal;

CapSense capacativeSense = CapSense( capacativeSensorPin, capacativeReaderPin); 
Servo servo;

void setup(){
	Serial.begin(9600);
    pinMode(ledPin, OUTPUT);
    pinMode(piezoPin, OUTPUT);
    pinMode(solenoidPin, OUTPUT);
    pinMode(capacativeReaderPin, OUTPUT);
    servo.attach(servoPin)
    servo.write(servoStartPosition);
}

void loop(){
    Serial.print("CapValue: ");
    Serial.println(capacativeSense.capSense(30));
    switch(currentLevel){

        case TOPSECTION:
            capVal =  capacativeSense.capSense(30);
            if(capacativeDone()){
                openBox();
                analogWrite(piezoPin, 100);
                currentLevel = MIDSECTION;
                   
            }
           break;

        case MIDSECTION:
            
            potentiometerValue = readPotentiometer();

            analogWrite(piezoPin, map(potentiometerValue, 0, 1024, 110, 255));
            analogWrite(ledPin, map(potentiometerValue, 0, 1024, 0, 255));

            if(potentiometerValue == 1023){
                solenoidOpen();
                currentLevel = DONE;
            }
            #if defined DEBUG
                Serial.print("potval: ");
                Serial.println(potentiometerValue);
            #endif 
            break;    

        case DONE:
            analogWrite(piezoPin, LOW);
            analogWrite(ledPin, LOW);
            #if defined DEBUG
//                Serial.println("done");
            #endif
            break;
           
    }
}

boolean capacativeDone(){
    if(capVal < capPressed){
        return false;
    }else{
        return true;
    }
    
}

int readPotentiometer(){
   return analogRead(potentiometerPin);
}

void solenoidOpen(){
    digitalWrite(solenoidPin, HIGH);
}

void openBox(){
    servo.write(servoEndPosition);
}    
