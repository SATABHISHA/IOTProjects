#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>
#include "FirebaseESP8266.h"
#include <WiFiManager.h>


#define WIFI_SSID ""
#define WIFI_PASSWORD ""
#define NUM_LEDS 2

// Setting RGB pin output
#define LED D6
#define LED D5
#define LED D2
// Declaring LED_STATUS = 0 means LED is OFF
int LED_STATUS = 0;
int RED = 0;
int GREEN = 0;
int BLUE = 0;

FirebaseData firebaseData;
WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
  // pinMode function is used to configure a specific pin to behave as an input or an output
  pinMode(D6, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D2, OUTPUT);
  Serial.begin(9600);

  connectWifi();
}

void loop() {
  // put your main code here, to run repeatedly:
  LED_STATUS = Firebase.getInt(firebaseData, "/status");
  if (LED_STATUS == 0) {
    Serial.print("LED IS OFF");
  } else {
    Serial.println("LED IS ON");

    if (Firebase.getInt(firebaseData, "/red")) {
        if (firebaseData.dataType() == "int") {
          int val = firebaseData.intData();
          if (val != RED) {
            RED = val;
            RGB_color(RED, GREEN, BLUE);
          }
        }
      }

      if (Firebase.getInt(firebaseData, "/green")) {
        if (firebaseData.dataType() == "int") {
          int val = firebaseData.intData();
          if (val != GREEN) {
            GREEN = val;
            RGB_color(RED, GREEN, BLUE);
          }
        }
      }

      if (Firebase.getInt(firebaseData, "/blue")) {
        if (firebaseData.dataType() == "int") {
          int val = firebaseData.intData();
          if (val != BLUE) {
            BLUE = val;
            RGB_color(RED, GREEN, BLUE);
          }
        }
      }
    if (Firebase.getInt(firebaseData, "/customRGBStatus") == 0) {
      
    }

    /*else if (Firebase.getInt(firebaseData, "/customRGBStatus") == 1) {
      //---added on 14th Aug 2023, code starts
      char strRed[] = "", strGreen[] = "", strBlue[] = "";
      
      strRed[1000] = Firebase.getString(firebaseData, "/redArr");
      strGreen[1000] = Firebase.getString(firebaseData, "/greenArr");
      strBlue[1000] = Firebase.getString(firebaseData, "/blueArr");
      int init_sizeRed = strlen(strRed);
      int init_sizeGreen = strlen(strGreen);
      int init_sizeBlue = strlen(strBlue);

      //----get commas count for looping, code starts
      int commaCount = 1;
      for (int c = 0; c < init_sizeRed; c++) {
        if (strRed[c] == ',') {
          commaCount = commaCount + 1;
        }
      }
      //----get commas count for looping, code ends

      int z1 = 0, i1 = 0, i2 = 0, i3 = 0;

      for (int z = z1; z < commaCount; z++) {

        for (int i = i1; i < init_sizeRed; i++) {
          if (strRed[i] == ',') {
            // printf("\n");
            i1 = i + 1;
            z1 = z1 + 1;
            break;
          }
          RED = strRed[i];
          // RGB_color(RED, GREEN, BLUE);
        }
        // printf(" ");
        for (int i = i2; i < init_sizeGreen; i++) {
          if (strGreen[i] == ',') {
            // printf("\n");
            i2 = i + 1;
            break;
          }
      GREEN = strGreen[i];
      // RGB_color(RED, GREEN, BLUE);
      // printf("%c", strGreen[i]);
        }
        // printf(" ");
        for (int i = i3; i < init_sizeBlue; i++) {
          if (strBlue[i] == ',') {
            // printf("\n");
            i3 = i + 1;
            break;
          }
          BLUE = strBlue[i];
          // RGB_color(RED, GREEN, BLUE);
          // printf("%c", strBlue[i]);
        }
        RGB_color(RED, GREEN, BLUE); //---added on 16th August
        delay (1000);
        // printf("\n");
      }

      //---added on 14th Aug 2023, code ends
    }*/
  }
}


void RGB_color(int red_light_value, int green_light_value, int blue_light_value) {
  // analogWrite function is used to pass values to specific pin
  // In our example it will pass RGB value to D6, D5 & D2 pins respectively
  analogWrite(D6, red_light_value);
  analogWrite(D5, green_light_value);
  analogWrite(D2, blue_light_value);
}


void connectWifi() {
  // WiFiManager
  // Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;

  // Uncomment and run it once, if you want to erase all the stored information
  wifiManager.resetSettings();

  // set custom ip for portal
  // wifiManager.setAPStaticIPConfig(IPAddress ip, IPAddress gw, IPAddress sn)
  // wifiManager.setAPIStaticConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));

  // fetches ssid and pass from eeprom and tries to connect
  // if it does not connect it starts an access point with the specified name
  // here  "AutoConnectAP"
  // and goes into a blocking loop awaiting configuration
  wifiManager.autoConnect("SatabhishaIOTWifi");
  // or use this for auto generated name ESP + ChipID
  //wifiManager.autoConnect();

  // if you get here you have connected to the WiFi
  Serial.println("Connected.");

  server.begin();

  Firebase.begin("https://iotdemo-a5feb-default-rtdb.firebaseio.com/", "7UfGXx1ryefwT8u7dXsx1hgLKrqNPWVbDJFYB4sr");
}