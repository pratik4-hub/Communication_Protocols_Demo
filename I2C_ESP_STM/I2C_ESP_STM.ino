/************NodeMCU as I2C Master*************/

#include <Wire.h>
#include <stdarg.h>
#include <PolledTimeout.h>
#include <ESP8266WiFi.h>

#define SDA_PIN D1
#define SCL_PIN D2

int flag = 0;
const int16_t I2C_MASTER = 0x42;
const int16_t I2C_SLAVE = 0x55;

char C, msg[64]; int i = 0;

void setup() {
  Serial.begin(115200);
  Wire.setClock(100000);
  WiFi.disconnect();
  Wire.begin(SDA_PIN,SCL_PIN,I2C_MASTER);
}
void receiveData()
{ 
  while(flag != 0){
    Wire.beginTransmission(I2C_SLAVE);
    using periodic = esp8266::polledTimeout::periodicMs;
    static periodic nextPing(1000);
  
    if (nextPing) 
    {
      Wire.requestFrom(I2C_SLAVE, 11);    // request 6 bytes from slave device #8
      while(Wire.available())
      { // slave may send less than requested
        char c = Wire.read();    // receive a byte as character
        Serial.print(c);
        i++;
        if(i == 11)
        {
          flag=0;
          i = 0;
          break;
        }
      }
    }
  }
  flag = 0; 
}
void transferData()
{
    if(Serial.available()>0 && flag == 0)
    {
      C = Serial.read();  
      Wire.beginTransmission(I2C_SLAVE);
      Wire.write(C);
      Wire.endTransmission();
    }
    if(C == '\r')
    {
      flag = 1;
    }
}


void loop() {
      transferData();
      delay(1);
      receiveData();
 }
