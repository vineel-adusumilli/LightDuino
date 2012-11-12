LightDuino
==========

LightDuino is the Arduino complement to [lightwall](https://github.com/vineel-adusumilli/lightwall).

LightDuino connects to lightwall via a TCP connection over WiFi. lightwall then pushes RGB values to LightDuino which are then output via DMX. The end result is an illuminated wall at [TinyFactory](http://tinyfactory.co/).

LightDuino takes advantage of the [ProtoShield](https://www.sparkfun.com/products/7914), [Arduino DMX](http://www.skpang.co.uk/catalog/arduino-dmx-shield-p-663.html), and [WiFly](http://sparkfun.com/products/9954) sheilds.

The ProtoSheild is needed to connect pin 7 with the reset pin so the Arduino can reset itself whenever the heartbeat from the node.js server stops.

Usage
-----

The [SimpleTimer](http://www.arduino.cc/playground/Code/SimpleTimer), [DmxSimple](http://code.google.com/p/tinkerit/wiki/DmxSimple), and [WiFly-Shield](https://github.com/sparkfun/WiFly-Shield) should be in your sketches/libraries folder.

Another file, 'Credentials.h' is required before LightDuino can start working. It should look something like this:

```c
#ifndef __CREDENTIALS_H__
#define __CREDENTIALS_H__

// Wifi parameters
char ssid[] = "SSID";
char passphrase[] = "PASSPHRASE";

#endif
```

Issues
------

Currently, the baud rate is only set at 9600. This becomes a problem when the color is updated frequently and a buffer overflow occurs. I'm working on a fork of the WiFly-Shield library to increase the baud rate.

If the Arduino loses connection to lightwall, it needs to be restarted in order to reconnect. Hopefully I will be able to address this by modifying WiFly-Shield.

