//
// Created by piotr on 26/10/2021.
//
#include "SimulationEngine/plane.h"
#include "iostream"
#include "sfml_window/window.h"
int main(){

  printf("hello world of simulations!\n");

  Plane test(100,100);
  Window screen(800,800);

  screen.PushFrame(test);


  return 0;
}