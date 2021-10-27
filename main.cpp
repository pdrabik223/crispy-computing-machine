//
// Created by piotr on 26/10/2021.
//
#include "SimulationEngine/engine.h"
#include "SimulationEngine/plane.h"
#include "iostream"
#include "sfml_window/window.h"
#include <conio.h>
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
int main() {

  printf("hello world of simulations!\n\n");

  Plane test(100, 100);
  Window screen(800, 800);
  test.AddSquare({50, 50}, 10, 10);
  screen.PushFrame(test);
  Engine engine(test);

  while (true) {
    engine.Step();
    screen.PushFrame(engine.GetPlane());
    while(screen.GetQueueSize() > 30) std::this_thread::sleep_for(std::chrono::milliseconds(16)) ;
    if(screen.GetQueueSize() > 100) break;
  }

  return 0;
}
#pragma clang diagnostic pop