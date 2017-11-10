#pragma once
#include "../BrabeNetz/Network.h"

/// <summary>
/// A Neuronal Network Trainer supporting bools
/// </summary>
class trainer
{
public:
	// Teach the network XOR switches, return duration it took in microseconds
	static long long train_xor(network& net, int train_times);
	// Train the network to recognize handwritten digits, return duration it took in microseconds
	static long long train_handwritten_digits(network& net, string mnist_images, string mnist_labels);
};
