/*!
	\file
	\brief Implements a centralized trace class
	\author Flying Domotic
	\date April 11th, 2023
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
		FF_TRACE_LEVEL_NONE,		//!< No trace output
		FF_TRACE_LEVEL_ERROR,		//!< Critical errors (usually aborting current action)
		FF_TRACE_LEVEL_WARN,		//!< Warning messages (usually not aborting)
		FF_TRACE_LEVEL_INFO,		//!< Information messages
		FF_TRACE_LEVEL_DEBUG,		//!< Debug information
		FF_TRACE_LEVEL_VERBOSE		//!< Extra verbose information
	} traceLevel_t;

	/*!
		Define callback type
		\param _level: level associated to message
		\param _message: message to send/display
	*/

	typedef void (traceCallback_t)(const traceLevel_t _level, const char* _file, const uint16_t _line, const char* _function, const char* _message);

	#ifdef __cplusplus
	/*!	\class FF_Trace
		\brief Implements a centralized trace class

		This class allows to have a centralized place to display trace message on multiple supports.
			Message is sent by any code having something to report using printf() message format.
			Class will then generate message and send it to all routines declared by trace.registerCallback().
			Routines could then look at message level and message contents to decide if it should display/send it (or not).

		Even if you may use directly members of this class, it's highly recommended to use it through its macros
			in order to allow smooth changes in the future (like implementation of messages types that are in the tube).
			Doing so, you won't break you code when new functionalities will be added.

		Implementation in a project could be:
			- Declare class in main code using trace_declare().
			- Parts of code that are interested by getting trace message should declare them-self using trace_register() and trace_callback().
			- Messages are sent by trace_<level>(), where <level> can be error, warn, info, debug or verbose.

		Having multiple callbacks make sense if you want, for example, write messages to serial and send them to syslog and/or MQTT.

		You may also want to have only one callback to centralize messages and decide here what to do with them.

		As of now, the following macros are defined:
			trace_declare(): declare trace class, to be inserted in root source code.
			trace_register(callback): declare a callback routine to register
			trace_callback(callback): routine code to be called when a message has to be sent/printed.
			trace_setLevel(level): set minimum severity level of messages to be sent/printed. Can be FF_TRACE_LEVEL_NONE/ERROR/WARD/INFO/DEBUG/VERBOSE.
			trace_getLevel(): return minimum severity level of messages to be sent/printed. Can be any FF_TRACE_LEVEL_???
			trace_error(format, parameters...): print/send an error message (with printf syntax), using format and paramaters
			trace_warn(format, parameters...): print/send a warning message (with printf syntax), using format and paramaters
			trace_info(format, parameters...): print/send an information message (with printf syntax), using format and paramaters
			trace_debug(format, parameters...): print/send a debug message (with printf syntax), using format and paramaters
			trace_verbose(format, parameters...): print/send a verbose message (with printf syntax), using format and paramaters
			trace_xxxx_P(format, parameters...): PSTR version of messages

		Note that callback routine won't be called if message severity level if higher than current severity level set.

		Callback routines will be called with the following arguments:
			_level: severity level of message (can be any FF_TRACE_LEVEL_xxxx value)
			_file: calling source file name with extension
			_line: calling source file line
			_function: calling calling source function name
			_message: text message to send
	*/

	class FF_Trace {
		public:
			FF_Trace();
			void registerCallback(const traceCallback_t _callback);
			void printf(const traceLevel_t _level, const char* _file, const uint16_t _line, const char* _function, const char* _format, ...);
			void setLevel(const traceLevel_t _level);
			traceLevel_t getLevel(void);
		private:
			traceCallback_t *callbacks[FF_TRACE_MAX_TRACE];
			traceLevel_t currentLevel;
	};
	#endif

	/*
		Macros definition to insure compatibility with future versions
	*/

	/*!
		Set class implementation name
	*/
	#define FF_TRACE ffTrace

	/*!
		Declare class : To be used by root code to implement class
	*/
	#define trace_declare() FF_Trace FF_TRACE;

	/*!
		Declare a callback routine to be called for each message
		\param	routine: name of routine to be called when a message is to be sent/printed
	*/
	#define trace_register(callback) FF_TRACE.registerCallback(callback)

	/*!
		Implements code of a callback routine

		Routine should be defined by trace_callback() {<code of routine>} and will get:
			const traceLevel_t _level: severity level of message to be sent/displayed
			const char* _file: calling source file name with extension
			const uint16_t _line: calling source file line
			const char* _function: calling calling source function name
			const char* _message: message to be sent/displayed

	*/
	#define trace_callback(callback) void callback(const traceLevel_t _level, const char* _file, const uint16_t _line, const char* _function, const char* _message)

	/*!
		Set minimum severity level of messages to be sent/printed
		\param	level: Can be FF_TRACE_LEVEL_NONE/ERROR/WARD/INFO/DEBUG/VERBOSE
	*/
	#define trace_setLevel(level) FF_TRACE.setLevel(level)

	/*!
		Return minimum severity level of messages to be sent/printed
		\return	minimum level: Can be FF_TRACE_LEVEL_NONE/ERROR/WARD/INFO/DEBUG/VERBOSE
	*/
	#define trace_getLevel() FF_TRACE.getLevel()

	/*!
		Sends an error message
		\param	format: printf format message
		\param	parameters: message parameters (depends on message format)
	*/
	#define trace_error(...) FF_TRACE.printf(FF_TRACE_LEVEL_ERROR, __FILE__, __LINE__, __func__, __VA_ARGS__)
	#define trace_error_P(fmt, ...) FF_TRACE.printf(FF_TRACE_LEVEL_ERROR, __FILE__, __LINE__, __func__, PSTR(fmt), __VA_ARGS__)

	/*!
		Sends a warning message
		\param	format: printf format message
		\param	parameters: message parameters (depends on message format)
	*/
	#define trace_warn(...) FF_TRACE.printf(FF_TRACE_LEVEL_WARN, __FILE__, __LINE__, __func__, __VA_ARGS__)
	#define trace_warn_P(fmt, ...) FF_TRACE.printf(FF_TRACE_LEVEL_WARN, __FILE__, __LINE__, __func__, PSTR(fmt), __VA_ARGS__)

	/*!
		Sends an information message
		\param	format: printf format message
		\param	parameters: message parameters (depends on message format)
	*/
	#define trace_info(...) FF_TRACE.printf(FF_TRACE_LEVEL_INFO, __FILE__, __LINE__, __func__, __VA_ARGS__)
	#define trace_info_P(fmt, ...) FF_TRACE.printf(FF_TRACE_LEVEL_INFO, __FILE__, __LINE__, __func__, PSTR(fmt), __VA_ARGS__)

	/*!
		Sends a debug message
		\param	format: printf format message
		\param	parameters: message parameters (depends on message format)
	*/
	#define trace_debug(...) FF_TRACE.printf(FF_TRACE_LEVEL_DEBUG, __FILE__, __LINE__, __func__, __VA_ARGS__)
	#define trace_debug_P(fmt, ...) FF_TRACE.printf(FF_TRACE_LEVEL_DEBUG, __FILE__, __LINE__, __func__, PSTR(fmt), __VA_ARGS__)

	/*!
		Sends a verbose message
		\param	format: printf format message
		\param	parameters: message parameters (depends on message format)
	*/

	#define trace_verbose(...) FF_TRACE.printf(FF_TRACE_LEVEL_VERBOSE, __FILE__, __LINE__, __func__, __VA_ARGS__)
	#define trace_verbose_P(...) FF_TRACE.printf(FF_TRACE_LEVEL_VERBOSE, __FILE__, __LINE__, __func__, PSTR(fmt), __VA_ARGS__)

	/*!
		Declare class as external
	*/
	extern trace_declare();
#endif
