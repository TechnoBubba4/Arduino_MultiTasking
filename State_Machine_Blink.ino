
#include <TimerOne.h>  // can also use TimerThree instead (Mega ONLY!)
 
// Many Thanks go to --> https://github.com/PaulStoffregen/TimerOne
// Note: we're only using it for a cyclic interrupt source

//------------------------------------------------------------------------
//  Arduino State Machine MultiTasking 

//  Using a Timer1 interrupt to process multiple
//  global "software" counters.

// This example works only on the Arduino Mega,
// but can be modified for the other boards.

// The code:
// *  State Machine based execution
// *  Allows 'cooperative' multitasking while maintaining 'timing.
// *  Eliminates the '53' day overflow w. Millis

// created 13 Jan. 2016
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

unsigned int state_var = 1 ; // my 'state variable' actually an "index" for array

// 'state' array of pointers to functions
void (*st_array[10])(void) = {state0, state1, state2, state3} ;


void state0(void) {
  state_var++ ;
  return ;
}

void state1(void) {
  if (!TimR1) { // Is TimR1 == 0 ?
    digitalWrite( 22,  digitalRead( 22 ) ^ 1 ); // XOR and output
    TimR1 = 17 ;  // TimR1 started !
  }
  state_var++ ; //   increment state_var
  return ;
}

void state2(void) {
   if (!TimR2) { // Is TimR2 == 0 ?
    digitalWrite( 24,  digitalRead( 24 ) ^ 1 );
    TimR2 = 12 ;  // TimR2 started !
  }
  state_var++ ; //   increment state_var

  return ;
}

void state3(void) {
   if (!TimR3) { // Is TimR3 == 0 ?
    digitalWrite( 26,  digitalRead( 26 ) ^ 1 );
    TimR3 = 24 ;   // TimR3 started !
  }
  state_var = 1 ; // back to begin

  return ;
}

void setup()
{
 // Initialize the digital pins as output.
  pinMode(22, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(26, OUTPUT);

  void(*st_array[4])(void) = {state0} ; // can init individually or add states
  
  // Initialize the Timer1
  Timer1.initialize(100000); // set a timer of length 100000 microseconds
  //(or 0.1 sec - or 10Hz  )
  Timer1.attachInterrupt( timerIsr ); // attach the service routine here

}

void loop()
{
  // Main code loop
  // NOTE: instead of the "digitalWrite" a 'State Machine' is being called.

// The line below is a "dispatch" (call) to one of the pointers in the array
  st_array[state_var]( ) ;
 
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
