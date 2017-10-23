#include "stdafx.h"
#include "Trainer.h"
#include <iostream>
#include <fstream>
#include <bitset>

// Use a constant learn rate (LEARN_RATE) for training instead of small decreasing one
#define CONST_LEARN_RATE true
// Print the input, expected and actual output to console (that's hella slow!)
#define PRINT_OUTPUT true

typedef bitset<8> byte; // byte

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

// TODO: Fix MSB first (Little/Big endian)
void trainer::train_handwritten_digits(network& net, int train_times, const string mnist_images, const string mnist_labels)
{
	const string format = "File \"%s\" = %.3f\n";

	// Open streams
	ifstream images_stream(mnist_images, fstream::in | fstream::binary); // Open the images file
	ifstream labels_stream(mnist_labels, fstream::in | fstream::binary); // Open the labels file

	if (!images_stream.is_open() || !labels_stream.is_open()) // Check if exists
		throw "Images/Labels training file not found!";

	// First 32 bit: MAGIC NUMBER
	int32_t i_magic_number = 0;
	int32_t l_magic_number = 0;
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
			//image[p] = reinterpret_cast<double>(&pixel);
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
