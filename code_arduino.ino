#include <Wire.h>;
#include "DHT.h"
#include <LiquidCrystal_I2C.h>;
LiquidCrystal_I2C lcd(0x27,16,2);

#define relay 8
#define doam A0
#define pot A1

const int mode_man =2;
const int led_man =5;
const int mode_auto =3;
const int led_auto =6;
const int mode_motor =4;
const int led_motor =7;
const int DHTPIN = 9;
const int DHTTYPE = DHT11;
DHT dht(DHTPIN, DHTTYPE);
unsigned char onoff=0;
unsigned char onoff1=0;
unsigned char onoff2=0;
int doamdat;
int bientro;


void setup(){
  pinMode(led_man, OUTPUT);
  pinMode(mode_man, INPUT_PULLUP);
  pinMode(led_auto, OUTPUT);
  pinMode(mode_auto, INPUT_PULLUP);
  pinMode(led_motor, OUTPUT);
  pinMode(mode_motor, INPUT_PULLUP);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
  lcd.init();
  lcd.backlight();
  dht.begin();
}
void hienthi_man(int DAD){
 int h = dht.readHumidity();
 float t = dht.readTemperature();
 lcd.setCursor(0,0);
 lcd.print("Man");
 lcd.setCursor(8,0);
 lcd.print("T:  ");
 lcd.setCursor(10,0);
 lcd.print(t);
 lcd.setCursor(0,1);
 lcd.print("DAD:  %");
 lcd.setCursor(4,1);
 lcd.print(DAD);
 lcd.setCursor(8,1);
 lcd.print("DAK:  %");
 lcd.setCursor(12,1);
 lcd.print(h);
 
 
 }
 
 
void hienthi_auto(int DA, int BT){
  int h = dht.readHumidity();
  float t = dht.readTemperature();
  lcd.setCursor(0,0);
  lcd.print("Auto");
  lcd.setCursor(8,0);
  lcd.print("T:  *C");
  lcd.setCursor(10,0);
  lcd.print(t);
  lcd.setCursor(0,1);
  lcd.print("DAD:  %");
  lcd.setCursor(4,1);
  lcd.print(DA);
  lcd.setCursor(8,1);
  lcd.print("BT:  %");
  lcd.setCursor(11,1);
  lcd.print(BT);
   
}


void loop(){
 
   
  if (digitalRead(mode_man)==LOW){
  delay(20);
  if (digitalRead(mode_man)==LOW){
    if (onoff==0){
      onoff=1;
      digitalWrite(led_man, HIGH);
    }
    else{
      lcd.clear();
      onoff=0;
      digitalWrite(led_man,LOW);
    }  
}
while(digitalRead(mode_man)==LOW);
  }




if (digitalRead(mode_auto)==LOW){
  delay(20);
  if (digitalRead(mode_auto)==LOW){
    if (onoff1==0){
      hienthi_auto(doamdat, bientro);
      onoff1=1;
      digitalWrite(led_auto, HIGH);
    }
    else{
      lcd.clear();
      onoff1=0;
      digitalWrite(led_auto,LOW);
    }  
}
while(digitalRead(mode_auto)==LOW);
}


if(digitalRead(led_man)==HIGH){
  doamdat = analogRead(doam);
  doamdat = map(doamdat,1023,0,0,100);
  hienthi_man(doamdat);
if (digitalRead(mode_motor)==LOW){
  delay(20);
  if (digitalRead(mode_motor)==LOW){
    if (onoff2==0){
      digitalWrite(relay, HIGH);
      onoff2=1;
      digitalWrite(led_motor, HIGH);
    }
    else{
      digitalWrite(relay,LOW);
      onoff2=0;
      digitalWrite(led_motor,LOW);
    }  
}
while(digitalRead(mode_motor)==LOW);
}
}


 if(digitalRead(led_auto)==HIGH){
   doamdat = analogRead(doam);
   doamdat = map(doamdat,1023,0,0,100);
  bientro = analogRead(pot);
  bientro = map(bientro,0,1023,0,100);
  hienthi_auto(doamdat, bientro);
  if(doamdat < bientro){
  digitalWrite(relay, HIGH); 
    }
    else{
  digitalWrite(relay, LOW);
    }
  }
}









  
