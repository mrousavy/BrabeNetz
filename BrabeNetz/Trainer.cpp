#include "stdafx.h"
#include "Trainer.h"
#include <iostream>
#include <fstream>
#include <bitset>

typedef bitset<8> byte; // byte

void trainer::train_xor(network& net, const int train_times)
{
	const int size = 2;
	double* values;
	double* expected = new double[1];

	for (int i = 0; i < train_times * 4; i++) // Loop train_times (1000) * possibilities for XOR (4)
	{
		switch (i % 4) // Train all 4 cases alternately
		{
			case 0:
				values = new double[size] { 0, 0 };
				expected[0] = 0;
				break;
			case 1:
				values = new double[size] { 1, 0 };
				expected[0] = 1;
				break;
			case 2:
				values = new double[size] { 0, 1 };
				expected[0] = 1;
				break;
			case 3:
			default:
				values = new double[size] { 1, 1 };
				expected[0] = 0;
				break;
		}

		#if !CONST_LEARN_RATE
		const double learn_rate = 1.0 / (i + 1.0);
		net.set_learnrate(learn_rate);
		#endif

		double* total_error = new double(0);
		const double* output = net.train(values, expected, *total_error);

		if (PRINT_OUTPUT)
			cout << "{ " << values[0] << ", " << values[1] << " } = " << output[0] << " | Error: " << *total_error << endl;

		// Cleanup
		delete[] values;
		delete total_error;
	}
	delete[] expected;
}

void trainer::train_handwritten_digits(network& net, int train_times, const string mnist_images, const string mnist_labels)
{
	// Open streams
	ifstream images_stream(mnist_images, fstream::in | fstream::binary); // Open the images file
	ifstream labels_stream(mnist_labels, fstream::in | fstream::binary); // Open the labels file

	if (!images_stream || !labels_stream) // Check if exists
		throw "Images/Labels training file not found!";

	// First 32 bit: MAGIC NUMBER
	int i_magic_number = 0;
	int l_magic_number = 0;
	images_stream.read(reinterpret_cast<char*>(&i_magic_number), sizeof(i_magic_number));
	labels_stream.read(reinterpret_cast<char*>(&l_magic_number), sizeof(l_magic_number));

	// 32 bit: ELEMENTS COUNT
	int images_count = 0;
	int labels_count = 0;
	images_stream.read(reinterpret_cast<char*>(&images_count), sizeof(images_count));
	labels_stream.read(reinterpret_cast<char*>(&labels_count), sizeof(labels_count));

	if (images_count != labels_count)
		throw "Images count != Labels count - Aborting!";

	// 2x 32 bit: IMAGE ROWS/COLUMNS (PIXELS)
	int image_hpx = 0;
	int image_vpx = 0;
	images_stream.read(reinterpret_cast<char*>(&image_hpx), sizeof(image_hpx));
	images_stream.read(reinterpret_cast<char*>(&image_vpx), sizeof(image_vpx));
	const int pixels = image_hpx * image_vpx;

	for (int i = 0; i < images_count; i++) // loop through each image/label
	{
		byte label;
		labels_stream.read(reinterpret_cast<char*>(&label), sizeof(label)); // read 1 label

		double* image = new double[pixels];
		for (int p = 0; p < pixels; p++) // Loop through each pixel on this image
		{
			byte pixel;
			labels_stream.read(reinterpret_cast<char*>(&pixel), sizeof(pixel)); // read 1 pixel
			//image[p] = pixel;
		}

		double* total_error = new double();
		//net.train(image, label, *total_error);

		// cleanup
		delete total_error;
		delete[] image;
	}

	images_stream.close();
	labels_stream.close();
}
