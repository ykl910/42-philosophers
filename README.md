# 42 Philosophers

This project is part of the 42 Paris curriculum and explores the classic **Dining Philosophers** problem.

## Overview

The project has two parts:

- **Mandatory:**  
  Uses **threads** and **mutexes** to simulate philosophers who alternate between thinking, eating, and sleeping. Synchronization ensures no deadlocks or starvation.

- **Bonus:**  
  Implements the same simulation using **processes** and **semaphores**, adding complexity by handling inter-process communication and synchronization.

## Features

- Multithreaded simulation with mutex synchronization (mandatory part).
- Process-based simulation using semaphores (bonus part).
- Correct handling of timing, synchronization, and termination conditions.
- Optional argument to specify the number of times each philosopher must eat.

## Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
