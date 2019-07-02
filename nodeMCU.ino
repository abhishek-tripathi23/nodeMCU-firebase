#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>

#include <ESP8266WiFi.h>                                                    // esp8266 library
#include <FirebaseArduino.h>                                                // firebase library

#define FIREBASE_HOST "firebase name"                          // the project name address from firebase id
#define FIREBASE_AUTH "******"            // the secret key generated from firebase

#define WIFI_SSID "wifi name"                                             // input your home or public wifi name 
#define WIFI_PASSWORD "*****"                                    //password of wifi ssid
#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11   // DHT 11

#define dht_dpin 0
DHT dht(dht_dpin, DHTTYPE); 
void setup(void)
{ 
  Serial.begin(9600);
  dht.begin();
  delay(700);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                              // connect to firebase

  
}

int n= 0;

void loop() {
    float h = dht.readHumidity();
    float t = dht.readTemperature();     
    Serial.print("Current humidity = ");
    Serial.print(h);
    Serial.print("%  ");
    String fireHumid = String(h) + String("%"); 
    Serial.print("temperature = ");
    Serial.print(t); 
    Serial.println("C  ");
    String fireTemp = String(t) + String("Â°C");   
    delay(700);

    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    root["temperature"] = t;
    root["humidity"] = h;
    
    if (!isnan(h) && !isnan(t)) {
    String name = Firebase.push("/dht", root);
    }
    delay(4000);
}
