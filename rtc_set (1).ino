#include <Wire.h>
#include <RTClib.h>

RTC_DS1307 rtc;

void setup(){
  
  Serial.begin(9600); 
  Wire.begin();
  rtc.begin();
  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop(){
  
  DateTime now = rtc.now();
 DateTime future (now + TimeSpan(0,0,0,0));
    Serial.print(future.year(),DEC);
    Serial.print('/');
   
    Serial.print(future.month(),DEC);
    Serial.print('/');
   
    Serial.print(future.day(),DEC);
    Serial.print(",");
     
    Serial.print(future.hour(),DEC);
    Serial.print(':');
   
    Serial.print(future.minute(),DEC);
    Serial.print(':');
  
    Serial.print(future.second(),DEC);
  
    Serial.println(",");
 
    delay(3000);
}
  
