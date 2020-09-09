#include<SPI.h>

char buff[]="H";

void setup() {
 
 Serial.begin(115200); /* begin serial with 9600 baud */
 SPI.begin();  /* begin SPI */
}

void loop() {
 char c;
 String readData;
 char buf[100];
 readData = Serial.readString();
 for (int i = 0; i < readData.length(); i++) { 
        buf[i] = readData[i]; 
    }

   digitalWrite(SS, LOW); // enable Slave Select
   // send test string

   //for (const char * p = "Hello, world!\r\n" ; c = *p; p++) 
   for (int i=0; c = buf[i],i<=strlen(buf); i++) 
   {
      SPI.transfer (c);
      //delay(1);
      Serial.print(c);
      
   }
   digitalWrite(SS, HIGH); // disable Slave Select
   //delay(1);
 //Serial.println("Sent!!\n");
 memset(&buf,0,sizeof(buf));  
}
