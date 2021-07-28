#pragma once
#include <chrono>

class Timer {
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
	std::chrono::duration<double, std::milli> duration;
public:
	Timer() {
	}

	void start() {
		startTime = std::chrono::high_resolution_clock::now();
	}

	void stop() {
		duration += std::chrono::high_resolution_clock::now() - startTime;
	}

	std::chrono::duration<double, std::milli> getDuration() {
		return duration;
	}

};
