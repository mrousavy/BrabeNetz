# BrabeNetz
**BrabeNetz** is a **supervised neural network** written in **C++**, aiming to be **as fast as possible** by using **C arrays** and only **raw values instead of objects** _(May be hard to read because of that)_

**BrabeNetz** has **no bounds- or error-checking** for performance reasons, be careful what you feed it.

I've currently trained it to solve **XOR**, once I fix [this](https://github.com/mrousavy/BrabeNetz/issues/3), I'll train it to **recognize handwritten characters**.

Be sure to [read the network description](https://github.com/mrousavy/BrabeNetz/blob/master/DESCRIPTION.md)

## Benchmarks
It's pretty fast (TODO)

## Goals
* [x] **Fast Feed-Forward** algorithm
* [ ] **Fast Backwards-Propagation** algorithm
* [x] **Easy to use** (Inputs, outputs)
* [x] **C arrays** > `std::vector`
* [x] **Fast network state saving** via `state.nn` file (_Weights, Biases, Sizes_)
* [ ] **Multithreaded** if worth the spawn-overhead (`std::thread` or **NVIDIA CUDA**)
* [x] **Scalability** (Neuron size, Layer count) - only limited by **hardware**

## Specs
* **Randomly generated values** to begin with
* Easily save/load with `network::save(string)`/`network::load(string)`
* **Sigmoid** squashing function (TODO: **ReLU?**)
* **Biases** for each neuron
* `network_topology` helper objects **for loading/saving state** _(user friendly)_

## Usage
1. Constructors
    * `network(initializer_list<int>)`: Create a new neural network with the given **topology vector** and **fill it with random numbers** (`{ 2, 3, 4, 1}` = 2 Input, 3 Hidden, 4 Hidden, 1 Output **Neurons** - _total of 4 layers_)
    * `network(network_topology&)`: Create a new neural network with the given **network topology** and **load_ it's values**
    * `network(string)`: Create a new neural network with the given path to the `sate.nn` file and **load it**. _(See `network_topology::load(string)` for more info)_

2. Functions
    * `double train(double* input_values, int length, int& out_length)`: **Feed** the network `input_values` and return an array of output values (size of **output layer** in topology) (where `out_length` will be set to the **length** of returned output values)
    * `double train(double* input_values, int length, double* expected_output)`: **Feed** the network `input_values` and **compare** _predicted output_ with `expected_output`, **Backwards-Propagate** (adjust _weights/biases_) if needed. **Returns** the total error of the output layer.
    * `void save(string path)`: Save the **current network state** _(topology, weights, biases)_ to **disk** (with the given path or default: `state.nn`)
    * `void set_learnrate(double value)`: Set the learn rate of the network (used by `train(..)` function). Should always be `1 / (total train times + 1)`

An example of this can be found [here](https://github.com/mrousavy/BrabeNetz/blob/master/BrabeNetz/__ConsoleEntry.cpp), and [here](https://github.com/mrousavy/BrabeNetz/blob/master/BrabeNetz/Trainer.cpp)
