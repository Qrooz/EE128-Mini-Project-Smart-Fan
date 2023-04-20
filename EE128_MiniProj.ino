// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, modified for integer use, public domain

#include "TinyDHT.h"

#define DHTPIN 2  // DHT connected to Arduino Uno Digital Pin 2

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

//PIN ASSIGNEMNT
/*PIN 2 input from PIR sensor
 * PIN3 input from Temperature sensor
 * PIN 4 Output signal for PIR sensor
 * pin 5 output for temp sensor slow < 25
 * pin 6 output for temp sensor medium  25 =< x =< 27
 * pin 7 output for temp sensor high > 27
 * 
 */ 

int PIR_sig = LOW;
int motion = 0;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); // Output status on Uno serial monitor
  Serial.println("DHTxx test!");


  pinMode(3,INPUT); // PIR sensor input pin
  pinMode(4,OUTPUT); //Motion detection output
  pinMode(5,OUTPUT); //slow speed output
  pinMode(6,OUTPUT); //med speed output
  pinMode(7,OUTPUT); //fast speed output
  Serial.begin(9600);
 
  dht.begin();
}

void loop() {
  // TEMPERATURE SENSOR
  int8_t h = dht.readHumidity();
  int16_t t = dht.readTemperature(0);

  // check if returns are valid then something went wrong!
  if ( t == BAD_TEMP || h == BAD_HUM ) { // if error conditions          
    Serial.println("Failed to read from DHT");
  } else {
    Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.println(" *C");
  }

  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);

  if(t < 24){ //set slow signal
     digitalWrite(5, HIGH);
  }
  else if(t >= 24 && t <= 26){ //set medium signal
     digitalWrite(6, HIGH);
  }
  else if (t > 26){ //set high signal
    digitalWrite(7, HIGH);
  }

   //PIR SENSOR
   PIR_sig = digitalRead(3);

  if(PIR_sig == HIGH){
    Serial.println("Motion detected!"); 
    digitalWrite(4,HIGH);
  }
  else{
    Serial.println("Nothing");
    digitalWrite(4,LOW); 
  }

  PIR_sig = LOW;
  
  delay(500);
}
