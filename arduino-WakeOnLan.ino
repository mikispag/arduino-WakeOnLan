// Arduino Wake-On-LAN
// Needs Arduino > 1.0-beta3 with the new UDP API ( http://code.google.com/p/arduino/wiki/Arduino1 )

// Date: 04 September 2011
// Author: Michele Spagnuolo
// Email: michele@spagnuolo.me
// Site: http://michele.spagnuolo.me

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

// ETHERNET CONFIGURATION
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };    // Arduino's MAC address
byte ip[] = { 192, 168, 1, 74 };     // Arduino IP address
byte gw[] = { 192, 168, 1, 1 };      // Gateway IP address
byte bc[] = { 192, 168, 1, 255 };    // Broadcast IP address

// WOL CONFIGURATION
byte pc_mac[] = {0x00, 0x24, 0x1D, 0xCD, 0x6D, 0x24};  // PC's MAC address

EthernetUDP Udp;

char WOL_done = 0;

void setup() {
    Ethernet.begin(mac,ip,gw);
    delay(100);
    Udp.begin(7);
    delay(100);
}

void WOL(byte mac[]) {
    byte preamble[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    char i;

    Udp.beginPacket(bc, 7);
    Udp.write(preamble, sizeof preamble);
    
    for (i=0; i<16; i++)
      Udp.write(mac, sizeof mac);
    
    Udp.endPacket();
}

void loop() {
  if (WOL_done)
    WOL(pc_mac);
  WOL_done = 1;
}
