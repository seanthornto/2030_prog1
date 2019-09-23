//  timer.h
//  declaration of a stopwatch class used to time code

//  declaration:  Timer Watch;       construct a watch set at 0.00 seconds
//  methods:      void Watch.Start();     starts the watch
//                void Watch.Stop();      stops the watch
//                double Watch.Time();    returns the current elapsed time
//                void Watch.Reset();     reset the elapsed time to 0.0 seconds

//  tom bailey  13 feb 98

#ifndef _timer_
#define _timer_

#include <ctime>

class Timer {
   public:
      Timer();
      ~Timer();

      void Start();
      void Stop();
      double Time();
      void Reset();
	 double returnElapsed() const;
   private:
      double Difference( clock_t stopTime, clock_t startTime );
      
      double elapsedTime;
      bool running;
      clock_t startTime;
   };
#include "timer.cpp"
#endif
