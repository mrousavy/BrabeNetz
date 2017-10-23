# Description
**This file explains all definitions and members important for the math of the network class.**

# Members
All Members of the `Network.cpp`/`Network.h` class:

* `layers_[][]`: An array of **all** layers (which contain _neurons_) in the **network**. _(double)_
  * **Note:**
  * `layers_[0]` would target the **input layer**.
  * `layers_[0][0]` would target the **first neuron**'s value (top one in topology) in the **input layer**.
* `biases_[][]`: An array of **biases for every neuron**. _(double)_
  * **Note:**
  * `biases_[0]` would target the **input layer's biases**.
  * `biases_[0][0]` would target the bias for the **first neuron** (top one in topology) in the **input layer**. (Every layer **but input layer** has biases)
* `weights_[][][]` An array of **weights between neurons**. _(double)_
  * **Note:**
  * `weights_[0]` would target the **input layer's weights** (or neurons in this case).
  * `weights_[0][0]` would target the weights going out from the **first neuron** (top one in topology) in the **input layer**.
  * `weights_[0][0][0]` would target the weight between the **first neuron** (top one in topology) in the **input layer** and the **first neuron** in the **next layer** _(first hidden layer)_.
* `topology_` An object representing the network's topology (containing **sizes & counts** and **weights**). _(network_topology)_
* `learn_rate_` A value indicating the learn rate of the network. _(double)_
  * **Note:**
  * This can be a constant: `0.1` or be updated after every train: `1 / (train_times + 1)`.
  * The higher the learn rate, the faster the network learns - but be aware your network will get unaccurate
* `layers_count_` The total count of layers in this network _(e.g.: Input + 3 Hidden + Output = 5 total)_. _(int)_
  * **Note:**
  * Mostly used to get last element in arrays. (`layers_count_ - 1`)


# Definitions
All compile time (`#define`) Definitions inside the `Globals.h` header file:

* `Network.h` (defined in `Globals.h`)
  * `LEARNING_RATE`: The default learning rate if none is manually set (`0.17`)
  * `STATE_FILE`: The default filepath to the network's state file (`"state.nn"`)
  * `FORCE_MULTITHREADED`: Force use of multithreading for Backwards-Propagation algorithm, only use on larger networks (hidden layers with >5 neurons) (Only in Release mode) (`false`)
  * `ITERS_PER_THREAD`: Amount of iterations in the Backwards-Propagation algorithm each thread is expected to do (`ITERS_PER_THREAD` * `core_count` are the minimum expected iterations of backprop to start multithreading instead of serial if `FORCE_MULTITHREADED` is false) (thread spawning takes ~270.000ns, the loop ~250ns) (`600`)
* `Trainer.cpp`
  * `CONST_LEARN_RATE`: Use a constant learn rate for training instead of using the thumb-rule formula (`true`)
  * `PRINT_OUTPUT`: Print the output of the training to console (use only for debug, I/O like printing is very slow, training will take ~0.02ms longer per iteration) (`true`)
  * `UPDATE_STATUS`: Update Titlebar of Console Window with status of iteration (i/total) (use only for debug, I/O like setting title is slow, training will take ~0.12ms longer per iteration) (`true`)
* `BrabeNetzConsole.cpp`:
  * `LOAD_STATE`: Load the network's state when starting the program instead of generating a new random network each time (`false`)
  * `TRAIN_TIMES_EACH`: Amount of times to train the network (depending on the training this has to scale, e.g. `4000 / 4` for XOR, so `1000` for each possibility) (`4000`)
