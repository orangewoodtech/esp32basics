#include <Wire.h>


//
//#define SDA 21
//#define SCL 22

//#define SDA2 5
//#define SCL2 4

int i;  long roundsX; long roundsY; byte buf[8];

void setup() {
  Serial.begin(115200);
  Wire.begin(17, 5);
}

void loop()
{
  Wire.requestFrom(8, 11);   // request 6 bytes from slave device #8

  for (i = 0; i <= 11; i++)  {
    buf[i] = Wire.read();

  }
  // Serial.println(buf[i],HEX);

  double valX = 0;          double valY1 = 0;   double  valY2 = 0;
  valX += buf[3] << 24;  valY1 += buf[7] << 24; valY2 += buf[11] << 24;
  valX += buf[2] << 16;  valY1 += buf[6] << 16; valY2 += buf[10] << 16;
  valX += buf[1] << 8;   valY1 += buf[5] << 8;  valY2 += buf[9] << 8;
  valX += buf[0];        valY1 += buf[4];       valY2 += buf[8];

  valX = (valX) / 100;     valY1 = (valY1) / 100; valY2 = (valY2) / 100;
  Serial.print(valX); Serial.print("  "); Serial.print(valY1);Serial.print("  "); Serial.println(valY2);
  stoll(valY1, valY2);

  delay(10);

}

void stoll(float valY1, float valY2)
{ if (abs(valY1 - valY2) > 1) {
    pause();
  }

}

