#include <Arduino.h>

void setup() {
  pinMode(D4, OUTPUT);
  pinMode(D1, INPUT);

}

void loop() { 
   

  if(digitalRead(D1) == LOW){
    digitalWrite(D4, HIGH); 
  }else{  
    digitalWrite(D4, LOW);
  }


}