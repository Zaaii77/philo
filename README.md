# Philosophers (philo)

`philo` is a multithreaded program simulating the dining philosophers problem, focusing on thread synchronization and resource sharing.

## Features
- Simulates the dining philosophers problem.
- Implements thread synchronization using mutexes.
- Handles resource contention (forks) and starvation prevention.
- Configurable parameters for the number of philosophers and timings.

## How to Build and Run
1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd philo
   ```

2. Compile the project:
   ```bash
   make
   ```

3. Run the program:
   ```bash
   ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_meals]
   ```

   Example:
   ```bash
   ./philo 5 800 200 200
   ```

## Parameters
- `<number_of_philosophers>`: Number of philosophers (and forks).
- `<time_to_die>`: Time (in milliseconds) a philosopher can live without eating.
- `<time_to_eat>`: Time (in milliseconds) a philosopher takes to eat.
- `<time_to_sleep>`: Time (in milliseconds) a philosopher spends sleeping.
- `[number_of_meals]` (optional): Number of meals each philosopher must eat before the simulation ends.

## Example Output
```bash
./philo 2 210 100 100 2
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
100 1 is sleeping
100 2 has taken a fork
100 2 has taken a fork
100 2 is eating
200 1 is thinking
200 2 is sleeping
200 1 has taken a fork
200 1 has taken a fork
200 1 is eating
...
Nice ! Each philosophers eat 2 time(s) !
```

## Notes
- The program uses mutexes to prevent race conditions.
- Philosophers alternate between eating, sleeping, and thinking.
- The simulation ends when all philosophers have eaten the required number of meals or one philosopher dies.

## License
This project is licensed under the MIT License.
