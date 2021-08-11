# Genetic Algorithm
A C implementation of a genetic algorithm to solve the N-Queens problem, using some functions of the GNU Scientific Library.
## Dependencies
* libgsl-dev
* libplot-dev

## Compilation

```bash
sudo apt install libgsl-dev libplot-dev
make
```

## Examples
To run the program for 8 queens, a population size of 10, a maximum generations of 50, a mutation probability of 0.2, a crossing probability of 0.8, roulette selection and print solution to file **solution.png**, do:

```bash
./genalg -i
```
**output**:

```bash
Solution found at generation #36
With queens = 8
Solution: [ 3, 6, 8, 2, 4, 1, 7, 5 ]
[ ][ ][Q][ ][ ][ ][ ][ ]
[ ][ ][ ][ ][ ][Q][ ][ ]
[ ][ ][ ][ ][ ][ ][ ][Q]
[ ][Q][ ][ ][ ][ ][ ][ ]
[ ][ ][ ][Q][ ][ ][ ][ ]
[Q][ ][ ][ ][ ][ ][ ][ ]
[ ][ ][ ][ ][ ][ ][Q][ ]
[ ][ ][ ][ ][Q][ ][ ][ ]
```
![solution1](/imgs/solution.png)


Run the algorithm with 8 queens, a population size of 20, a maximum generations of 150, a mutation probability of 0.3, a crossing probability of 0.7, roulette selection and show verbose output, do:

```bash
./genalg -p 20 -g 150 -m 0.3 -v
```

**output**:

```bash
Queens: 8
Population size: 20
Maximum generations before stop: 150
Selection: Roulette
Mutation probability: 0.30
Crossover probability: 0.70
Verbose output: True

Generation: 1
fitness = [ 6, 3, 4, 4, 2, 2, 2, 5, 4, 5, 3, 5, 5, 4, 6, 1, 3, 3, 4, 3 ]

Generation: 2
fitness = [ 5, 4, 4, 3, 4, 3, 2, 5, 4, 2, 4, 2, 4, 3, 3, 5, 4, 3, 3, 3 ]

Generation: 3
fitness = [ 4, 3, 5, 4, 4, 2, 2, 4, 4, 4, 4, 5, 2, 3, 3, 1, 4, 1, 3, 6 ]

Generation: 4
fitness = [ 2, 1, 3, 1, 4, 3, 6, 4, 4, 3, 2, 3, 3, 3, 4, 5, 2, 5, 3, 1 ]

Generation: 5
fitness = [ 3, 4, 3, 1, 4, 4, 1, 1, 2, 4, 3, 1, 3, 3, 4, 3, 3, 3, 4, 5 ]

Generation: 6
fitness = [ 1, 1, 3, 4, 1, 3, 3, 4, 3, 1, 3, 3, 4, 3, 3, 3, 1, 4, 6, 4 ]

Generation: 7
fitness = [ 3, 2, 3, 4, 1, 6, 3, 4, 3, 1, 4, 3, 4, 2, 3, 1, 1, 3, 1, 4 ]

Generation: 8
fitness = [ 2, 3, 3, 3, 3, 3, 1, 3, 3, 3, 2, 3, 3, 3, 3, 3, 5, 2, 1, 1 ]

Generation: 9
fitness = [ 3, 1, 3, 3, 2, 3, 3, 3, 4, 4, 2, 3, 2, 3, 3, 3, 3, 1, 4, 3 ]

Generation: 10
fitness = [ 3, 3, 3, 3, 3, 2, 2, 6, 2, 3, 4, 3, 4, 3, 2, 3, 5, 6, 1, 3 ]

Generation: 11
fitness = [ 3, 3, 3, 5, 3, 3, 6, 3, 5, 3, 4, 3, 4, 2, 2, 3, 4, 2, 4, 3 ]

Generation: 12
fitness = [ 3, 5, 4, 4, 4, 4, 5, 1, 6, 4, 2, 2, 3, 6, 4, 3, 4, 3, 3, 4 ]

Generation: 13
fitness = [ 2, 5, 3, 2, 3, 3, 5, 4, 4, 3, 4, 2, 5, 4, 4, 2, 2, 7, 4, 4 ]

Generation: 14
fitness = [ 4, 3, 3, 4, 3, 4, 5, 4, 4, 1, 5, 2, 2, 2, 2, 3, 2, 2, 6, 3 ]

Generation: 15
fitness = [ 4, 5, 4, 3, 6, 4, 3, 4, 2, 3, 4, 5, 4, 3, 4, 3, 2, 4, 4, 4 ]

Generation: 16
fitness = [ 4, 4, 5, 2, 3, 4, 5, 3, 3, 5, 6, 4, 4, 3, 3, 2, 3, 2, 4, 2 ]

Generation: 17
fitness = [ 6, 5, 2, 6, 4, 3, 6, 2, 4, 2, 2, 2, 2, 1, 3, 2, 2, 2, 4, 4 ]

Generation: 18
fitness = [ 5, 3, 6, 4, 4, 6, 4, 2, 1, 4, 2, 2, 2, 2, 2, 3, 3, 2, 2, 2 ]

Generation: 19
fitness = [ 4, 4, 2, 1, 3, 2, 4, 6, 4, 4, 2, 3, 1, 3, 4, 3, 3, 2, 2, 4 ]

Generation: 20
fitness = [ 5, 4, 6, 0, 4, 4, 3, 4, 1, 4, 4, 4, 8, 5, 4, 4, 3, 6, 3, 5 ]

Solution found at generation #20
With queens = 8
Solution: [ 4, 7, 5, 3, 1, 6, 8, 2 ]
[ ][ ][ ][Q][ ][ ][ ][ ]
[ ][ ][ ][ ][ ][ ][Q][ ]
[ ][ ][ ][ ][Q][ ][ ][ ]
[ ][ ][Q][ ][ ][ ][ ][ ]
[Q][ ][ ][ ][ ][ ][ ][ ]
[ ][ ][ ][ ][ ][Q][ ][ ]
[ ][ ][ ][ ][ ][ ][ ][Q]
[ ][Q][ ][ ][ ][ ][ ][ ]
```

To show help and usage, do:

```bash
./genalg -h
```

# ToDo:
- [  ] Modify the **ga_solution** struct to save all posible solutions found for N-Queens(this implies modifying **ga_solver** function to not end on the first solution found, but find all of them without saving repeated solutions.).
- [  ] Modify **crossover** function to work with N-Queens.(current implementation only works with 8-Queens). Also modify the **draw_solution** function to draw N-Queens in an image.
- [  ] Implement more selection algorithms.
- [ x ] Save an image of the solution representation. A chessboard(NxN) with the queens in their places. And maybe also save an image of every individual from each generation. Like in: https://en.wikipedia.org/wiki/Eight_queens_puzzle

![Example 1](/imgs/example1.png)

![Example 2](/imgs/example2.png)
