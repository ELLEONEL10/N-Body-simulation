# N-body Simulation using the Barnes-Hut Algorithm

This project implements an N-body simulation using the Barnes-Hut algorithm in C++. The project includes both serial and parallel implementations.

## Table of Contents
- [Introduction](#introduction)
- [Physics Behind the Simulation](#physics-behind-the-simulation)
- [Algorithm Explanation](#algorithm-explanation)
- [Code Structure](#code-structure)
- [How to Build](#how-to-build)
- [How to Run](#how-to-run)
- [Acknowledgements](#acknowledgements)

## Introduction

The N-body problem involves predicting the motion of a group of celestial bodies that interact with each other gravitationally. This project aims to simulate these interactions using the Barnes-Hut algorithm to reduce computational complexity.

## Physics Behind the Simulation

### Newton's Law of Gravitation

The force \( F \) between two bodies with masses \( m_1 \) and \( m_2 \) separated by a distance \( r \) is given by:

\[ F = \frac{G \cdot m_1 \cdot m_2}{r^2} \]

where \( G \) is the gravitational constant.

## Algorithm Explanation

The Barnes-Hut algorithm approximates the effect of distant bodies using a quadtree (or octree in 3D). This allows us to treat a group of distant bodies as a single "super body" to reduce the number of calculations.

## Code Structure

- `body.h`: Defines the `Body` structure, representing a celestial body.
- `main_serial.cpp`: Contains the serial implementation of the Barnes-Hut N-body simulation.
- `main_parallel.cpp`: Contains the parallel implementation of the Barnes-Hut N-body simulation using OpenMP.
- `Makefile`: Used to compile both the serial and parallel versions of the simulation.

## How to Build

1. Ensure you have a C++ compiler installed.
2. Navigate to the project directory.
3. Run the following command to build both serial and parallel versions:
   ```sh
   ./nbody_serial
   ./nbody_parallel

## Acknowledgements

This project was implemented based on detailed explanations and examples provided in the course materials. Special thanks to the authors of the referenced materials for their comprehensive guides.

## License

This project is licensed under the MIT License.
