
#include <Servo.h>

Servo myservo1;  

int p = 0;   

void setup() {
  myservo1.attach(6); 
}

void loop() {
  for (p = 45; p <= 145; p += 1) {
    myservo1.write(p);              
    delay(15);                       
  }
  for (p = 145; p >= 45; p -= 1) { 
    myservo1.write(p);              
    delay(15);                      
  }
}

