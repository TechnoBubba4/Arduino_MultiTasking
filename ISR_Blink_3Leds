
#include <TimerOne.h>  // can also use TimerThree instead (Mega ONLY!)

// Many Thanks go to --> https://github.com/PaulStoffregen/TimerOne
// Note: we're only using it for a cyclic interrupt source

//------------------------------------------------------------------------
//  Arduino MultiTasking w/o Millis

//  Using a Timer1 interrupt to process multiple 
//  global "software" counters.

// This example works only on the Arduino Mega,
// but can be modified for the other boards.

// The circuit:
// *  Allows 'cooperative' multitasking while maintaining 'timing.
// *  Eliminates the '53' day overflow w. Millis

// created 07 Jan. 2016
// by Vic Bojarski
// This example code is in the public domain.
 //------------------------------------------------------------------------
 
//--------------------------------------------------------------------
// These are "started" by setting them to a 'time' value
// max value is 65535 times 0.1 sec --> (6553 secs)
// These can be made 'unsigned long' if needed (at higher interrupt rates).
// (Don't confuse that with the hardware 16-bit resolution)
//--------------------------------------------------------------------

 unsigned int volatile TimR1 = 0 ;  
 unsigned int volatile TimR2 = 0 ;
 unsigned int volatile TimR3 = 0 ;

void setup()
{
  // Initialize the digital pins as output.
  pinMode(22, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(26, OUTPUT);

  // Initialize the Timer1
  Timer1.initialize(100000); // set a timer of length 100000 microseconds
  //(or 0.1 sec - or 10Hz  )
  Timer1.attachInterrupt( timerIsr ); // attach the service routine here

}

void loop()
{
  // Main code loop
  // NOTE: instead of the "digitalWrite" a more
  //  complex subroutine ( or 'State Machine' ) could be called.

  if (!TimR1) { // Is TimR1 == 0 ?
    digitalWrite( 22,  digitalRead( 22 ) ^ 1 ); // XOR and output
    TimR1 = 7 ;  // TimR1 started !  
  }
  if (!TimR2) { // Is TimR2 == 0 ?
    digitalWrite( 24,  digitalRead( 24 ) ^ 1 );  
    TimR2 = 10 ;  // TimR2 started !
  }
  if (!TimR3) { // Is TimR3 == 0 ?
    digitalWrite( 26,  digitalRead( 26 ) ^ 1 );  
    TimR3 = 14 ;   // TimR3 started !
  }



}

/// --------------------------
/// ISR Timer Routine
/// Please note: BY DECREMENTING WE AVOID THE 'OVERFLOW' PROBLEM.
///              EACH TIMER IS 'SELF-RESETTING'.
/// These can me made 'unsigned long' if more time (resolution) is needed or the
/// interrupt rate is higher.
/// --------------------------
void timerIsr()
{
  if (TimR1)
    TimR1-- ; // Only decrement if non-zero !!!!!!!!!!!!
  if (TimR2)
    TimR2-- ; // Analogy is that of an "egg-timer" which self resets!!!!!
  if (TimR3)  // Can add more "egg-timers" if needed.
    TimR3-- ;
}
