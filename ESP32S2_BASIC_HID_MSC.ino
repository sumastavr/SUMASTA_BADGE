/**
 * Simple MSC device with SD card
 * author: chegewara
 */
#include "hidkeyboard.h"
HIDkeyboard dev2;

#include "sdusb.h"

#define SD_MISO  13
#define SD_MOSI  11
#define SD_SCK   12
#define SD_CS    10

SDCard2USB dev;


class MyHIDCallbacks: public HIDCallbacks{
  void onData(uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize) {
    Serial.printf("ID: %d, type: %d, size: %d\n", report_id, (int)report_type, bufsize);  
     for (size_t i = 0; i < bufsize; i++)
    {
        Serial.printf("%d\n", buffer[i]);
    }   
  }
};

void dataCB(uint8_t report_id, uint8_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
    for (size_t i = 0; i < bufsize; i++)
    {
        Serial.printf("%d\n", buffer[i]);
        Serial.printf("%c\n", buffer[i]);
    }
}

boolean keyboard;

void setup()
{
  Serial.begin(115200);
  delay(200);
  pinMode(33,INPUT_PULLUP);

  dev2.setBaseEP(3);
  dev2.begin();
  dev2.setCallbacks(new MyHIDCallbacks());
  
  if(dev.initSD(SD_SCK, SD_MISO, SD_MOSI, SD_CS)) {
      Serial.println("dev init");
      if(dev.begin()) {
        Serial.println("MSC lun 1 begin");
      } else log_e("LUN 1 failed");
  }  
}


long timer=millis();

void loop()
{
  if(digitalRead(33)==LOW){
    Serial.println(dev2.sendString(String("123456789\n"))?"OK":"FAIL");
    //dev.begin();
  }

  if(millis()-timer>30000){
    //Serial.println(dev2.sendString(String("123456789\n"))?"OK":"FAIL");
    //timer=millis();
  }
  /*
   delay(1000);
  //if(keyboard){
    delay(1000);
    dev2.sendKey(HID_KEY_A);
    delay(1000);
    Serial.println(dev2.sendString(String("123456789\n"))?"OK":"FAIL");
    delay(1000);
    Serial.println(dev2.sendString(String("abcdefghijklmnopqrst Uvwxyz\n"))?"OK":"FAIL");
  //}
  */
}
