#include <Arduino.h>

#include <Servo.h>

Servo myservo;


int buttonState = 0;
int val = 0;

void setup() {
  pinMode(D4, OUTPUT);
  pinMode(D2, INPUT_PULLUP);

  myservo.attach(D4);
 
}

void loop() { 
   
   //buttonState = digitalRead(D2);

  val = map(90, 0, 1023, 20, 120); 
  myservo.write(val);              
  delay(5);   

  val = map(180, 0, 1023, 20, 120); 
  myservo.write(val);              
  delay(5);   

   //if (buttonState == LOW) {
 //   digitalWrite(D4, HIGH); 
 // }else{  
//    digitalWrite(D4, LOW);
//  }

}