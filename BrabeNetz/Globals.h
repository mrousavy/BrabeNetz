#pragma once

// --- Network.cpp:
// Default learning rate for the backpropagation weights/bias adjusting
#define LEARNING_RATE 0.17
// Filename for the state file
#define STATE_FILE "state.nn"
// Force use of multithreading for backpropagation (only use on larger layers, experiment yourself)
#define FORCE_MULTITHREADED false
// Minimum Neurons in a layer to start multithreading instead of serial
#define MIN_NEURONS_MULTITHREAD 10
// Amount of iterations each thread is expected to do
#define ITERS_PER_THREAD 4

// --- Trainer.cpp:
// Use a constant learn rate (LEARN_RATE) for training instead of small decreasing one
#define CONST_LEARN_RATE true
// Print the input, expected and actual output to console (that's hella slow!)
#define PRINT_OUTPUT true