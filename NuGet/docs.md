# BrabeNetz
> 🌐 A fast and clean supervised neural network in C++, capable of effectively using multiple cores 🧠

## Usage
1. Build & link library
    * See: [build/link instructions](https://github.com/mrousavy/BrabeNetz/blob/master/BUILD.md)

2. Choose your interface
	1. `brabe_netz.h`: _[Recommended]_ A wrapper for the raw `network.h` interface, but with **error handling** and **modern C++ interface** styling such as `std::vector`s, `std::exception`s, etc.
	2. `network.h`: The raw `network` with C-style arrays and no bound/error checking. **Only use this if _performance_ is important.**

3. Constructors
    1. `(initializer_list<int>, properties)`: Construct a new neural network with the given network size (e.g. `{ 2, 3, 4, 1 }`) and randomize all base weights and biases - [ref](https://github.com/mrousavy/BrabeNetz/blob/master/BrabeNetz/BrabeNetz.h#L86)
    2. `(network_topology&, properties)`: Construct a new neural network with the given network topology and import it's existing weights and biases - [ref](https://github.com/mrousavy/BrabeNetz/blob/master/BrabeNetz/BrabeNetz.h#L89)
    3. `(string, properties)`: Construct a new neural network with and load the neural network state from the file specified in `properties.state_file` - [ref](https://github.com/mrousavy/BrabeNetz/blob/master/BrabeNetz/BrabeNetz.h#L110)

4. Functions
    1. `network_result brabe_netz::feed(std::vector<double>& input_values)`: Feed the network input values and forward propagate through all neurons to estimate a possible output (Use the `network_result` structure ([ref](https://github.com/mrousavy/BrabeNetz/blob/master/BrabeNetz/BrabeNetz.h#L11)) to access the result of the forward propagation, such as `.values` to view the output) - [ref](https://github.com/mrousavy/BrabeNetz/blob/master/BrabeNetz/BrabeNetz.h#L134)
    2. `double network_result::adjust(std::vector<double>& expected_output)`: Backwards propagate through the whole network to adjust wrong neurons for result trimming and return the total network error - [ref](https://github.com/mrousavy/BrabeNetz/blob/master/BrabeNetz/BrabeNetz.h#L48)
    3. `void save(string path)`: Save the network's state to disk by serializing weights
    4. `void set_learnrate(double value)`: Set the network's learning rate. It is good practice and generally recommended to use one divided by the train count, so the learn rate decreases the more often you train - [ref](https://github.com/mrousavy/BrabeNetz/blob/master/BrabeNetz/BrabeNetz.h#L156)
    5. `network_topology& build_topology()`: Build and set the network topology object of the current network's state (can be used for network visualization or similar) - [ref](https://github.com/mrousavy/BrabeNetz/blob/master/BrabeNetz/BrabeNetz.h#L166)

Usage examples can be found [here](https://github.com/mrousavy/BrabeNetz/blob/master/BrabeNetzConsole/BrabeNetzConsole.cpp), and [here](https://github.com/mrousavy/BrabeNetz/blob/master/BrabeNetzConsole/Trainer.cpp)