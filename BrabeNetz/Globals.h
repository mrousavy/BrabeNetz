#pragma once

// --- Network.cpp:
// Default learning rate for the backpropagation weights/bias adjusting
#define LEARNING_RATE 0.17
// Filename for the state file
#define STATE_FILE "state.nn"
// Force use of multithreading for backpropagation (only use on larger layers, experiment yourself)
#define FORCE_MULTITHREADED false
// Amount of iterations each thread is expected to do (thread spawning takes ~270.000ns, the loop ~250ns)
#define ITERS_PER_THREAD 600