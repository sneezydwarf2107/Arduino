#include <Servo.h> 
 
Servo servo;  // create servo object 
 
unsigned long startzeit;
unsigned long messzeit = 100000; // Messintervall in Mikrosekunden
int val = 25;
 
void setup(){
  Serial.begin(9600);
  startzeit = micros();
  servo.attach(6);
  servo.write(25); //Wird zum Initialisieren des ESC  benötigt
  delay(2000);
  //servo.write(40); 
}
 
void loop(){
  if ((micros()- startzeit) >= messzeit){
    servo.write(val);
    Serial.println(val);
    startzeit = micros();
  }  
  val = map(analogRead(A0), 0, 1023, 30, 110);
  servo.write(val);
 
}
