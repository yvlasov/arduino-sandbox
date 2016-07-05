unsigned short stepPin = 9;                 // LED connected to digital pin 13
unsigned short dirPin = 10; 
unsigned short ms1Pin = 11; 
unsigned short ms2Pin = 12; 
unsigned short ms3Pin = 13; 
unsigned short microStep=16;
long amplitude=140000; //steps
long myPosition=0; //Steps*16
float stepIntMax=4000;
float stepInt=4000;
float stepIntMin=1;
int effectiveStepInt=0;
float accel=0.0005;
int timeLine=10000;
int curTime=0;
float curAcc=0;
unsigned int ticTac=0;
unsigned int ms16limit=1200;
unsigned int ms8limit=300;
unsigned int ms4limit=100;
unsigned int ms2limit=0;
unsigned int mslimit=0;
unsigned short dir=0;
int printTac=0;

void setup()
{
  Serial.begin(230400);
  pinMode(stepPin, OUTPUT);      // sets the digital pin as output
  pinMode(dirPin, OUTPUT);
  pinMode(ms1Pin, OUTPUT);
  pinMode(ms2Pin, OUTPUT);
  pinMode(ms3Pin, OUTPUT);
}


void loop()
{
  digitalWrite(stepPin, LOW);   // sets the LED on
  digitalWrite(dirPin, LOW);   // sets the LED on
  digitalWrite(ms1Pin, HIGH);   // sets the LED on
  digitalWrite(ms2Pin, HIGH);
  digitalWrite(ms3Pin, HIGH);
  stepInt=2000;
  ticTac=0; 
  curAcc=0;
  printTac=0;
  microStep=16;
  myPosition=0;
  
  Serial.println  ("HIGH");
  
  if ( dir > 0 ) {
    digitalWrite(dirPin, HIGH);
    dir=0;
  } else {
    digitalWrite(dirPin, LOW);
    dir=1; 
  }
  while (myPosition < amplitude){
   if(myPosition < amplitude-60000){
    //Speedup interval
    curAcc=accel;
   }
   else{
     curAcc=-accel;
   }
   if(printTac > 60000) {
    Serial.print  (" stepInt=");
    Serial.print  (stepInt);
    Serial.print  (" microStep=");
    Serial.print  (microStep);
    Serial.print  (" myPosition=");
    Serial.print  (myPosition);
    Serial.println  (";");
    printTac=0;
   }
   printTac++;
   ticTac++;
    if (ticTac * microStep >= stepInt){
      digitalWrite(stepPin, HIGH);
      myPosition = myPosition+16/microStep;
      stepInt=stepInt-(stepInt*curAcc);
      if (stepInt < stepIntMin){
        stepInt=stepIntMin;
      }
      if( stepInt > stepIntMax ){
        stepInt=stepIntMax;
      }
      if (stepInt < ms16limit ){ //set MS to 1/16=8+2x4 from 1/inf
        microStep=16;
        if (stepInt < ms8limit ){ //set MS to 1/8=2x4 from 1/16
          microStep=8;
          digitalWrite(ms3Pin, LOW);
          if (stepInt < ms4limit ){ //set MS to 1/4 from 1/8
            microStep=4;
            digitalWrite(ms1Pin, LOW); 
            if (stepInt < ms2limit ){ //set MS to 1/2 from 1/4
              microStep=2;
              digitalWrite(ms1Pin, HIGH);
              digitalWrite(ms2Pin, LOW);
              if (stepInt < mslimit ){ //set MS to 1 from 1/2
                microStep=1;
                digitalWrite(ms1Pin, LOW);
              } else {                //set MS to 1/2 from 1
                microStep=2;
                digitalWrite(ms1Pin, HIGH);
              }
            }else {       //set MS to 1/4 from 1/2
              microStep=4;
              digitalWrite(ms1Pin, LOW);
              digitalWrite(ms2Pin, HIGH);
            }
          } else { //set MS to 1/8 from 1/4
            microStep=8;
            digitalWrite(ms1Pin, HIGH); 
          }
      } else {    //set MS to 1/6=2x4 from 1/8
        microStep=16;
        digitalWrite(ms3Pin, HIGH); 
      }
      ticTac=0;
      digitalWrite(stepPin, LOW);
    }
   }
  }
  delay(1); 
}
