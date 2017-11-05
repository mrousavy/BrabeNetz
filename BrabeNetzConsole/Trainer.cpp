#include "stdafx.h"
#include "Trainer.h"
#include "Console.h"
#include "Helper.h"
#include <iostream>
#include <fstream>
#include <bitset>

// Use a constant learn rate (LEARN_RATE) for training instead of small decreasing one
#define CONST_LEARN_RATE true
// Print the input, expected and actual output to console (that's hella slow!)
#define PRINT_OUTPUT true
// Update Titlebar of Console Window with status of iteration (i/total)
#define UPDATE_STATUS true

typedef bitset<8> byte; // byte

/*
	Train the network to recognize a XOR input (recommended topology: {2,3,1})
*/
void trainer::train_xor(network& net, const int train_times)
{
	const string format = "{ %.0f, %.0f } = %.3f\n";

	double* zz = new double[2]{ 0,0 };
	double* zz_e = new double[1]{ 0 };
	double* oz = new double[2]{ 1,0 };
	double* oz_e = new double[1]{ 1 };
	double* zo = new double[2]{ 0,1 };
	double* zo_e = new double[1]{ 1 };
	double* oo = new double[2]{ 1,1 };
	double* oo_e = new double[1]{ 0 };

	for (int i = 0; i < train_times; i++) // Loop train_times (should be %4 = 0)
	{
#if !CONST_LEARN_RATE
		const double learn_rate = 1.0 / ((i / 4) + 1.0);
		net.set_learnrate(learn_rate);
#endif

		double* total_error = new double(0);
		double* output;

		switch (i % 4) // Train all 4 cases alternately
		{
		case 0:
			output = net.train(zz, zz_e, *total_error);
			if (PRINT_OUTPUT) printf(format.c_str(), zz[0], zz[1], output[0]);
			break;
		case 1:
			output = net.train(oz, oz_e, *total_error);
			if (PRINT_OUTPUT) printf(format.c_str(), oz[0], oz[1], output[0]);
			break;
		case 2:
			output = net.train(zo, zo_e, *total_error);
			if (PRINT_OUTPUT) printf(format.c_str(), zo[0], zo[1], output[0]);
			break;
		case 3:
		default:
			output = net.train(oo, oo_e, *total_error);
			if (PRINT_OUTPUT) printf(format.c_str(), oo[0], oo[1], output[0]);
			if (UPDATE_STATUS) console::set_title("XOR: " + to_string(i + 1) + "/" + to_string(train_times));
			break;
		}

		// Cleanup
		delete total_error;
	}

	// Cleanup
	delete[] zz;
	delete[] zz_e;
	delete[] oz;
	delete[] oz_e;
	delete[] zo;
	delete[] zo_e;
	delete[] oo;
	delete[] oo_e;
}

/*
	Train the network to recognize handwritten digits from the MNIST data set (recommended topology: {784,16,16,10})
*/
void trainer::train_handwritten_digits(network& net, const string mnist_images, const string mnist_labels)
{
	const string format = "\"%i\" = %i\n";

	// Open streams
	ifstream images_stream(mnist_images, fstream::in | fstream::binary); // Open the images file
	ifstream labels_stream(mnist_labels, fstream::in | fstream::binary); // Open the labels file

	if (!images_stream.good() || !labels_stream.good()) // Check if exists
		throw "Images/Labels training file not found!";

	// First 32 bit: MAGIC NUMBER
	int i_magic_number = read_int(images_stream);
	int l_magic_number = read_int(labels_stream);

	if (i_magic_number != 2051 || l_magic_number != 2049) // Check if valid
		throw "Images/Labels magic number not valid!";

	// 32 bit: ELEMENTS COUNT
	int images_count = read_int(images_stream);
	int labels_count = read_int(labels_stream);

	// 2x 32 bit: IMAGE ROWS/COLUMNS (PIXELS)
	int image_hpx = read_int(images_stream);
	int image_vpx = read_int(images_stream);
	const int pixels = image_hpx * image_vpx;
	double* total_error = new double();

	// TODO: label from previous train is current output - shifted by 1, why?
	for (int i = 0; i < images_count; i++) // loop through each image/label
	{
		uint8_t label = read_byte(labels_stream); // read 1 label (the expected image's number)
		double expected[10]; // Create empty array
		for (int i = 0; i < 10; i++) expected[i] = 0; // set every value to 0
		expected[label] = 1; // Set expected number to 1

		double* image = new double[pixels];
		for (int p = 0; p < pixels; p++) // Loop through each pixel on this image
		{
			uint8_t pixel = read_byte(images_stream); // read 1 pixel
			
			printf(pixel > 0 ? "X" : " ");
			if (p % 28 == 0) printf("\n");

			image[p] = (double)pixel;
		}
		printf("\n");

		double* output = net.train(image, expected, *total_error); // actually train the network
		auto output_l = highest_index(output, 10); // get the highest index of the output array (actual result)

		if (PRINT_OUTPUT) printf(format.c_str(), label, output_l);
		if (UPDATE_STATUS) console::set_title("Learning Characters: " + to_string(i + 1) + "/" + to_string(images_count));
		// cleanup
		delete[] image;
	}

	// cleanup
	delete total_error;
	images_stream.close();
	labels_stream.close();
}
