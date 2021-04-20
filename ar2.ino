#include <Adafruit_NeoPixel.h> //library pt LEDuri

#define RED   4
#define BLUE  3
#define GREEN 2
#define GAS   A3
#define LEDs 4 
//constanta care defineste nr de led-uri a benzii
#define DIN 8 
//intrarea care controleaza banda

int sensorValue = 0;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(LEDs, DIN); 
//instantiere banda cu 4 led-uri controlata de pinul 8
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12,6, NEO_GRB + NEO_KHZ800);

int rValue = 0; 
int gValue = 0; 
int bValue = 0; 
float distance = 0; 
unsigned int buzzer = 11; 
unsigned int rePin = 5; //switch
unsigned int valorRe = HIGH;
unsigned int ledPin = 13;
int valtemp;
int maxled;

void setup()
{
  pinMode(A0, INPUT);
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(A1, INPUT);
  pinMode(A3, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(4, HIGH);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(GAS, INPUT);
  strip.begin();
  pixels.begin(); 
  pinMode(buzzer, OUTPUT); 
  pinMode(5, INPUT_PULLUP); 
  pinMode(ledPin, OUTPUT); 
}

//functie de trimitere si primire puls de la ultrasonic
long readUltrasonicDistance(int triggerPin, int echoPin) 
{
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}
void loop()
{
  //****SENZOR FOTOREZISTOR****
  //se cieste val de la sensorul fotorezistor
  sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  //se mapeaza valoarea citita de la senzor pe led-uri
  analogWrite(9, map(sensorValue, 0, 1023, 0, 255));
  delay(100);
 
  //****SENZOR DE GAZ****
  //se citeste valoarea de la pinul conectat la senzor 
  //in functie de valoarea citita, se vor aprinde led-urile
  //verde=nu este gaz  ; galben=cantitate mica de gaz
  //rosu=cantitate ft mare de gaz
  int value = analogRead(GAS);
  Serial.println(value);
  if (value < 100) {
    digitalWrite(RED,   LOW);
    digitalWrite(BLUE,  LOW);
    digitalWrite(GREEN, HIGH);
  }
  else if (value < 300) {
    digitalWrite(RED,   HIGH);
    digitalWrite(BLUE,  LOW);
    digitalWrite(GREEN, HIGH);
  }
  else {
    digitalWrite(RED,   HIGH);
    digitalWrite(BLUE,  LOW);
    digitalWrite(GREEN, LOW);
  }
  
  //***SENZOR ULTRASONIC+BUZZER+NEOPIXEL 4****
  valorRe = digitalRead(rePin); 
  if (valorRe == LOW) 
  {//se calculeaza valoarea distantei
    digitalWrite(ledPin, HIGH); //ativa o built-in LED
    distance = 0.01723 * readUltrasonicDistance(7, 7); 
    //daca distanta e mai mica de 35 cm, se va activa buzzerul
    //la o frecv de 1000Hz pt 100ms si se va dezactiva dupa 100ms
    //si toate ledurile se vor colora rosu
    if (distance <= 35.0) 
    {
      tone(buzzer, 1000, 100); 
      delay(100); 
      for (int i=0; i < LEDs; i++) 
      {
        pixels.setPixelColor(i, pixels.Color(255, 0, 0));
        pixels.show(); 
      }
    }
    //daca distanta e mai mica de 100 cm, se va activa buzzerul
    //la o frecv de 1000Hz pt 100ms si se va dezactiva dupa 200ms
    //si toate ledurile se vor colora galben
    else if (distance <= 100.0) 
    {
      tone(buzzer, 1000, 100); 
      delay(200); 
      for (int i=0; i < LEDs; i++) 
      {
        pixels.setPixelColor(i, pixels.Color(255, 255, 0));
        pixels.show(); 
      }
    }
    //daca distanta e mai mica de 165 cm, se va activa buzzerul
    //la o frecv de 1000Hz pt 100ms si se va dezactiva dupa 400ms
    //si toate ledurile se vor colora verde
    else if (distance <= 165.0) 
    {
      tone(buzzer, 1000, 100); 
      delay(400); 
      for (int i=0; i < LEDs; i++) 
      {
        pixels.setPixelColor(i, pixels.Color(0, 128, 0));
        pixels.show();
      }
    }
    //daca obiectul se afla la o distanta mai mare de 165 cm
    //toate ledurile vor fi verzi
    else 
    {
      for (int i=0; i < LEDs; i++) 
      {
        pixels.setPixelColor(i, pixels.Color(0, 128, 0)); 
        pixels.show(); 
      } 
    }
  }
 
  
  valtemp = analogRead(A5);
  maxled= valtemp*12/358; //ultimul led ce se poate aprinde
 //se citeste valoare temperaturii, si in functie de aceasta se aprind/sting un nr de leduri
  for (int i=0; i<12; i++){
    if(i<=maxled){
      strip.setPixelColor(i,255,0,0); //rosu
    }else{
      strip.setPixelColor(i,0,0,0); //se sting
    }
  }
  strip.show();
}
