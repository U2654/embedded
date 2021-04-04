#include <Arduino.h>
#include <HardwareSerial.h>

#define REDV_LED 13

void setup() {
  pinMode(REDV_LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println("Next\n");
  digitalWrite(REDV_LED, HIGH);
  delay(500);                     
  digitalWrite(REDV_LED, LOW); 
  delay(500);                 
}
