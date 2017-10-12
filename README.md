# BrabeNetz
**BrabeNetz** is a **supervised neural network** written in C++, aiming to be as fast as possible by using bare values instead of objects

**BrabeNetz** has no bounds- or error-checking for performance reasons, be careful what you feed it.

I've currently trained it to solve **XOR**, once I fix [this](https://github.com/mrousavy/BrabeNetz/issues/3), I'll train it to **recognize handwritten characters**.

Be sure to [read the network description](https://github.com/mrousavy/BrabeNetz/blob/master/DESCRIPTION.md)

## Benchmarks
It's pretty fast (TODO)

## Goals
* [x] **Fast Feed-Forward** algorithm
* [ ] **Fast Backwards-Propagation** algorithm
* [x] **Easy to use** (Inputs, outputs)
* [x] **Pointer arrays** instead of `std::vector`
* [x] **Fast binary network state saving** via `state.nn` file (Weights, Biases, Sizes)
* [ ] **Multithreaded** if worth the spawn-overhead (`std::thread` or NVIDIA CUDA)
* [x] **Scalability** (Neuron size, Layer count) - only limited by hardware

## Specs
* **Randomly generated values** to begin with
* Easily save/load with `network::save(string)`/`network::load(string)`
* **Sigmoid** squashing function (TODO: ReLU?)
* **Biases** for each neuron
* `network_topology` helper objects for loading/saving state and inspecting network (TODO: Remove totally?)

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
