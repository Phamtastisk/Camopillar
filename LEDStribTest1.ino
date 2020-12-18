#include <FastLED.h>

#define LED_PIN 10
#define NUM_LEDS 11

// IR sensor
#define signal_pin 2

#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

int frequencyR = 0;
int frequencyG = 0;
int frequencyB = 0;


//int redColor = 0;
//int greenColor = 0;
//int blueColor = 0;

CRGB leds[NUM_LEDS];


void setup() {
FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Setting frequency-scaling to 20%

  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  // IR sensor
  pinMode(signal_pin, INPUT);
  
  Serial.begin(9600);
}




void loop() {

// IR sensoor
  if(digitalRead(signal_pin) == HIGH){
      Serial.println("Movement detected."); 
      //Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  // Reading the output frequency 
  frequencyR = pulseIn(sensorOut, LOW);
  //Remap 

frequencyR = map(frequencyR, 41,89, 255, 0);
if(frequencyR <= 0){
  frequencyR = 0;
  }
  else if(frequencyR >= 255){
  frequencyR = 255;
  frequencyG = 1;
  frequencyB = 1;
  }

  //Printing the value on the serial monitor
  Serial.print("R= ");//printing name 
  Serial.print(frequencyR);//printing RED color frequency  
  Serial.print(" ");

  delay(100);


  //Setting green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);

  // Reading the output frequency 
  frequencyG = pulseIn(sensorOut, LOW);
  //Remap 
frequencyG = map(frequencyG, 58,185, 255, 0);
  //Printing the value on the serial monitor
if(frequencyG <= 0){
  frequencyG = 0;
  }
    else if(frequencyG >= 255){
  frequencyG = 255;
  frequencyR = 0;
  frequencyB = 0;
  }
  Serial.print("G= ");//printing name 
  Serial.print(frequencyG);//printing RED color frequency  
  Serial.print(" ");

  delay(100);


  //Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

  // Reading the output frequency 
  frequencyB = pulseIn(sensorOut, LOW);
  //Remap 
frequencyB = map(frequencyB, 20,50, 255, 0);
//frequencyB = map(frequencyB, 20,100, 255, 0);

  //Printing the value on the serial monitor
if(frequencyB <= 0){
  frequencyB = 0;
  }
    else if(frequencyB >= 255){
  frequencyB = 255;
  frequencyR = 0;
  frequencyG = 0;
  }
  Serial.print("B= ");//printing name 
  Serial.print(frequencyB);//printing RED color frequency  
  Serial.println(" ");

  delay(100);



for (int i = 0; i <= 10; i++){
  leds[i] = CRGB(frequencyR,frequencyG,frequencyB);
  FastLED.show();
  delay(40);
  }
    }

    
    else{
      Serial.println("Did not detect any movement.");

for (int i = 0; i <= 10; i++){
  leds[i] = CRGB(0,0,0);
  FastLED.show();
  delay(40);
  }
      }
      delay(1000);



}
