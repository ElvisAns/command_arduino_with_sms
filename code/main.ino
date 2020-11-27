#include<SoftwareSerial.h>

SoftwareSerial Serial1(10, 11); //connect RXD pin of sim800L to pin 11 of arduino, connect the TXD pin of sim800L to pin10 of arduino
String command;
//make sure the antenna is well attached , otherwise you wont be able to see messages
//If you are using different powersupplies, make sure they are grounded together with the arduino's ground

#define  Im_at_break_please "BREAK"
#define  Im_outside_please "OUTS"
#define  Im_busy_for_now "BUSY"
#define  just_come_in "DISPO"

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println("Starting...");
  delay(1000);
  Serial1.println("AT");
  pollSms();
  int x=0;
  while(x<1500){
  
  Serial.println("Searching Network...");
  delay(10);
   x++;
  }
  delay(5000);
  Serial.println("Network connected succesfully...");
  Serial.println("Now send you commands on sms to sim card inserted in the module...");
  delay(100);
  Serial1.println("AT+CMGF=1");
  pollSms();
  Serial1.println("AT+CNMI=1,2,0,0,0");
  pollSms();
}

void loop()
{
  pollSms();
}

void pollSms()
{
  delay(500);
  String constchar;

  while (Serial.available())
  {
    Serial1.write(Serial.read());
  }
  delay(100);
  while (Serial1.available())
  {
    constchar += char(Serial1.read());
  }

  if (constchar.length() > 56) {
    command = constchar.substring(56);
    command.trim();
    command.toUpperCase();
    if (command ==  Im_at_break_please) {
      Serial.println("Im at break please comme after");
    }
    //nest all other conditions after!
    //Serial.println(constchar.substring(56));
  }

}
