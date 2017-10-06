# BrabeNetz
**BrabeNetz** is a **neural network** written in **C++**, aiming to be **as fast as possible¹** by using **C arrays** and only **raw values instead of objects** _(May be hard to read because of that)_

**BrabeNetz** has **no bounds- or error-checking** for performance reasons, be careful what you feed it.

I've currently trained it to solve **XOR**.

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


¹: I'm new to C/C++ so; as fast as **I** can do it
