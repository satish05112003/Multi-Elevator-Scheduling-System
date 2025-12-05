# Multi-Elevator-Scheduling-System
A simple multi-elevator scheduling system implemented in C, designed to demonstrate decision-making, real-time movement logic, and state management for embedded systems. The project models multiple elevators responding to hall calls, selecting the optimal lift, and simulating step-by-step motion. Suitable for showcasing embedded system concepts such as resource scheduling, control logic, and modular C programming

## Overview

The system models multiple elevators, each with its own current floor, target floor, and movement direction. When a hall call is made, the scheduler selects the most suitable elevator based on its current state and proximity. The simulation progresses step-by-step, showing how each elevator moves and responds to requests.

The project demonstrates:

* Struct-based modeling of embedded components
* Decision-making logic for optimal elevator assignment
* Stepwise simulation representing real-time behavior
* Modular and maintainable code suitable for embedded applications

## Features

* Configurable number of elevators and floors
* Automatic selection of the best elevator for any hall call
* Realistic movement logic (up, down, idle)
* Status display showing floor levels, targets, and directions
* Step-by-step simulation to mimic real-time system behavior

## Flow Diagram

[Multi Elevator Scheduling System](multi-elevator_scheduling_system.png)


## How It Works

1. **Initialization**
   User inputs number of floors and elevators. All elevators start at floor 0 in an idle state.

2. **Hall Call Assignment**
   When a call is placed from any floor, the scheduler:

   * Computes distance from each elevator to the requested floor
   * Penalizes elevators already handling a target
   * Assigns the call to the optimal elevator
   * Updates its target floor and direction

3. **Movement Logic**
   Each time step moves elevators by one floor toward their targets.
   Once a target floor is reached, the elevator becomes idle again.

4. **Status Monitoring**
   System state can be viewed anytime, showing:

   * Current floor
   * Target floor
   * Direction (UP, DOWN, IDLE)

## Applications

Although this program runs on a standard compiler, the logic maps well to embedded systems such as:

* Microcontroller-based lift controllers
* Real-time elevator dispatch systems
* Smart building automation
* Scheduling algorithms for resource allocation in embedded devices

The code is intentionally kept simple and modular, allowing easy porting to platforms like ARM Cortex, AVR, ESP32, or RTOS environments.

## File Structure

* `main.c` – Contains the complete implementation of the elevator scheduling logic.
* `README.md` – Documentation for understanding, running, and extending the project.

## Running the Program

1. Compile using any C compiler:

   ```
   gcc main.c -o elevator
   ```

2. Run the executable:

   ```
   ./elevator
   ```

3. Follow on-screen prompts to:

   * Add hall calls
   * Advance simulation steps
   * Check elevator status


