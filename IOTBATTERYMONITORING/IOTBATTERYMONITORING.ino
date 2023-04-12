// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPLvJzAlw-c"
#define BLYNK_TEMPLATE_NAME "Battery monitoring system"
#define BLYNK_AUTH_TOKEN "Q3oHwYdmWfYfAIX4M-WG-a0-KlgIkbM9"


// Comment this out to disable prints and save space

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>

#include <WiFiClient.h>

#include <BlynkSimpleEsp8266.h>

float voltage;

int bat_percentage;

int analogInPin = A0; // Analog input pin

int sensorValue;

// Check Battery voltage using multimeter & add/subtract the value

float calibration = 0.36; 

// Your WiFi credentials.

// Set password to "" for open networks.

char ssid[] = "iMaK";

char pass[] = "gate@024";

char auth[] = BLYNK_AUTH_TOKEN;

void setup()

{

  pinMode(analogInPin, INPUT);

  // Debug console

  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);

}

void loop()

{

  Blynk.run();

  sensorValue = analogRead(analogInPin);

  // Multiply by two as voltage divider network is 100K & 100K Resistor

  voltage = (((sensorValue * 3.3) / 1024) * 2 - calibration); 

  // 2.8V as Battery Cut off Voltage & 4.2V as Maximum Voltage

  bat_percentage = map(voltage, 2.8, 4.2, 0, 100); 

  if (bat_percentage >= 100)

  {

    bat_percentage = 100;

  }

  if (bat_percentage <= 0)

  {

    bat_percentage = 1;

  }

  //send data to blynk

  Blynk.virtualWrite(V0, voltage);  // for battery voltage

  Blynk.virtualWrite(V1, bat_percentage);  // for battery percentage

  Serial.print("Analog Value = ");

  Serial.println(sensorValue);

  Serial.print("Output Voltage = ");

  Serial.println(voltage);

  Serial.print("Battery Percentage = ");

  Serial.println(bat_percentage);

  Serial.println();

  Serial.println("****************************");

  Serial.println();

  delay(1000);

}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)

{

  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;

}
