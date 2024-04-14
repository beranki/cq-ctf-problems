#include <iostream>
#include <stdlib.h>
#include <robolib.h>

RB_Instance* robo;
RB_ColorSensor* sensor;

RB_Color readSensor (RB_ColorSensor* sensor) {
  RB_Color* color = (RB_Color*) malloc(sizeof(RB_Color));
  RB_ColorSensorRead(sensor, color);

  return color;
}

int main () {

  if (RB_init(robo) < 0) {
    printf("Robolib initalization failed\n");
    return -1;
  }

  if (RB_initSensor(robo, sensor) < 0) {
    printf("Robolib colorsensor initalization failed\n");
    return -1;
  }

  bool interrupted = false;
  int cnt = 100;
  while (!interrupted) {
    while (RB_hasEvent(robo)) {
      RB_EVENT e = RB_nextEvent(robo);
      if (e == RB_EVENT_INTERRUPT) {
        interrupted = true;
      }
    }
    if (cnt-- == 0) {
      getAndDrawColor();
      // Read & Draw Sensor Value
      RB_Color* color = readSensor(sensor);
      printf("Color Read: (%d, %d, %d)", color->r, color->g, color->b);

      cnt = 100;
    }
  }

  return 0;
}
