#include <Arduino.h>
#include <SoftwareSerial.h>

#include <ESPAsyncWebServer.h>

unsigned long lastoutput = 0l;

SoftwareSerial testSerial(D6, D7);

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
AsyncEventSource events("/events");

void setup()
{
  // put your setup code here, to run once:
  testSerial.begin(9600);
  Serial.begin(9600);
  Serial.println("Starting");
}

byte number = 0;

void echoloop()
{
  if (testSerial.available())
  {
    number = testSerial.read();
    Serial.printf("character received: [%c] [%d]\n", number, number);
  }

  if (millis() - lastoutput > 2000) {
    lastoutput = millis();
    testSerial.printf("I am alive\n");
  }
}

void outputloop()
{
  testSerial.println("Here");
  Serial.println("Here");
  delay(1000);
}

void loop()
{
  //outputloop();
  echoloop();
}