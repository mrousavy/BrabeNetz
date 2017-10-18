<p align="center">
   <h1 align="left">BrabeNetz</h1>
   <img align="right" src="Images/brain.png" alt="Brain - Image by medium.com" width=200>
</p>

**BrabeNetz** is a **supervised neural network** written in C++, aiming to be as fast as possible by using bare values instead of objects

**BrabeNetz** has no bounds- or error-checking for performance reasons, be careful what you feed it.

I've currently trained it to solve **XOR**, I'll train it to **recognize handwritten characters**.

Be sure to [read the network description](https://github.com/mrousavy/BrabeNetz/blob/master/DESCRIPTION.md)

## Benchmarks

<p align="center">
   <img align="center" src="Images/cout.png" alt="Console output with elapsed time (2ms)">
   <p align="center">Training a <b>XOR</b> 1000 times</p>
   <br/>
   <img align="center" src="Images/cpuload.png" alt="Using 24/24 cores in Taskmanager">
   <p align="center">Effectively using <b>all available cores</b></p>
</p>

## Goals
* [x] **Fast Feed-Forward** algorithm
* [x] **Fast Backwards-Propagation** algorithm
* [x] **Fast binary network state saving** via `state.nn` file (Weights, Biases, Sizes)
* [x] **Multithreaded** where worth the spawn-overhead (CPU: `std::thread` | GPU: OpenCL/CUDA)
* [x] **Scalability** (Neuron size, Layer count) - only limited by hardware

## Specs
* **Faster accessing** via `malloc`/`free` instead of `new`/`delete`, and **pointers** instead of `std::vector`
* Smart **multithreading** by [OpenMP](http://www.openmp.org/)
* **Easy to use** (Inputs, outputs)
* **Randomly generated values** to begin with
* Easily save/load with `network::save(string)`/`network::load(string)`
* **Sigmoid** squashing function
* **Biases** for each neuron
* `network_topology` helper objects for loading/saving state and inspecting network

## Usage
1. Constructors
    * `network(initializer_list<int>)`: Create a new neural network with the given topology vector and fill it with random numbers (`{ 2, 3, 4, 1}` = 2 Input, 3 Hidden, 4 Hidden, 1 Output **Neurons** - total of 4 layers)
    * `network(network_topology&)`: Create a new neural network with the given network topology and load_ it's values
    * `network(string)`: Create a new neural network with the given path to the `sate.nn` file and load it.

2. Functions
    * `double feed(double* input_values, int length, int& out_length)`: Feed the network `input_values` and return an array of output values (where `out_length` will be set to the length of returned output values, that's the size of the output layer in topology)
    * `double train(double* input_values, int length, double* expected_output)`: Feed the network `input_values` and compare predicted output with `expected_output`, **Backwards-Propagate** (adjust weights/biases) if needed. Returns the total error of the output layer.
    * `void save(string path)`: Save the current network state (topology, weights, biases) to disk (with the given path or default: `state.nn`)
    * `void set_learnrate(double value)`: Set the learn rate of the network (used by `train(..)` function). Should always be `1 / (total train times + 1)`

An example of this can be found [here](https://github.com/mrousavy/BrabeNetz/blob/master/BrabeNetz/__ConsoleEntry.cpp), and [here](https://github.com/mrousavy/BrabeNetz/blob/master/BrabeNetz/Trainer.cpp)
