#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <time.h>

#define firebaseURl "antrian-32d47.firebaseio.com"
#define authCode "s3eUTQNkkRSYRiR44tZy1DK1DjzLg8fzcO8KeR8r"

#include <PString.h>
#include "Adafruit_Thermal.h"
#include <Wire.h>

//#include "RTClib.h"

//RTC_DS1307 RTC;

#include "SoftwareSerial.h"
#define TX_PIN D3 
#define RX_PIN D4 

SoftwareSerial mySerial(RX_PIN, TX_PIN); 
Adafruit_Thermal printer(&mySerial);   

const char* ssid = "tay";
const char* password = "12345123";
int timezone = 7 * 3600;
int dst = 0;
int hitung_int;

float hitung=0;

const int buttonPin = D1;
const int buttonPin2 = D2;
const int buttonReset = D5;

int buttonState=0;             
int lastButtonState = LOW;  
long lastDebounceTime = 0;  
long debounceDelay = 50;
bool sekali = true,sekali2 = true, sekali3 = true;

void setup() {
   Wire.begin();
//    RTC.begin();
//   /  if (! RTC.isrunning()) {
//    Serial.println("RTC is NOT running!");
    
//    RTC.adjust(DateTime(__DATE__, __TIME__));
//  }
 pinMode(buttonPin, INPUT_PULLUP);
 pinMode(buttonPin2, INPUT_PULLUP);
 pinMode(buttonReset, INPUT_PULLUP);
//  Serial.begin(9600);
  mySerial.begin(9600); 
  
  printer.begin();  
  Pengaturan_wifi();
  Pengaturan_data();      
  pengaturan_waktu();
}

void loop() {
      char buffer[40];
      PString stri(buffer, sizeof(buffer));
      time_t now = time(nullptr);
      struct tm* p_tm = localtime(&now);
      stri.print(p_tm->tm_mday);
      stri.print("/");
      stri.print(p_tm->tm_mon + 1);
      stri.print("/");
      stri.print(p_tm->tm_year + 1900);
      
      stri.print(" ");
      
      stri.print(p_tm->tm_hour);
      stri.print(":");
      stri.print(p_tm->tm_min);
      stri.print(":");
      stri.println(p_tm->tm_sec);
      


      
  buttonState = digitalRead(buttonPin);
   if (!buttonState && sekali == true) {     
      printer.wake();       
      printer.setDefault(); 
      hitung+=1;
      Firebase.set("antrian",hitung);
      char buffer[40];
      PString str(buffer, sizeof(buffer));
      if(hitung<100)
      {
        str.print(0);
        if(hitung<10)
        {
          str.print(0);
        }
      }
      else if(hitung<10)
        {
          str.print(0);
        }
      hitung_int = hitung;
      str.print(hitung_int);
//      Serial.println(hitung);
  
      printer.boldOn();
      printer.justify('C');
  
      printer.setSize('M');
      printer.println(F("Nomor Antrian :"));
      delay(1000);
      printer.setSize('L');
      printer.println(str);
      delay(1000);
      printer.setSize('S');

    //  tambahan Waktu
//      str.begin();
//      time_t now = time(nullptr);
//      struct tm* p_tm = localtime(&now);
//      str.print(p_tm->tm_mday);
//      str.print("/");
//      str.print(p_tm->tm_mon + 1);
//      str.print("/");
//      str.print(p_tm->tm_year + 1900);
//      
//      str.print(" ");
//      
//      str.print(p_tm->tm_hour);
//      str.print(":");
//      str.print(p_tm->tm_min);
//      str.print(":");
//      str.println(p_tm->tm_sec);


  //  DateTime now = RTC.now();
  //  str.begin();
  //  str.print("tgl.");
  //  str.print(now.day(), DEC);
  //  str.print('-');
  //  str.print(now.month(), DEC);
  //  str.print('-');
  //  str.print(now.year(), DEC);
  //  str.print(' ');
  //  int z=0;
  //  z=now.hour(), DEC;
  //  if(z<10)str.print('0');
  //  
  //  str.print(z);
  //  str.print(':');
  //  z=now.minute(), DEC;
  //  if(z<10)str.print('0');
  //  str.print(now.minute(), DEC);
  //  str.print(':');
  //  z=now.second(), DEC;
  //  if(z<10)str.print('0');
  //  str.print(now.second(), DEC);
//    Serial.println(str);
    printer.println(stri);
    delay(1000);
//    printer.println("dibuat oleh tari");
    printer.feed(1);
//    printer.setDefault();
    printer.sleep();      
    delay(1000);  
    printer.wake();       
    printer.setDefault(); 
    
    } 

  else{
    sekali = true;
  } 
  
  if(!(digitalRead(buttonPin2))&& sekali2 == true){  
      printer.wake();       
      printer.setDefault();    
      hitung-=1;
      char buffer[40];
      PString str(buffer, sizeof(buffer));
      if(hitung<100)
      {
        str.print(0);
        if(hitung<10)
        {
          str.print(0);
        }
      }
      else if(hitung<10)
        {
          str.print(0);
        }
      hitung_int = hitung;
      if(hitung<0)hitung=0;
//      Serial.println(hitung);
      Firebase.set("antrian",hitung);
      str.print(hitung_int);
      printer.boldOn();
      printer.justify('C');
  
      printer.setSize('M');
      printer.println(F("Nomor Antrian :"));
      delay(1000);
      printer.setSize('L');
      printer.println(str);
      delay(1000);
      printer.setSize('S');

//      str.begin();
      
    //  DateTime now = RTC.now();
    //  str.begin();
    //  str.print("tgl.");
    //  str.print(now.day(), DEC);
    //  str.print('-');
    //  str.print(now.month(), DEC);
    //  str.print('-');
    //  str.print(now.year(), DEC);
    //  str.print(' ');
    //  int z=0;
    //  z=now.hour(), DEC;
    //  if(z<10)str.print('0');
    //  
    //  str.print(z);
    //  str.print(':');
    //  z=now.minute(), DEC;
    //  if(z<10)str.print('0');
    //  str.print(now.minute(), DEC);
    //  str.print(':');
    //  z=now.second(), DEC;
    //  if(z<10)str.print('0');
    //  str.print(now.second(), DEC);
//      Serial.println(str);
      printer.println(stri);
      delay(1000);
//    printer.println("dibuat oleh tari");
      printer.feed(1);
//    printer.setDefault();
      printer.sleep();      
      delay(1000);  
      printer.wake();       
      printer.setDefault(); 
       
      
         
         
        sekali2 = false;
    } 

  else{
    sekali2 = true;
  }

  if(!(digitalRead(buttonReset))&& sekali3 == true){
      printer.wake();       
      printer.setDefault(); 

      hitung=0;
//      Serial.println(hitung);
      Firebase.set("antrian",hitung);
      printer.justify('C');
  
      printer.setSize('M');
      delay(1000);
      printer.println(F("Printer Direset"));
      delay(1000);
      printer.feed(1);
      printer.sleep();
      delay(1000);
      printer.wake();
      printer.setDefault(); 
         
      //delay(3000);         
//      printer.wake();       
//      printer.setDefault();
  sekali3 = false;
    } 

  else{
    sekali3 = true;
  }
  
}

void Pengaturan_wifi(){
//  Serial.println();
//  Serial.print("Wifi connecting");
//  Serial.print(ssid);

  WiFi.begin(ssid,password);

//  Serial.println();
//  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
//    Serial.print(".");
  }
  delay(2000);
//  Serial.println(WiFi.localIP());
//  Serial.println("wif.iconnect");
}


void Pengaturan_data(){
  Firebase.begin(firebaseURl,authCode);
  delay(1000);
  float checking = Firebase.getFloat("check");
  while(checking != 1){
    Firebase.begin(firebaseURl,authCode);
    float checking = Firebase.getFloat("check");
    delay(1000);
  }
  hitung = Firebase.getFloat("antrian");
}

void pengaturan_waktu(){
  configTime(timezone, dst, "pool.ntp.org","time.nist.gov");
//  Serial.println("\nWaiting for Internet time");

  while(!time(nullptr)){
//     Serial.print("*");
     delay(1000);
  }
//  Serial.println("\nTime response....OK"); 
}

