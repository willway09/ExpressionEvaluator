#pragma once
#include <chrono>

class Timer {
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
	std::chrono::duration<double, std::milli> duration;
public:
	Timer() {
	}

	// set startTime to current time and in stop() we take the difference of these times and store it in duration
	void start() {
		startTime = std::chrono::high_resolution_clock::now();
	}

	// also works if you want to start the timer again and stop it again (it adds up the time cumulatively)
	void stop() {
		duration += std::chrono::high_resolution_clock::now() - startTime;
	}

	std::chrono::duration<double, std::milli> getDuration() {
		return duration;
	}

};
