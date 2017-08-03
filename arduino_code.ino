#include <DHT.h>
#include "DHT.h"

#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT11   // we are using the DHT11 sensor

DHT dht(DHTPIN, DHTTYPE);

#define DC_MOTOR_PIN 1

const int LED_PIN=6;
const int g_pin = 5, y_pin = 4, r_pin = 3;

void setup() {
  /* Initialize DC motor control pin as digital output */
  pinMode( DC_MOTOR_PIN, OUTPUT );
  pinMode(LED_PIN, OUTPUT);
  pinMode(g_pin, OUTPUT);
  pinMode(y_pin, OUTPUT);
  pinMode(r_pin, OUTPUT);

  dht.begin();
  
  //Serial.begin(9600);
  //Serial.setTimeout(1000);
}

void loop() {
/*Control light*/
  int sensor_value = analogRead(A0);
  //Serial.println(sensor_value);
  if (sensor_value < 150)// the point at which the state of LEDs change 
    { 
      digitalWrite(LED_PIN, HIGH);  //sets LEDs ON
    }
  else
    {
      digitalWrite(LED_PIN,LOW);  //Sets LEDs OFF
    }

  // Reading temperature or humidity takes about 250 milliseconds!
  float h = dht.readHumidity();
  
  float t = dht.readTemperature();  // Read temperature as Celsius (the default)

  Serial.println(t);
  
//the 3-led setup process
  if (t<=20)
  {
  digitalWrite(g_pin, HIGH);
  digitalWrite(y_pin, LOW);
  digitalWrite(r_pin, LOW);

  digitalWrite( DC_MOTOR_PIN, 0 );
  Serial.println(analogRead(DC_MOTOR_PIN));
  }
  else if (t>20)
  {
  digitalWrite(y_pin, HIGH);
  digitalWrite(g_pin, LOW);
  digitalWrite(r_pin, LOW);

  digitalWrite( DC_MOTOR_PIN, 1 );
  }
  else if (t>=30)
  {
  digitalWrite(r_pin, HIGH);
  digitalWrite(y_pin, LOW);
  digitalWrite(g_pin, LOW);
  
  digitalWrite( DC_MOTOR_PIN, 255 );
  }
  
  delay(1000);
}
  
