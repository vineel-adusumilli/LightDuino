#include <avr/wdt.h>
#include <DmxSimple.h>
#include <SPI.h>
#include <WiFly.h>

#include "Credentials.h"

WiFlyClient client("192.168.1.123", 5000);

int DMX_dir = 4;

byte rgb[] = { 0, 0, 0 };
byte ctr = 0;

boolean debug = false;

void setup() {
  // disable watchdog incase enabled for some reason
  wdt_disable();
  
  if (debug) {
    Serial.begin(115200);
    Serial.println("Initialized.");
  }
  WiFly.begin();

  if (!WiFly.join(ssid, passphrase)) {
    while (1) {
      // Hang on failure.
    }
  }
  
  if (debug)
    Serial.print("Connecting to client...");
  while (!client.connected()) {
    client.connect();
  }
  if (debug)
    Serial.print("handshaking...");
  client.write('a');
  while (client.read() != 'b');
  client.write('c');
  if (debug)
    Serial.println("connected!");

  pinMode(DMX_dir, OUTPUT);
  digitalWrite(DMX_dir, HIGH);
  DmxSimple.usePin(2);
  DmxSimple.write((int) 1, (int) 81);
  updateColors();
  
  wdt_enable(WDTO_8S);
}

void loop() {
  while (client.available()) {
    byte b = client.read();
    if (b != 1) {
      rgb[ctr++] = b;
      ctr %= 3;
    } 
    else {
      if (ctr == 0) {
        if (debug) {
          Serial.print(rgb[0]);
          Serial.print(", ");
          Serial.print(rgb[1]);
          Serial.print(", ");
          Serial.println(rgb[2]);
        }
        wdt_reset();
        updateColors();
      }
      ctr = 0;
      client.write(32);
    }
  }
}

void updateColors() {
  DmxSimple.write((int) 3, rgb[0]);
  DmxSimple.write((int) 4, rgb[1]);
  DmxSimple.write((int) 5, rgb[2]);
}

