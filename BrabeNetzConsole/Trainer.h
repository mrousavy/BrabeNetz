#pragma once
#include "../BrabeNetz/Network.h"
#include "../BrabeNetz/Globals.h"

/// <summary>
/// A Neuronal Network Trainer supporting bools
/// </summary>
class trainer
{
public:
	// Teach the network XOR switches
	static void train_xor(network& net, int train_times);
	// Train the network to recognize handwritten digits
	static void train_handwritten_digits(network& net, int train_times, string mnist_images, string mnist_labels);
};
