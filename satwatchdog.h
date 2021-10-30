#ifdef MYESP32
#include <esp_task_wdt.h>
#endif

#if defined(ARDUINO_PORTENTA_H7_M4) || defined(ARDUINO_PORTENTA_H7_M7)
#include <Watchdog.h>
#endif

#define WDT_TIMEOUT 3


/*
 * 
* A hardware watchdog timer that resets the system in the case of system
 * failures or malfunctions. If you fail to refresh the Watchdog timer periodically,
 * it resets the system after a set period of time.
 *
 * There is only one instance of the Watchdog class in the system, which directly maps to the hardware.
 * Use Watchdog::get_instance to obtain a reference.
 *
 * Watchdog::start initializes a system timer with a time period specified in
 * @a timeout param. This timer counts down and triggers a system reset
 * when it wraps. To prevent the system reset, you must periodically kick or refresh
 * the timer by calling Watchdog::kick, which resets the countdown
 * to the initial value.
 *
 * Example:
 * @code
 * Watchdog &watchdog = Watchdog::get_instance();
 * watchdog.start(500);
 *
 * while (true) {
      // kick watchdog regularly within provided timeout
      watchdog.kick();
      // Application code
 * }
 * @endcode
 *
 * @note Synchronization level: Interrupt safe
 */


class CSatWatchdog {
  public:
  CSatWatchdog(){}
  void setup(){};
  void loop(){
  #ifdef MYESP32
  //  if(lc%1000000==0)esp_task_wdt_reset();   
    #endif  
  }
};
