# Description
**This file explains all members important for the math of the network class.**

* `layers_[][]`: An array of **all** layers (which contain _neurons_) in the **network**. _(double)_
  * **Note:**
  * `layers_[0]` would target the **input layer**.
  * `layers_[0][0]` would target the **first neuron** (top one in topology) in the **input layer**.
* `biases_[][]`: An array of **biases for every neuron**. _(double)_
  * **Note:**
  * `biases_[0]` would target the **input layer's biases**.
  * `biases_[0][0]` would target the bias for the **first neuron** (top one in topology) in the **input layer**.
* `weights_[][][]` An array of **weights between neurons**. _(double)_
  * **Note:**
  * `weights_[0]` would target the **input layer's weights** (or neurons in this case).
  * `weights_[0][0]` would target the weights going out from the **first neuron** (top one in topology) in the **input layer**.
  * `weights_[0][0][0]` would target the weight between the **first neuron** (top one in topology) in the **input layer** and the **first neuron** in the **next layer** _(first hidden layer)_.
* `topology_` An object representing the network's topology (containing **sizes & counts** and **weights**). _(network_topology)_
* `learn_rate_` A value indicating the learn rate of the network. _(double)_
  * **Note:**
  * This can be a constant: `0.01` or be updated after every train: `1 / (train_times + 1)`.
  * The higher the learn rate, the faster the network learns - but be aware your network will get unaccurate
* `layers_count_` The total count of layers in this network _(e.g.: Input + 3 Hidden + Output = 5 total)_. _(int)_
  * **Note:**
  * Mostly used to get last element in arrays. (`layers_count_ - 1`)
