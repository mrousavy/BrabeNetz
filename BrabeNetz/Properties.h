#pragma once

/// \brief A structure for holding properties to initialize the network with
struct properties
{
	/// \brief The default learn rate to begin with
	double def_learn_rate;

	/// \brief The minimum iterations a thread is
	/// expected to do to start spawning multiple
	/// threads on a backpropagation algorithm
	int iters_per_thread;

	/// \brief Force spawning multiple threads
	/// on the backpropagation algorithm
	/// (effectively ignores `iters_per_thread`)
	bool force_multithreaded;

	/// \brief The state file path to save the
	/// network's save on `network::save()` to
	std::string state_file;

	explicit properties(const double learn_rate = 0.01,
	                    const int iters_per_thread = 600,
	                    const bool force_multithreaded = false,
						std::string state_file = "state.nn")
		:	def_learn_rate(learn_rate), 
			iters_per_thread(iters_per_thread),
			force_multithreaded(force_multithreaded),
			state_file(state_file)
	{
		
	}

	~properties()
	{
		
	}
};