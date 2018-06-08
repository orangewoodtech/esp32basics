#include <ArduinoJson.h>
#include <ETH.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <WiFiGeneric.h>
#include <WiFiMulti.h>
#include <WiFiScan.h>
#include <WiFiServer.h>
#include <WiFiSTA.h>
#include <WiFiType.h>
#include <WiFiUdp.h>


WiFiMulti WiFiMulti;
WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network
  WiFiMulti.addAP("orangewoodlabs", "9953562788");

  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  delay(500);

  //////Jason Setup
}

int value = 0;
String json;
int i = 0;


void loop() {
  WiFiClient client = server.available();   // listen for incoming clients
  if (client) {                             // if you get a client,
    Serial.println("New Client.");
    client.connected();// print a message out the serial port
    client.write("Hello PI");                                          // make a String to hold incoming data from the client
    if (client.available()) {             // if there's bytes to read from the client,
      char d = client.read();
      if (d == 'Y') {
        while (client.connected()) {           // loop while the client's connected
          if (client.available()) {             // if there's bytes to read from the client,
            char c = client.read();
            // read a byte, then
            json = json + c;

            if (c == '}') {
              DynamicJsonBuffer jsonBuffer;
              JsonObject& root = jsonBuffer.parseObject(json);
              if (!root.success()) {
                Serial.println("parseObject() failed");
              }
              int index = root["index"];
              const char* Gcode = root["GCode"];
              int hash_value = root["Hash_value"];
              int hash_try = hashing(Gcode);
              if (index == i && hash_try == hash_value) {
                Serial.print(index);
                Serial.print("\t");
                Serial.print(Gcode);
                Serial.print("\t");
                Serial.println(hash_value);
                if (Serial.available())
                { Serial.write(Gcode);
                 String a=Serial.readString();
                  if (a == "ok")
                { while (1)
                    { Serial.write( "?" );      /////GRBL code
                      String pos = Serial.readString();
                      if(pos="IDLE")
                      {break;}
                    }
                    }
                  }
                  json = "";
                         client.write("Y");
                         i++;
                }
                else {
                  client.write("N");
                  json = "";
                }
                index = 0;
                Gcode = "";
                hash_value = 0;
              }
            }
          }
        }
      }
    }

    client.stop();
    Serial.println("Client Disconnected.");

    delay(10);
  }


int hashing(String val)
  { int hash = 0, i = 0;
    while (val[i] != '\0') {
      hash += int(val[i]) % 101;
      ++i;
    }
    return hash;
  }



