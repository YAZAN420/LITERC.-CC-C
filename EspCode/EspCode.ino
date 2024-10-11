#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
const char* ssid = "lolia"; 
const char* password = "11111111";
ESP8266WebServer server(80); 
int x=0,y=0,dif=40,mode=-1;
int echoPin=D7;
int trigPin=D8;
int duration,distance;
int speedmove,speedturn;
int Motor1pin1=D1,Motor1pin2=D2,Motor2pin1=D3,Motor2pin2=D4,SpeedRight=D5,speedLeft=D6;
void setup() {
  pinMode(Motor1pin1,OUTPUT);
  pinMode(Motor1pin2,OUTPUT);
  pinMode(Motor2pin1,OUTPUT);
  pinMode(Motor2pin2,OUTPUT);
  pinMode(SpeedRight,OUTPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  analogWrite(SpeedRight,100);
  analogWrite(speedLeft,100);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println(WiFi.localIP());
  server.on("/mode", HTTP_POST, []() {
    if (server.hasArg("plain")) {  
      String body = server.arg("plain");
      StaticJsonDocument<200> doc;
      DeserializationError error = deserializeJson(doc, body);
      JsonArray array = doc.as<JsonArray>();
      mode=int(array[0]);
      server.send(200, "application/json", "{\"status\":\"Mode received\"}");
    }
  });
  server.on("/array", HTTP_POST, []() {
    if (server.hasArg("plain")) {  
      String body = server.arg("plain");
      StaticJsonDocument<200> doc;
      DeserializationError error = deserializeJson(doc, body);
      JsonArray array = doc.as<JsonArray>();
      x=int(array[0]);
      y=int(array[1]); 
      server.send(200, "application/json", "{\"status\":\"Array received\"}");
    }
  });
  server.begin(); 
  Serial.println("HTTP server started");
}
void loop() {
    server.handleClient();
    digitalWrite(trigPin,LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin,LOW);
    duration=pulseIn(echoPin,HIGH);
    distance=duration*0.034/2;
    if(mode==1){
      if(y>10){
            speedmove=map(y,0,180,0,200);
            analogWrite(SpeedRight,speedmove);
            analogWrite(speedLeft,speedmove);
            digitalWrite(Motor1pin1,HIGH);
            digitalWrite(Motor1pin2,LOW);
            digitalWrite(Motor2pin1,HIGH);
            digitalWrite(Motor2pin2,LOW);
      }else if(x<dif&&x>-1*dif&&y>-1*dif&&y<dif){
            digitalWrite(Motor1pin1,LOW);
            digitalWrite(Motor1pin2,LOW);
            digitalWrite(Motor2pin1,LOW);
            digitalWrite(Motor2pin2,LOW);
            x=0;y=0;
      }else if(x>=dif){
            speedmove=map(x,0,180,0,200);
            analogWrite(SpeedRight,speedmove);
            analogWrite(speedLeft,speedmove);
            digitalWrite(Motor1pin1,HIGH);
            digitalWrite(Motor1pin2,LOW);
            digitalWrite(Motor2pin1,LOW);
            digitalWrite(Motor2pin2,HIGH);
      }else if(x<=-1*dif){
            speedmove=map(x,0,-65,0,200);
            analogWrite(SpeedRight,speedmove);
            analogWrite(speedLeft,speedmove);
            digitalWrite(Motor1pin1,LOW);
            digitalWrite(Motor1pin2,HIGH);
            digitalWrite(Motor2pin1,HIGH);
            digitalWrite(Motor2pin2,LOW);
      }else if(y<-1*dif){
            speedmove=map(y,0,-90,0,200);
            analogWrite(SpeedRight,speedmove);
            analogWrite(speedLeft,speedmove);
            digitalWrite(Motor1pin1,LOW);
            digitalWrite(Motor1pin2,HIGH);
            digitalWrite(Motor2pin1,LOW);
            digitalWrite(Motor2pin2,HIGH);
      }
    }else if(mode==2){
            if(distance>40){
                    digitalWrite(Motor1pin1,LOW);
                    digitalWrite(Motor1pin2,HIGH);
                    digitalWrite(Motor2pin1,LOW);
                    digitalWrite(Motor2pin2,HIGH);
            }else{
                    digitalWrite(Motor1pin1,LOW);
                    digitalWrite(Motor1pin2,HIGH);
                    digitalWrite(Motor2pin1,HIGH);
                    digitalWrite(Motor2pin2,LOW);
            }
            Serial.println(distance);
    }
}
