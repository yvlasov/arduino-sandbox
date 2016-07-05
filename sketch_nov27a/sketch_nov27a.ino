//#include <Arduino.h>
#include <SoftwareSerial.h>
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("This software is a part of research project\n\rdesigned by Yuri S. Vlasov <yv@pytn.ru> \n\rin St-Petersburg Polytechnic University\n\rStarting ...\n\r");
  unsigned int i =0;
}

unsigned int i=0;

void loop() {
  // put your main code here, to run repeatedly:
  float data;
  float T =0.1; //Period T
  data=sin(T*i);
  Serial.print("DATA=");
  Serial.print(data);
  Serial.print("\n\r");
  i++;
  delay(500);
}

