#pragma once
#include <SDL_hints.h>

class Timer
{
	    public:
		//Initializes variables
		Timer();

		//The various clock actions
		void start();
		void stop();
		void pause();
		void unpause();

		//Gets the timer's time
		Uint32 getTicks() const;

		//Checks the status of the timer
		bool isStarted() const;
		bool isPaused() const;

    private:
		//The clock time when the timer started
		Uint32 startTicks;

		//The ticks stored when the timer was paused
		Uint32 pausedTicks;

		//The timer status
		bool paused;
		bool started;
};
