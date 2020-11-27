#include<SoftwareSerial.h>

SoftwareSerial Serial1(10, 11);
String command;

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
  delay(10000);
  Serial.println("Searching Network...");
  delay(5000);
  Serial.println("Searching Network...");
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
