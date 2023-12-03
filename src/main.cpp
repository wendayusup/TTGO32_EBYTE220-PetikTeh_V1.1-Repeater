/*KODE REPEATER
PT MAKERINDO PRIMA SOLUSI
PETIK TEH*/

#include <Arduino.h>

// LONG RANGE SOURCE
#include <LoRa.h>
#include <SPI.h>
#define SS 18
#define RST 14
#define DIO0 26
#define SCK 5
#define MISO 19
#define MOSI 27

// GPS SOURCE
#include <TinyGPS++.h>
#define RX 34
#define TX 12
HardwareSerial neogps(1);
TinyGPSPlus gps;
String Latitude = "0";
String Longitude = "0";
String Altitude = "0";

// EBYTE SOURCE
HardwareSerial ebyteSerial(2);

// UNIQUE ID / KEY
byte Nodegateway = 0xC0;
byte NoderepeaterA = 0xB0;
byte NoderepeaterB = 0xB1;
// PILIH BYTE SESUAI DEVICE
byte NodeNetral = 0x00;
byte Nodepetik1 = 0xA0;
byte Nodepetik2 = 0xA1;
byte Nodepetik3 = 0xA2;
byte Nodepetik4 = 0xA3;
byte Nodepetik5 = 0xA4;
byte Nodepetik6 = 0xA5;
byte Nodepetik7 = 0xA6;
byte Nodepetik8 = 0xA7;
byte Nodepetik9 = 0xA8;
byte Nodepetik10 = 0xA9;
String SenderNode = "";
String outgoing;
byte msgCount = 0;
String incoming = "";

bool node1 = true;
bool node2 = false;
bool node3 = false;
bool node4 = false;
bool node5 = false;
bool node6 = false;
bool node7 = false;
bool node8 = false;
bool node9 = false;
bool node10 = false;
bool rpt = false;

int RSSI;
String ID = "RPGMBG0823001";

// MILLIS()
unsigned long int awal = 0;
unsigned long sekarang = 0;
unsigned long int sec = 0;
int interval = 2;
int Secs = 0;

void setup()
{
  /*Serial Begin*/
  Serial.begin(115200);

  /*Ebyte Begin*/
  ebyteSerial.begin(9600, SERIAL_8N1, 32, 33);

  /*GPS Begin*/
  neogps.begin(9600, SERIAL_8N1, RX, TX);

  /*LoRa Begin*/
  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DIO0);
  LoRa.begin(915E6);
  LoRa.setSpreadingFactor(11);
  LoRa.setCodingRate4(2);
  LoRa.setSignalBandwidth(500E3);
}

void sendMessage(String outgoing, byte NoderepeaterA, byte othernode)
{
  LoRa.beginPacket();            // start packet
  LoRa.write(othernode);         // add destination address
  LoRa.write(NoderepeaterA);     // add sender address
  LoRa.write(msgCount);          // add message ID
  LoRa.write(outgoing.length()); // add payload length
  LoRa.print(outgoing);          // add payload
  LoRa.endPacket();              // finish packet and send it
  msgCount++;                    // increment message ID
}

void onReceive(int packetSize)
{
  if (packetSize == 0)
    return;
  int recipient = LoRa.read();
  byte sender = LoRa.read();
  if (sender == 0XA0)
    SenderNode = "NodePetik1:";
  else if (sender == 0XA1)
    SenderNode = "NodePetik2:";
  else if (sender == 0XA2)
    SenderNode = "NodePetik3:";
  else if (sender == 0XA3)
    SenderNode = "NodePetik4:";
  else if (sender == 0XA4)
    SenderNode = "NodePetik5:";
  else if (sender == 0XA5)
    SenderNode = "NodePetik6:";
  else if (sender == 0xA6)
    SenderNode = "NodePetik7:";
  else if (sender == 0XA7)
    SenderNode = "NodePetik8:";
  else if (sender == 0XA8)
    SenderNode = "NodePetik9:";
  else if (sender == 0XA9)
    SenderNode = "NodePetik10:";
  byte incomingMsgId = LoRa.read();
  byte incomingLength = LoRa.read();

  while (LoRa.available())
  {
    incoming = LoRa.readStringUntil('\n');
  }
  if (incomingLength != incoming.length())
  {
    Serial.println("error: message length does not match length");
    ;
    return;
  }

  if (recipient != Nodepetik1 && recipient != NoderepeaterA)
  {
    // Serial.println("This message is not for me(1).");
    ;
    return;
  }

  if (incoming.startsWith("MPGMBG0823001"))
  {
    Serial.println(incoming);
    ebyteSerial.println(incoming);
  }
  else if (incoming.startsWith("MPGMBG0823002"))
  {
    Serial.println(incoming);
    ebyteSerial.println(incoming);
  }
  else if (incoming.startsWith("MPGMBG0823003"))
  {
    Serial.println(incoming);
    ebyteSerial.println(incoming);
  }
  else if (incoming.startsWith("MPGMBG0823004"))
  {
    Serial.println(incoming);
    ebyteSerial.println(incoming);
  }
  else if (incoming.startsWith("MPGMBG0823005"))
  {
    Serial.println(incoming);
    ebyteSerial.println(incoming);
  }
  else if (incoming.startsWith("MPGMBG0823006"))
  {
    Serial.println(incoming);
    ebyteSerial.println(incoming);
  }
  else if (incoming.startsWith("MPGMBG0823007"))
  {
    Serial.println(incoming);
    ebyteSerial.println(incoming);
  }
  else if (incoming.startsWith("MPGMBG0823008"))
  {
    Serial.println(incoming);
    ebyteSerial.println(incoming);
  }
  else if (incoming.startsWith("MPGMBG0823009"))
  {
    Serial.println(incoming);
    ebyteSerial.println(incoming);
  }
  else if (incoming.startsWith("MPGMBG0823010"))
  {
    Serial.println(incoming);
    ebyteSerial.println(incoming);
  }
}

void gpsdata()
{
  while (neogps.available())
    if (gps.encode(neogps.read()))
      if (gps.location.isValid())
      {
        Latitude = String(gps.location.lat(), 6);
        Longitude = String(gps.location.lng(), 6);
        Altitude = String(gps.altitude.meters() - 25.00);
      }
}

void loop()
{

  sekarang = millis();
  sec = sekarang / 1000;
  if ((unsigned long)(sec - awal) >= interval)
  {
    awal = sec;
    Secs++;

   
    if ((Secs > 0 && Secs <= 3))
    {
      String message = "11";
      sendMessage(message, NoderepeaterA, Nodepetik1);
    }
    else if ((Secs > 3 && Secs <= 6))
    {
      String message = "22";
      sendMessage(message, NoderepeaterA, Nodepetik2);
    }
    else if ((Secs > 6 && Secs <= 9))
    {
      String message = "33";
      sendMessage(message, NoderepeaterA, Nodepetik3);
    }
    else if ((Secs > 9 && Secs <= 12))
    {
      String message = "44";
      sendMessage(message, NoderepeaterA, Nodepetik4);
    }
    else if ((Secs > 12 && Secs <= 15))
    {
      String message = "55";
      sendMessage(message, NoderepeaterA, Nodepetik5);
    }
    else if ((Secs > 15 && Secs <= 18))
    {
      String message = "66";
      sendMessage(message, NoderepeaterA, Nodepetik6);
    }
    else if ((Secs > 21 && Secs <= 24))
    {
      String message = "77";
      sendMessage(message, NoderepeaterA, Nodepetik7);
    }
    else if ((Secs > 24 && Secs <= 27))
    {
      String message = "88";
      sendMessage(message, NoderepeaterA, Nodepetik8);
    }
    else if ((Secs > 27 && Secs <= 30))
    {
      String message = "99";
      sendMessage(message, NoderepeaterA, Nodepetik9);
    }
    else if ((Secs > 30 && Secs <= 33))
    {
      String message = "1010";
      sendMessage(message, NoderepeaterA, Nodepetik10);
    }
    else if ((Secs > 33 && Secs <= 36))
    {
      String message = String() + ID + "," + Latitude + "," + Longitude + "," + Altitude + ",*";
      ebyteSerial.println(message);
      message = "";
    }
     else if (Secs > 37)
    {
      Secs = 0;
    }
  }
  gpsdata();
  onReceive(LoRa.parsePacket());
}