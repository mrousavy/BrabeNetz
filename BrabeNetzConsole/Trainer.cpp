#include "stdafx.h"
#include "Trainer.h"
#include "Console.h"
#include "Helper.h"

#include <vector>

using namespace std;

// Use a constant learn rate (LEARN_RATE) for training instead of small decreasing one
#define CONST_LEARN_RATE true
// Print the input, expected and actual output to console (that's hella slow!)
#define PRINT_OUTPUT true
// Update Titlebar of Console Window with status of iteration (i/total)
#define UPDATE_STATUS true

/*
	Train the network to recognize a XOR input (recommended topology: {2,3,1})
	This example shows how to use the polished brabenetz.h interface
*/
long long trainer::train_xor(brabenetz& net, const int train_times)
{
	const string format = "{ %.0f, %.0f } = %.3f | e=%.3f\n";

	vector<double> zz{ 0,0 };
	vector<double> zz_e{ 0 };
	vector<double> oz{ 1,0 };
	vector<double> oz_e{ 1 };
	vector<double> zo{ 0,1 };
	vector<double> zo_e{ 1 };
	vector<double> oo{ 1,1 };
	vector<double> oo_e{ 0 };

	const auto train_start = chrono::high_resolution_clock::now();
	for (int i = 0; i < train_times; i++) // Loop train_times (should be %4 = 0)
	{
		#if !CONST_LEARN_RATE
		const double learn_rate = 1.0 / ((i / 4) + 1.0);
		net.set_learnrate(learn_rate);
		#endif

		double total_error;
		vector<double> output;
		network_result* result = nullptr;

		switch (i % 4) // Train all 4 cases alternately
		{
			case 0:
			{
				auto x = zz.data();
				auto result = net.feed(zz);
				total_error = result.adjust(zz_e);
				if (PRINT_OUTPUT) printf(format.c_str(), zz[0], zz[1], output[0], total_error);
				break;
			}
			case 1:
			{
				auto result = net.feed(oz);
				total_error = result.adjust(oz_e);
				if (PRINT_OUTPUT) printf(format.c_str(), oz[0], oz[1], output[0], total_error);
				break;
			}
			case 2:
			{
				auto result = net.feed(zo);
				total_error = result.adjust(zo_e);
				if (PRINT_OUTPUT) printf(format.c_str(), zo[0], zo[1], output[0], total_error);
				break;
			}
			case 3:
			default:
			{
				auto result = net.feed(oo);
				total_error = result.adjust(oo_e);
				if (PRINT_OUTPUT) printf(format.c_str(), oo[0], oo[1], output[0], total_error);
				if (UPDATE_STATUS) console::set_title("XOR: " + to_string(i + 1) + "/" + to_string(train_times));
				break;
			}
		}
	}
	const auto train_finish = chrono::high_resolution_clock::now();

	return std::chrono::duration_cast<chrono::microseconds>(train_finish - train_start).count();
}

/*
	Train the network to recognize handwritten digits from the MNIST data set (recommended topology: {784,16,16,10})
	This example shows how to use the raw network.h interface (is a bit faster)
*/
long long trainer::train_handwritten_digits(network& net, const string mnist_images, const string mnist_labels)
{
	const string format = "\"%i\" = %i\n";

	printf("Loading training sets from disk... (%s & %s)\n", mnist_images.c_str(), mnist_labels.c_str());

	// Open streams
	ifstream images_stream(mnist_images, fstream::in | fstream::binary); // Open the images file
	ifstream labels_stream(mnist_labels, fstream::in | fstream::binary); // Open the labels file

	if (!images_stream.good() || !labels_stream.good()) // Check if exists
		throw runtime_error("Images/Labels training file not found! Download and unzip from http://yann.lecun.com/exdb/mnist");

	// First 32 bit: MAGIC NUMBER
	const int i_magic_number = read_int(images_stream);
	const int l_magic_number = read_int(labels_stream);

	if (i_magic_number != 2051 || l_magic_number != 2049) // Check if valid
		throw runtime_error("Images/Labels magic number not valid!");

	// 32 bit: ELEMENTS COUNT
	const int images_count = read_int(images_stream);
	const int labels_count = read_int(labels_stream);

	// 2x 32 bit: IMAGE ROWS/COLUMNS (PIXELS)
	const int image_hpx = read_int(images_stream);
	const int image_vpx = read_int(images_stream);
	const auto pixels = image_hpx * image_vpx;
	const auto total_error = new double();

	const auto images = new double*[images_count]; // Images (in memory)
	const auto labels = new uint8_t[labels_count];

	// Load into memory
	for (int i = 0; i < images_count; i++) // loop through each image/label
	{
		labels[i] = read_byte(labels_stream); // read 1 label (the expected image's number)

		double* image = new double[pixels];
		for (int p = 0; p < pixels; p++) // Loop through each pixel on this image
		{
			image[p] = static_cast<double>(read_byte(images_stream)); // read 1 pixel
		}

		images[i] = image; // Push loaded image back to memory
	}

	printf("60000/60000 training sets loaded, starting training...\n");

	const auto train_start = chrono::high_resolution_clock::now();
	for (int i = 0; i < images_count; i++) // loop through each image/label
	{
		const uint8_t label = labels[i];
		double* image = images[i];

		double expected[10]; // Create empty array
		for (int ii = 0; ii < 10; ii++) expected[ii] = 0; // set every value to 0
		expected[label] = 1; // Set expected number to 1, all others are 0

		// Remove if not necessary
		if (PRINT_OUTPUT)
		{
			for (int p = 0; p < 784; p++)
			{
				printf(image[p] > 0 ? "X" : " ");
				if (p % 28 == 0) printf("\n");
			}
			printf("\n");
		}

		double* output = net.feed(image, true); // feed forward
		net.adjust(expected); // backprop
		const int output_l = highest_index(output, 10); // get the highest index of the output array (actual result)

		if (PRINT_OUTPUT) printf(format.c_str(), label, output_l);
		if (UPDATE_STATUS) console::set_title("Learning Characters: " + to_string(i + 1) + "/" + to_string(images_count));
		// cleanup
		delete[] image;
	}
	const auto train_finish = chrono::high_resolution_clock::now();

	// cleanup
	delete total_error;
	delete[] images;
	delete[] labels;
	images_stream.close();
	labels_stream.close();

	return std::chrono::duration_cast<chrono::microseconds>(train_finish - train_start).count();
}
