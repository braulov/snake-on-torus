
# Snake on a Torus Game Engine

This repository contains the implementation of a "Snake on a Torus" game engine and various algorithms to solve the game under different strategies. The game operates on a toroidal grid where the snake 1x1 moves to reach an apple 1x1, wrapping around the grid edges as needed. The engine supports multiple solving strategies, from spiral searches to random walks.

## Features

- **Toroidal Grid**: The snake navigates a grid where moving off one edge wraps around to the opposite side.
- **Game State Tracking**: Includes functionality to track the snake's position, apple's position, number of steps taken, and game completion status.
- **Multiple Solving Strategies**: Includes 5 different strategies, more details are provided in the **Solvers** section. Main solution - **mixSolve**().
- **Performance Analysis**: Tests different strategies over multiple randomized game setups and evaluates their efficiency.

## Getting Started

### Prerequisites

- A C++ compiler supporting C++17 or later.
- Standard libraries for building and running the code.

### Compilation

Use the following command to compile the program:
```bash
g++ -std=c++17 -O2 -o snake_on_torus main.cpp
```

### Running the Program

After compilation, execute the program:
```bash
./snake_on_torus
```

The program will run 100 test cases with n = 1001, m = 1001 by default and evaluate the performance of the mixed strategy (`mixSolve`). Results include:
- **Average ratio of steps to grid size (S = n * m)**.
- **Number of tests where steps exceeded 35 times the grid size.**

### Example Output

```text
Average ratio steps/S = 0.02345
Number of tests with steps > 35S = 0
```

## Code Structure

### `engine` Class
The core of the game engine:
- Tracks the snake's and apple's positions.
- Handles movement commands with edge wrapping.
- Maintains step counts and game completion status.
- Prints the game field for visualization.

### Solvers
Each solver implements a different strategy for navigating the grid:
- `spiralSolve`: Explores the grid in a spiral pattern.
- `randomWalk4`: Randomly selects from all four directions. (When proving performance estimates, this strategy actively utilized insights from [this article](https://www.cse.cuhk.edu.hk/~cslui/CMSC5734/LovaszRadnomWalks93.pdf). It is an excellent paper providing an overview of numerous fascinating concepts.)
- `randomWalk2`: Randomly selects between UP and RIGHT.
- `coprimeCase`: Moves diagonally, useful for specific grid configurations.
- `mixSolve`: Combines structured and random movements for a flexible approach.

### Testing Framework
The program runs multiple test cases with:
- Randomized grid dimensions.
- Random initial positions for the snake and the apple.

### Performance Metrics
- **Steps/S**: Measures efficiency by comparing steps taken to the grid size.
- **Excessive Step Count**: Tracks instances where the solver takes significantly more steps than expected.
