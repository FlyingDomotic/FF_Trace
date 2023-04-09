/*!
  \file
  \brief Implements a centralized trace class
  \author Flying Domoticz
  \date April 8th, 2023

  This class allows to have a centralized place to display trace message on multiple supports.
    Message is sent by anycode having something to report using trace.printf() call.
    Class with then generate message and send it to all routines declared by trace.registerCallback().
    Routines could then look at message level and message contents to decide if it should display/send it (or not).
        
*/

#include "FF_Trace.h"

/// Class initialization
FF_Trace::FF_Trace() {
  // Clear all callbacks
  for (uint8_t i = 0; i < FF_TRACE_MAX_TRACE; i++) {
    callbacks[i] = NULL;
  }
  // Init level to info
  currentLevel = FF_TRACE_LEVEL_INFO;
}

/*!
    Register one callback to call when a message should be displayed

    /param _callback: callback routine to be called when a message is to be displayed
*/
void FF_Trace::registerCallback(const traceCallback_t _callback) {
  // Find an empty slot to insert callback
  for (uint8_t i = 0; i < FF_TRACE_MAX_TRACE; i++) {
    if (callbacks[i] == NULL) {
      callbacks[i] = _callback;
      return;
    }
    // No slot available, do nothing...
  }

}

/*!
 
    Send a message to all registered routines

    /param  _level: level associated to this message
    /param  _format: (printf) format string to use
    /param  ...: associated parameters (depends on format string contents)

*/
void FF_Trace::printf(const traceLevel_t _level, const char* _format, ...) {
  // Check level against internal one
  if (_level <= currentLevel) {
    // Make the message
    char msg[100];
    va_list arguments;
    va_start(arguments, _format);
    vsnprintf(msg, sizeof(msg), _format, arguments);
    va_end(arguments);
    // Call all registered callbacks
    for (uint8_t i = 0; i < FF_TRACE_MAX_TRACE; i++) {
      if (callbacks[i] != NULL) {
        (callbacks[i])(_level, msg);
      }
    }
  }
}

/*!
 
    Set current message level

    /param  _level: minimum level required to display message

*/
void FF_Trace::setLevel(const traceLevel_t _level) {
  // Save given level
  currentLevel = _level;
}

/*!
 
    Return current message level

    /return Current stored level

*/
traceLevel_t FF_Trace::getLevel(void) {
  // Return internal level
  return currentLevel;
}
