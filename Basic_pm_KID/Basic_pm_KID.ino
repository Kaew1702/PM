#include "PMS.h"
#define RXD2 23 //fafwf
#define TXD2 19
PMS pms(Serial);
PMS::DATA data;

void setup()
{
  Serial.begin(9600, SERIAL_8N1, RXD2, TXD2);   // GPIO1, GPIO3 (TX/RX pin on ESP-12E Development Board)
  //Serial.begin(9600);  // GPIO2 (D4 pin on ESP-12E Development Board)
}

void loop()
{
  if (pms.read(data))
  {
    Serial.print("PM 1.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_1_0);

    Serial.print("PM 2.5 (ug/m3): ");
    Serial.println(data.PM_AE_UG_2_5);

    Serial.print("PM 10.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_10_0);

    Serial.println();
  }

  // Do other stuff...
}
