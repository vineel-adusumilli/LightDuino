
// (Based on Ethernet's WebClient Example)

#include <DmxSimple.h>
#include <SPI.h>
#include <WiFly.h>

#include "Credentials.h"

WiFlyClient client("192.168.1.121", 8080);

int DMX_dir = 4;

byte rgb[] = { 0, 0, 0 };
byte ctr = 0;

void setup() {
  //Serial.begin(9600);
  //Serial.println("Initializing...");

  WiFly.begin();
  
  if (!WiFly.join(ssid, passphrase)) {
    //Serial.println("Association failed.");
    while (1) {
      // Hang on failure.
    }
  }
  
  //Serial.print("connecting...");
  while (!client.connected()) {
    client.connect();
  }
  //Serial.println("connected");
  
  pinMode(DMX_dir, OUTPUT);
  digitalWrite(DMX_dir, HIGH);
  DmxSimple.usePin(2);
  DmxSimple.write((int) 1, (int) 81);
  updateColors();
}

void loop() {
  if (!client.connected()) {
    //Serial.print("reconnecting...");
    while (!client.connected()) {
      client.connect();
    }
    //Serial.println("connected");
  }
  
  while (client.available()) {
    byte b = client.read();
    if (b != 1) {
      rgb[ctr++] = b;
      ctr %= 3;
    } else {
      //Serial.print(rgb[0]);
      //Serial.print(" ");
      //Serial.print(rgb[1]);
      //Serial.print(" ");
      //Serial.print(rgb[2]);
      //Serial.println();
      if (ctr == 0) {
        updateColors();
      }
      ctr = 0;
    }
  }
}

void updateColors() {
  //Serial.println("Updating Colors!");
  DmxSimple.write((int) 3, rgb[0]);
  DmxSimple.write((int) 4, rgb[1]);
  DmxSimple.write((int) 5, rgb[2]);
}
