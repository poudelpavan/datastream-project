#include <DHT.h>

#include "DHT.h"

#define DHTPIN 2     // what pin we're connected to

#define DHTTYPE DHT11   // we are using the DHT11 sensor

DHT dht(DHTPIN, DHTTYPE);

#define DC_MOTOR_PIN 1

const int led=6;

void setup() {
  /* Initialize DC motor control pin as digital output */
  pinMode( DC_MOTOR_PIN, OUTPUT );
  pinMode(led, OUTPUT);

  for (int DigitalPin = 3; DigitalPin <= 5; DigitalPin++) 
  {
    pinMode(DigitalPin, OUTPUT);
  }
  dht.begin();
  //Serial.begin(9600);
  //Serial.setTimeout(1000);
}

void loop() {
/*Control light*/
  int sensor_value = analogRead(A0);
  Serial.println(sensor_value);
  if (sensor_value < 150)// the point at which the state of LEDs change 
    { 
      digitalWrite(led, HIGH);  //sets LEDs ON
    }
  else
    {
      digitalWrite(led,LOW);  //Sets LEDs OFF
    }

  delay(1000);
  // Reading temperature or humidity takes about 250 milliseconds!
  float h = dht.readHumidity();
  
  float t = dht.readTemperature();  // Read temperature as Celsius (the default)

  Serial.println(t);
  
//the 3-led setup process
  if (t<=20)
  {
  digitalWrite(5, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);

  digitalWrite( DC_MOTOR_PIN, 0 );
  Serial.println(analogRead(DC_MOTOR_PIN));
  }
  else if (t>20)
  {
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(3, LOW);

  digitalWrite( DC_MOTOR_PIN, 1 );
  }
  else if (t>=30)
  {
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  
  digitalWrite( DC_MOTOR_PIN, 255 );
  }   
}
  
