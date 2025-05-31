# 42 Philosophers

This project is part of the curriculum at 42 Paris. It simulates the classic "Dining Philosophers" problem using multithreading and synchronization in C.

## Overview

The goal is to create a program that launches multiple philosopher threads that alternate between **thinking**, **eating**, and **sleeping**. The challenge is to avoid deadlocks and starvation while ensuring all philosophers get enough time to eat.

## Features

- Implementation of the **Dining Philosophers problem** with threads and mutexes.
- Handles timing and synchronization correctly to avoid race conditions.
- Includes the **bonus** part:
  - Added an optional argument to limit the number of times each philosopher must eat.
  - Properly terminates the simulation once all philosophers have eaten the required times.

## Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
