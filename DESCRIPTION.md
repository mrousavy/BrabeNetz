# Description
**This file explains all definitions and members important for the math of the network class.**

# Members

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

* `Network.h`
  * `LEARNING_RATE`: The default learning rate if none is manually set (`0.1`)
  * `STATE_FILE`: The default filepath to the network's state file (`"state.nn"`)
  * `MULTITHREADED`: Use multithreading for Backwards-Propagation algorithm, only use on larger networks (hidden layers with >5 neurons) (Only in Release mode) (`true`)
* `Trainer.h`
  * `CONST_LEARN_RATE`: Use a constant learn rate for training instead of using the thumb-rule formula (`true`)
  * `PRINT_OUTPUT`: Print the output of the training to console (use only for debug, `cout` is very slow, training will take ~1500 times longer) (`false`)
* `__ConsoleEntry.cpp`:
  * `LOAD_STATE`: Load the network's state when starting the program instead of generating a new random network each time (`false`)
  * `TRAIN_TIMES_EACH`: Amount of times to train the network (depending on the training this has to scale) (`1000` for XOR)
