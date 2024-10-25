#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include <LiquidCrystal_I2C.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"


// Insert your network credentials
#define WIFI_SSID ""
#define WIFI_PASSWORD ""//Mettre mot de passe Ici

// Insert Firebase project API Key
#define API_KEY ""

String serverName = "heroku";


// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL ".firebaseio.com/" 

//Define Firebase Data object
FirebaseData fbdo;
LiquidCrystal_I2C lcd(0x27, 16, 2);
FirebaseAuth auth;
FirebaseConfig config;



unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;
bool boolValue;

void setup(){
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
        String requeteCompteur = httpGETRequest(serverName + "/api/compteur");
      JSONVar monCompteur = JSON.parse(requeteCompteur);
      int compteur = monCompteur["data"]["compteur"];
      Serial.println(compteur);
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Compteur: ");
      lcd.setCursor(0, 1);
      lcd.print(compteur);
      Firebase.RTDB.setBool(&fbdo, "modifier", false);
}

void loop(){
  while (Firebase.ready() ){
    if (Firebase.RTDB.getBool(&fbdo, "modifier")) {

    boolValue = fbdo.boolData();


      if (boolValue==true) {
      String requeteCompteur = httpGETRequest(serverName + "/api/compteur");
      JSONVar monCompteur = JSON.parse(requeteCompteur);
      int compteur = monCompteur["data"]["compteur"];
      Serial.println(compteur);
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Compteur: ");
      lcd.setCursor(0, 1);
      lcd.print(compteur);
      Firebase.RTDB.setBool(&fbdo, "modifier", false);
    }
    else{
        Serial.println("boom");

    }
  
}

    else{
        Serial.println("rereboom");

    }
    
    // Write an Float number on the database path test/float
    
  }

    

}

String httpGETRequest(String serverName) {
  HTTPClient http;
  http.begin(serverName);
  int httpResponseCode = http.GET();
  String payload = "{}"; 
  if (httpResponseCode > 0) {
    Serial.print("Code de réponse HTTP : ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  } else {
    Serial.print("Code d'erreur : ");
    Serial.println(httpResponseCode);
  }
  http.end();
  return payload;
}
