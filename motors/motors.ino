#include "motor_functions.h"

void setup() {
  //init_movement();
  init_movement(); //init_movement();

  //for(int i = 0; i < 1000; i++) {
    //move_forward();
    //delay(10);
    //brake();
    //delay(100);
  //}


  move_forward();
  delay(500);
  brake();
  delay(100);
  brake();
  return;
}

void loop() {
  //
}
