// #include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>
#include "FirebaseESP8266.h"
#include <WiFiManager.h> 

#define WIFI_SSID ""
#define WIFI_PASSWORD ""
#define NUM_LEDS 2

FirebaseData firebaseData;

Adafruit_NeoPixel leds(NUM_LEDS, 2, NEO_GRB + NEO_KHZ800);
// Current color values
int redValue = 0;
int greenValue = 0;
int blueValue = 0;

 // Set web server port number to 80
WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
  //  Serial.begin(9600);
   connectWifi();
  //  leds.begin();
   pinMode(16,OUTPUT);  // Blue led Pin Connected To D0 Pin   
   pinMode(5,OUTPUT);  // Green Led Pin Connected To D1 Pin   
   pinMode(4,OUTPUT);  // Red Led Connected To D2 Pin    

}

void loop() {
  WiFiClient client = server.available();
  /*digitalWrite(16,blueValue); 
  digitalWrite(5,greenValue);  
  digitalWrite(4,redValue);*/


  if (Firebase.getInt(firebaseData, "/red")) {
    if  (firebaseData.dataType() == "int") {
      int val = firebaseData.intData();
      if (val != redValue) {
        redValue = val;
        //  setLedColor();
        digitalWrite(16,blueValue); 
        digitalWrite(5,greenValue);  
        digitalWrite(4,redValue);
      }
    }
  }
  if (Firebase.getInt(firebaseData, "/green")) {
    if  (firebaseData.dataType() == "int") {
      int val = firebaseData.intData();
      if (val != greenValue) {
        greenValue = val;
        // setLedColor();
        digitalWrite(16,blueValue); 
        digitalWrite(5,greenValue);  
        digitalWrite(4,redValue);
      }
    }
  }
  if (Firebase.getInt(firebaseData, "/blue")) {
    if  (firebaseData.dataType() == "int") {
      int val = firebaseData.intData();
      if (val != blueValue) {
        blueValue = val;
        // setLedColor();
        digitalWrite(16,blueValue); 
        digitalWrite(5,greenValue);  
        digitalWrite(4,redValue); 
      }
    }
  }

  if(client) {
  // put your main code here, to run repeatedly:
  



  }

  

  //---for rgb led diode, code starts
  
   // BLUE LED ON  
   /* digitalWrite(16,HIGH);  
    digitalWrite(5,LOW);  
    digitalWrite(4,LOW);  
    delay(500);  
    // GREEN LED ON  
    digitalWrite(16,LOW);  
    digitalWrite(5,HIGH);  
    digitalWrite(4,LOW);  
    delay(500);  
    // RED LED ON  
    digitalWrite(16,LOW);  
    digitalWrite(5,LOW);  
    digitalWrite(4,HIGH);  
    delay(500);  */

  //---rgb led diode, code ends
}


void connectWifi() {
// WiFiManager
  // Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  
  // Uncomment and run it once, if you want to erase all the stored information
  // wifiManager.resetSettings();
  
  // set custom ip for portal
  // wifiManager.setAPStaticIPConfig(IPAddress ip, IPAddress gw, IPAddress sn)
  // wifiManager.setAPIStaticConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));

  // fetches ssid and pass from eeprom and tries to connect
  // if it does not connect it starts an access point with the specified name
  // here  "AutoConnectAP"
  // and goes into a blocking loop awaiting configuration
  wifiManager.autoConnect("AutoConnectAP");
  // or use this for auto generated name ESP + ChipID
  //wifiManager.autoConnect();
  
  // if you get here you have connected to the WiFi
  Serial.println("Connected.");
  
  server.begin();

  Firebase.begin("https://iotdemo-a5feb-default-rtdb.firebaseio.com/", "7UfGXx1ryefwT8u7dXsx1hgLKrqNPWVbDJFYB4sr");

}

void setLedColor() {
  leds.setPixelColor(0,leds.Color(redValue, greenValue, blueValue));

  /*for (int i=0; i < NUM_LEDS; i++) 
    leds.setPixelColor(i, leds.Color(redValue, greenValue, blueValue));*/
   leds.show();
   
}