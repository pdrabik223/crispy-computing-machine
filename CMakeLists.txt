cmake_minimum_required(VERSION 3.20)
project(TheLockScreenQuestion)

set(CMAKE_CXX_STANDARD 14)

set(sfml_window_dir
        sfml_window/window.h
        sfml_window/window.cpp
        sfml_window/view.h
        sfml_window/view.cpp
        )
set(simulation_dir
        CellularSimulationEngine/cell.h
        CellularSimulationEngine/cell.cpp
        CellularSimulationEngine/plane.h
        CellularSimulationEngine/plane.cpp
        CellularSimulationEngine/engine.h
        CellularSimulationEngine/engine.cpp
        )
set(sim_painter_dir
        SimPainter/painter.h
        SimPainter/painter.cpp)

add_executable(main  main.cpp
        ${sfml_window_dir}
       ${simulation_dir})

add_executable(painter  SimPainter/painter_example.cpp
        ${sfml_window_dir}
        ${simulation_dir}
        ${sim_painter_dir})

add_subdirectory(SFML)
add_subdirectory(pm-stl)

set(executables main painter)

foreach(executable IN LISTS executables)
    target_link_directories(${executable}
            PUBLIC ${PROJECT_SOURCE_DIR}/sfml/src
            PUBLIC ${PROJECT_SOURCE_DIR}/pm-stl
            )

    target_link_libraries(${executable}
            sfml-graphics
            sfml-system
            sfml-window
            pm_stl
            )

    target_include_directories(${executable}
            PUBLIC ${PROJECT_SOURCE_DIR}/sfml/include
            PUBLIC ${PROJECT_SOURCE_DIR}/pm-stl
            )
endforeach()
