# BrabeNetz
**BrabeNetz** is a **supervised neural network** written in **C++**, aiming to be **as fast as possible¹** by using **C arrays** and only **raw values instead of objects** _(May be hard to read because of that)_

**BrabeNetz** has **no bounds- or error-checking** for performance reasons, be careful what you feed it.

I've currently trained it to solve **XOR**.

You can **save the network's state to disk** with the `network::save(string)` function, and **load it on next startup**. An example of this can be found [here](https://github.com/mrousavy/BrabeNetz/blob/master/BrabeNetz/__ConsoleEntry.cpp).

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
    * `network(initializer_list<int>)`: Create a new neural network with the given **topology vector** and _fill it_ with random numbers (`{ 2, 3, 4, 1}` = _2_ Input, _3_ Hidden, _4_ Hidden, _1_ Output)
    * `network(network_topology&)`: Create a new neural network with the given **network topology** and _load_ it's values
    * `network(string)`: Create a new neural network with the given path to the `sate.nn` file and _load it_. _(See `network_topology::load(string)` for more info)_

2. Functions
    * `double train(double* input_values, int length, int& out_length)`: **Feed** the network `input_values` and return an array of output values (size of **output layer** in topology) (where `out_length` will be set to the **length** of returned output values)
    * `double train(double* input_values, int length, double* expected_output)`: **Feed** the network `input_values` and **compare** _predicted output_ with `expected_output`, **Backwards-Propagate** (adjust _weights/biases_) if needed. **Returns** the total error of the output layer.
    * `void save(string path)`: Save the **current network state** _(topology, weights, biases)_ to **disk** (with the given path or default: `state.nn`)
    * `void set_learnrate(double value)`: Set the learn rate of the network (used by `train(..)` function). Should always be `1 / (total train times + 1)`


¹: I'm new to C/C++ so; as fast as **I** can do it
