//  timer.cpp
//  definition of a stopwatch class used to time code

//  declaration:  Timer Watch;       construct a watch set at 0.00 seconds
//  methods:      void Watch.Start();     starts the watch
//                void Watch.Stop();      stops the watch
//                double Watch.Time();    returns the current elapsed time
//                void Watch.Reset();     reset the elapsed time to 0.0 seconds

//  tom bailey  13 feb 98

#include "timer.h"

Timer::Timer():
   elapsedTime( 0.0 ), running( false ) {
   }

Timer::~Timer() {
   }

void
Timer::Start() {
   if( !running ) {
      startTime = clock();
      running = true;
      }
   }

void
Timer::Stop() {
   clock_t stopTime;
   if( running ) {
      stopTime = clock();
      running = false;
      elapsedTime += Difference( stopTime, startTime );
      }
   }

double
Timer::Time() {
   if( running ) {
      Stop();
      Start();
      }
   return elapsedTime;
   }

void
Timer::Reset() {
   if( running ) {
      Stop();
      elapsedTime = 0.0;
      Start();
      }
   else
      elapsedTime = 0.0;
   }

double
Timer::Difference( clock_t stopTime, clock_t startTime ) {
   return double( stopTime - startTime ) / double( CLOCKS_PER_SEC );
   }

double Timer::returnElapsed() const
{
	return elapsedTime;
}
