//
// Created by piotr on 27/10/2021.
//
#include "../SimulationEngine/engine.h"
#include "../SimulationEngine/plane.h"
#include "../sfml_window/window.h"
#include "iostream"
#include "painter.h"
#include <conio.h>
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
int main() {

  printf("hello world of simulations!\n\n");

  Painter painter(800,800,100,100);

  Window screen(800, 800);


  Engine engine(painter.GetPlane());
  screen.PushFrame(engine.GetPlane());
  while (true) {
    engine.Step();
    screen.PushFrame(engine.GetPlane());
    while(screen.GetQueueSize()>30) std::this_thread::sleep_for(std::chrono::milliseconds(16)) ;
    if(screen.GetQueueSize() == 0) break;
  }

  return 0;
}
#pragma clang diagnostic pop