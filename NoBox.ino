/*
 * No Box
 */
#define SERVOSECTION = 1;
#define PEIZOSECTION = 2;
#define SHOCKSECTION = 3;
const int capacativePin = 2;
const int piezoPin = 11;
const int servoPin = 10;
const int solenoidPin = 10;
const int potentiometerPin = A0;
int currentLevel = SERVOSECTION;
int potentiometerValue;

void setup(){
	Serial.begin(9600);
    pinMode(peizoPin, OUTPUT);
    pinMode(servoPin, OUTPUT);
    pinMode(solenoidPin, OUTPUT);
    pinMode(capacativePin, OUTPUT);

}
void loop(){
    switch(currentLevel){
        SERVOSECTION:
            if(digitalRead(capacativePin == HIGH)){
                openBox();
                currentLevel = PEIZOSECTION;
                   
            }
            break;
        PEIZOSECTION:
            potentiometerValue = readPotentiometer();
            analogWrite(piezoPin, map(potentiometerValue, 0, 1024, 0, 255));
            analogWrite(ledPin, map(potentiometerValue, 0, 1024, 0, 255));
            if(potentiometerValue == 1024){
                
            }
            break;    
    }
}
int readPotentiometer(){
   return analogRead(potentiometerPin);
}
void openBox(){
    
}
