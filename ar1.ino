//motor 1
#define motor00 5
#define motor01 6
//motor 2
#define motor10 3
#define motor11 11

#define servo_pin 8

#include <Servo.h>
Servo srv;
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 10, 9, 4 ,2);

const int ping_pin = 7;
int distance;
int position=0;
int duration = 0;

//functie determinare distanta de la PING))
int getDistance(){
 
int distance;
unsigned long duration=0;
pinMode(ping_pin, OUTPUT);
digitalWrite(ping_pin, LOW);
delayMicroseconds(5);
digitalWrite(ping_pin, HIGH);
delayMicroseconds(5);
digitalWrite(ping_pin, LOW); 
pinMode(ping_pin, INPUT);
duration=pulseIn(ping_pin, HIGH);
//viteza sunetului este 340 m/s sau 29 microsec/cm
//semnalul calatoreste inainte si inapoi
//ca sa aflam distanta pana la obiect
//impartim distanta parcusa la 2
distance = int(duration/29/2);
return distance;
  
}
//functie mers inainte motoare
void goForward(){
 lcd.setCursor(0,0);
 lcd.print("FREE ROAD");
 lcd.setCursor(0,1);
 lcd.print("GO FORWARD");
 digitalWrite(A0, HIGH);
 delay(70);
 digitalWrite(A0, LOW);
 delay(70);
 digitalWrite(A0, HIGH);
 delay(70);
 digitalWrite(A0, LOW);
 delay(70);
 digitalWrite(motor00, HIGH);
 digitalWrite(motor01, LOW);
 digitalWrite(motor10, HIGH);
 digitalWrite(motor11, LOW);
}
                  
                  
//functie mers inapoi motoare
void goBackward(){
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("GOING BACK");
 lcd.setCursor(0,1);
 lcd.print(distance);
 lcd.setCursor(3,1);
 lcd.print("cm");
 digitalWrite(A1, HIGH);
 delay(70);
 digitalWrite(A1, LOW);
 delay(70);
 digitalWrite(A1, LOW);delay(70);
 digitalWrite(A1, HIGH);delay(70);
 digitalWrite(motor00,LOW);
 digitalWrite(motor01, HIGH);
 digitalWrite(motor10, LOW);
 digitalWrite(motor11, HIGH);
}
//functie mers la stanga motoare
void goLeft(){ 
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("TURNING LEFT");
 lcd.setCursor(0,1);
 lcd.print(distance);
 lcd.setCursor(3,1);
 lcd.print("cm");  
 digitalWrite(A3, HIGH);
 delay(70);
 digitalWrite(A3, LOW);
 delay(70);
 digitalWrite(A3, HIGH);
 delay(70);
 digitalWrite(A3, LOW);
 delay(70);
 digitalWrite(motor00, HIGH);
 digitalWrite(motor01, LOW);
 delay(70);
 digitalWrite(motor10, LOW);
 digitalWrite(motor11, HIGH);
 delay(70);
}
//functie mers la dreapta motoare
void goRight(){
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("TURNING RIGHT");
 lcd.setCursor(0,1);
 lcd.print(distance);
 lcd.setCursor(3,1);
 lcd.print("cm");  
 digitalWrite(A2, HIGH);
 delay(70);
 digitalWrite(A2, LOW);
 delay(70);
 digitalWrite(A2, HIGH);
 delay(70);
 digitalWrite(A2, LOW);
 delay(70);
 digitalWrite(motor00,LOW);
 digitalWrite(motor01,HIGH);
 delay(70);
 digitalWrite(motor10,HIGH);
 digitalWrite(motor11, LOW);
 delay(70);  
}
//functie oprire motoare
void stop(){
 lcd.clear(); 
 lcd.setCursor(0,0);
 lcd.print("SMTH IN FRONT");
 lcd.setCursor(0,1);
 lcd.print("STOP-AVOID OBST"); 
 digitalWrite(A4, HIGH);
 delay(70);
 digitalWrite(A4, LOW);
 delay(70);
 digitalWrite(A4, HIGH);
 delay(70);
 digitalWrite(A4, LOW);
 delay(70);
 digitalWrite(motor00,LOW);
 digitalWrite(motor01,LOW);
 delay(70);
 digitalWrite(motor10, LOW);
 digitalWrite(motor11, LOW);
 delay(70);
}
// Utilizare servo
// Pozitionare in trei unghiuri
// La final, ramane in mijloc (90 grade) 
void playWithServo(int pin){
 srv.attach(pin);
 srv.write(0);
 goLeft();
 delay(70);
 srv.write(90);
 goLeft();
 delay(70);
 srv.write(180);
 goRight();
 delay(70);
 srv.write(90);
 goRight();
 delay(70);
 srv.detach();
} 

void setup() {
  Serial.begin(9600);
  srv.attach(8);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(11, OUTPUT);
  lcd.begin(16, 2);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A5, INPUT); 
}

void loop() {
 Serial.print(distance);
 srv.write(90);
 distance = int (getDistance());
 Serial.print(distance);
 
  while(distance >50 ) {
   goForward();
   distance=getDistance(); 
  }
  
 while(distance <= 50){
  stop();
  delay(70);
  goBackward(); 
  delay(70);
  goLeft();
  delay(70);
  goForward();
  srv.write(position);
  position+=50;
  if(position == 225)
     position = 0;
  distance=getDistance();
  // Pornirea motorului Servo 
  playWithServo(8); 
}  
 
}
