#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>
#define PIN D1
#define NUM_LEDS 2

const char* ssid = "ARB Mac mini";
const char* password = "$@ltL@keCovid12Jan";
FirebaseData firebaseData;

Adafruit_NeoPixel leds(NUM_LEDS, 2, NEO_GRB + NEO_KHZ800);
// Current color values
int redValue = 0;
int greenValue = 0;
int blueValue = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  connectWifi();
  leds.begin();
  
  Firebase.begin("https://iotdemo-a5feb-default-rtdb.firebaseio.com/", "7UfGXx1ryefwT8u7dXsx1hgLKrqNPWVbDJFYB4sr");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Firebase.getInt(firebaseData, "/red")) {
    if  (firebaseData.dataType() == "int") {
      int val = firebaseData.intData();
      if (val != redValue) {
        redValue = val;
         setLedColor();
      }
    }
  }
  if (Firebase.getInt(firebaseData, "/green")) {
    if  (firebaseData.dataType() == "int") {
      int val = firebaseData.intData();
      if (val != greenValue) {
        greenValue = val;
        setLedColor();
      }
    }
  }
  if (Firebase.getInt(firebaseData, "/blue")) {
    if  (firebaseData.dataType() == "int") {
      int val = firebaseData.intData();
      if (val != blueValue) {
        blueValue = val;
        setLedColor();
      }
    }
  }

}

void connectWifi() {
  // Let us connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(".......");
  Serial.println("WiFi Connected....IP Address:");
  Serial.println(WiFi.localIP());
}

void setLedColor() {
  leds.setPixelColor(0,leds.Color(redValue, greenValue, blueValue));

  /*for (int i=0; i < NUM_LEDS; i++) 
    leds.setPixelColor(i, leds.Color(redValue, greenValue, blueValue));*/
   leds.show();
   
}
