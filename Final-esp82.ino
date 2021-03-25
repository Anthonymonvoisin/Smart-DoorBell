#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "OnePlus6"; // Enter your WiFi name
const char* password =  "OnePlus6"; // Enter WiFi password
const char* mqttServer = "iot.fr-par.scw.cloud";
const int mqttPort = 1883;
const char* mqttUser = "7e5d985b-4c63-443c-84e6-acb3456d39b6";
const char* mqttPassword = "";
const char* topic_PHOTO = "SMILE";
const char* topic_UP = "PICTURE";
const char* topic_FLASH = "FLASH";

WiFiClient espClient;
PubSubClient client(espClient);
#include <Keypad.h>
 
const byte n_rows = 4;
const byte n_cols = 4;
 int number = 0; 
 char nombre [5];
 
char keys[n_rows][n_cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
 
byte colPins[n_rows] = {D3, D2, D1, D0};
byte rowPins[n_cols] = {D7, D6, D5, D4};
 
Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, n_rows, n_cols);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
      Serial.println("connected"); 
    } else {

      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
}
int longueur;
     char myKey[3];

  for (int i = 0; i <3; i++){
    char tmp = myKeypad.waitForKey();
    
     if(tmp != 'A'){
      myKey[i] = tmp;
     }
     else{
      Serial.println("Keys pressed :");
      int lengthChar = i;
      char nombre[lengthChar];
      
      for (i = 0; i < lengthChar; i++){
                number = number + (myKey[i] - 48) * pow(10,lengthChar - i -1); //Technique de schlag mettre le 48 mdr
        nombre[i]=myKey[i];
      }
    }}
      Serial.print("number =");
      Serial.println(number);
      if (number!=NULL){
      sendmqtt();
      }


}
  

void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}

void sendmqtt(){
    Serial.println("Sending payload");
  client.publish("SMILE", "SMILE"); //Topic name
  Serial.println("Payload sent!");
  client.subscribe(topic_PHOTO);
}

void loop() {
  client.loop();
}
