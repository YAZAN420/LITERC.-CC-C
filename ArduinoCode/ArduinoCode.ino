#include <cvzone.h>
#include <Wire.h>
#include <QMC5883LCompass.h>
QMC5883LCompass compass;
SerialData s1(2,4);
int val[2];
void setup() {
  s1.begin(9600);
  Wire.begin();
  compass.init();
}
void loop() {
  int x, y;
  compass.read();
  x = compass.getX();
  y = compass.getY();
  val[0]=x;
  val[1]=y;
  s1.Send(val);
  delay(300);
}