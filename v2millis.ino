//https://github.com/Aufazahron/MotorListrik
//Create By Azrn <3
byte sda = 10;
byte rst = 9;

#include<KRrfid.h>
#include<ezButton.h>

ezButton standar(4);

unsigned long serv=millis();
unsigned long times=millis();


const int BUTTON_PIN=7;  
const int RELAY_PIN=3;
const int kontak=2;
const int slnida=5;
const int slnidb=6;

int relayState = LOW;     
int lastButtonState;    
int currentButtonState;
int woe = LOW;
int RFID = HIGH;

void setup() {
  Serial.begin(115200);
  rfidBegin();
  standar.setDebounceTime(50);
  digitalWrite(RELAY_PIN,HIGH);
  pinMode(slnida,OUTPUT);
  pinMode(slnidb,OUTPUT);
  pinMode(kontak,OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); 
  pinMode(RELAY_PIN, OUTPUT);
  woe = LOW;
  RFID = HIGH;
  digitalWrite(kontak, HIGH);
}

void loop() {
  bismilah();
  //timer();
  standar.loop();
  if (standar.isPressed())
    Serial.println("Standar Naik");
  if (standar.isReleased())
    Serial.println("Standar Turun");
    
  int stdr = standar.getState();
  if (stdr == LOW){
    
    getTAG();
    if (TAG=="118514517"){
      Serial.println("TAG : Kartu");
      TAG = "";
      
      if(RFID == HIGH) {
        woe = HIGH;
        Serial.println("Raspberry Sys ON / Selenoid Narik");  
        RFID = LOW;
        slena();
        delay(300);
      }
      else {
        woe = LOW;
        Serial.println("Raspberry Sys OFF / Selenoid Dorong");
        RFID = HIGH;
        digitalWrite(RELAY_PIN,HIGH);
        slenb();
        delay(300);
        Serial.println(" ");
      }
    }
  }
}

void bismilah(){
  lastButtonState = currentButtonState;      
  currentButtonState = digitalRead(BUTTON_PIN); 
   if(lastButtonState == HIGH && currentButtonState == LOW) {
      Serial.println("The button is pressed");
      if(woe == HIGH){
         if(relayState == HIGH){
           relayState = LOW;
           delay(100);
         }
         
         else{
          relayState = HIGH;
         }
     digitalWrite(RELAY_PIN, relayState); 
     }
   }
}

void slena(){
  if(woe == HIGH){
    digitalWrite(slnida,LOW);
    digitalWrite(slnidb,HIGH);
    serv=millis();
  }
  if(serv<millis()-1500){
    digitalWrite(slnidb,LOW);
  }
}

void slenb(){
  if(woe == LOW){
    digitalWrite(slnidb,LOW);
    digitalWrite(slnida,HIGH);
    serv=millis();
  }
  if(serv<millis()-1500){
    digitalWrite(slnida,LOW);
  }
}

void timer(){
  if(RFID==HIGH){
    if(relayState==HIGH){
    times=millis();
    digitalWrite(kontak, HIGH);
    }
  }
  if(times<millis()-5000){
    digitalWrite(kontak, LOW);
    Serial.print("a");
  }
}
