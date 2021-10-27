//
// Created by piotr on 26/10/2021.
//

#ifndef THELOCKSCREENQUESTION_SIMULATIONENGINE_CELL_H_
#define THELOCKSCREENQUESTION_SIMULATIONENGINE_CELL_H_

struct Cell{

  enum class State{
    AIR,
    FLUID,
    BARRIER,
    // pipe_ip
        // pipe_out
  };

  Cell(State state);
  Cell(const Cell& other) = default;
  Cell& operator=(const Cell& other) = default;
  State state;


};

#endif // THELOCKSCREENQUESTION_SIMULATIONENGINE_CELL_H_
