/*!
  \file
  \brief Implements a centralized trace class
  \author Flying Domoticz
  \date April 8th, 2023

	Have a look at FF_Trace.cpp for more details
	
*/
#ifndef FF_TRACE_H
	#define FF_TRACE_H
	#pragma once

	#include "Arduino.h"

	// Maximum number of callback routines
	#define FF_TRACE_MAX_TRACE 5

  /*!
  
      Define supported levels
      
   */
   typedef enum {
  		FF_TRACE_LEVEL_NONE,       	//!< No trace output
  		FF_TRACE_LEVEL_ERROR,      	//!< Critical errors (usually aborting current action)
  		FF_TRACE_LEVEL_WARN,       	//!< Warning messages (usually not aborting)
  		FF_TRACE_LEVEL_INFO,       	//!< Information messages
  		FF_TRACE_LEVEL_DEBUG,      	//!< Debug information
  		FF_TRACE_LEVEL_VERBOSE     	//!< Extra verbose information
   } traceLevel_t;

  /*!

      Define callback type

      \param _level: level associated to message
      \param _message: message to send/display
      
   */
  typedef void (traceCallback_t)(const traceLevel_t _level, const char* _message);

	#ifdef __cplusplus
  /*! \class FF_Trace
      \brief Implements a centralized trace class
  
      This class allows to have a centralized place to display trace message on multiple supports.
        Message is sent by anycode having something to report using trace.printf() call.
        Class with then generate message and send it to any routine declared by trace.registerCallback().
        Routine could then look at message level and message contents to decide if it should display it (or not).
        
  */
  class FF_Trace {
		public:
			FF_Trace();
			void registerCallback(const traceCallback_t _callback);
			void printf(const traceLevel_t _level, const char* _format, ...);
			void setLevel(const traceLevel_t _level);
			traceLevel_t getLevel(void);
		private:
			traceCallback_t *callbacks[FF_TRACE_MAX_TRACE];
			traceLevel_t currentLevel;
	};
	#endif

#endif
