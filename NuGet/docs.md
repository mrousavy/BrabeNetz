# BrabeNetz
> 🌐 A fast and clean supervised neural network in C++, capable of effectively using multiple cores 🧠

## Usage
1. Build & link library
    * See: [build/link instructions](https://github.com/mrousavy/BrabeNetz/BUILD.md)

2. Constructors
    1. `network(initializer_list<int>, properties)`: Create a new neural network with the given topology vector and properties and fill it with random numbers (`{ 2, 3, 4, 1}` = 2 Input, 3 Hidden, 4 Hidden, 1 Output **Neurons** - total of 4 layers)
    2. `network(network_topology&, properties)`: Create a new neural network with the given network topology and load_ it's values
    3. `network(string, properties)`: Create a new neural network with the given path to the `sate.nn` file and load it

3. Functions
    1. `double* feed(double[] input_values)`: Feed the network `input_values` and return an array of output values (where the array's length is the size of the output layer in topology)
    2. `double* train(double[] input_values, double[] expected_output, double& out_total_error)`: Feed the network `input_values` and **backwards-propagate** to adjust the weights/biases and reduce error. Returns the output layer's values, `out_total_error` will be set to the total error of the output layer (This can be used to check if more training is needed)
    3. `void save(string path)`: Save the current network state (topology, weights, biases) to disk (with the given path or default: `state.nn`)
    4. `void set_learnrate(double value)`: Set the learn rate of the network (used by `train(..)` function). Should either be a constant (`0.5`) or `1 / (total train times + 1)`
    5. `network_topology& build_topology()`: Build and set the network topology object of the current network's state (Can be used for network visualization or similar)

Usage examples can be found [here](https://github.com/mrousavy/BrabeNetz/blob/master/BrabeNetzConsole/BrabeNetzConsole.cpp), and [here](https://github.com/mrousavy/BrabeNetz/blob/master/BrabeNetzConsole/Trainer.cpp)