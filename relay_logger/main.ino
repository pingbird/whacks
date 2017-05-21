#include <NewPing.h>
#define TRIGGER_PIN 10
#define ECHO_PIN 9
#define MAX_DISTANCE 200
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
void setup() {
  Serial.begin(9600);
}

void loop() {
   delay(50);
unsigned int uS = sonar.ping();
pinMode(ECHO_PIN,OUTPUT);
digitalWrite(ECHO_PIN,LOW);
pinMode(ECHO_PIN,INPUT);
int val = (uS / US_ROUNDTRIP_CM);
Serial.print("\42\69");
 Serial.print(val);
 Serial.print(";");

}
