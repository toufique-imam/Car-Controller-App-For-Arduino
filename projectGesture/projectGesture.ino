#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
char readString[20];
RH_ASK driver;
void setup()
{
  Serial.begin(9600);
  if (!driver.init())
    Serial.println("init failed");
}
int idx=0;
void loop()
{
  
  while (Serial.available()) {
    delay(3);
    if (Serial.available() > 0) {
      char c = Serial.read();
      readString[idx++]= c;
    }
  }
  if (strlen(readString) > 0) {
    Serial.println(readString);
    driver.send((uint8_t *)readString,strlen(readString));
    driver.waitPacketSent();
    idx=0;
    delay(300);
  }
}
