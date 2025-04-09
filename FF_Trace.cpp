/*!
	\file
	\brief Implements a centralized trace class
	\author Flying Domotic

	Have a look at FF_Trace.h for details.

	Please prefer using macro in FF_Trace.h instead of calling class directly.
*/

#include "FF_Trace.h"

/*!
	Class initialization
*/
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
	Send a message to all registered routines using printf format

	A first try is done with a 200 bytes buffer.
	If too short, a sufficiently long one is dynamically allocated.
	IF dynamic allocation fails, only the first 200 bytes of message are displayed.
	Else, full message is shown.

	/param	_level: level associated to this message
	/param	_file: calling source file name with extension
	/param	_line: calling source file line
	/param	_function: calling calling source function name
	/param	_format: (printf) format string to use
	/param	...: associated parameters (depends on format string contents)

*/
#ifndef FF_TRACE_NO_SOURCE_INFO
void FF_Trace::printf(const traceLevel_t _level, const char* _file, const uint16_t _line, const char* _function, const char* _format, ...) {
#else
void FF_Trace::printf(const traceLevel_t _level, const char* _format, ...) {
#endif
	// Check level against internal one
	if (_level <= currentLevel) {
		// Make the message
		char msg[200];										// Allocate 200 bytes for message (larger buffer allocated dynamically if needed)
		va_list arguments;
		va_start(arguments, _format);
		int size = vsnprintf(msg, sizeof(msg), _format, arguments);
		va_end(arguments);
		// Was buffer large enough?
		if (size < (int) sizeof(msg)) {
			// Call all registered callbacks
			for (uint8_t i = 0; i < FF_TRACE_MAX_TRACE; i++) {
				if (callbacks[i] != NULL) {
					#ifndef FF_TRACE_NO_SOURCE_INFO
						(callbacks[i])(_level, _file, _line, _function, msg);
					#else
						(callbacks[i])(_level, msg);
					#endif
				}
			}
		} else {
			// Use dynamic buffer allocation
			char* buffer = (char *) malloc(size+1);
			if (!buffer) {
				// Not enougth memory, call all registered callbacks with fixed string
				for (uint8_t i = 0; i < FF_TRACE_MAX_TRACE; i++) {
					if (callbacks[i] != NULL) {
						#ifndef FF_TRACE_NO_SOURCE_INFO
							(callbacks[i])(_level, _file, _line, _function, msg);
						#else
							(callbacks[i])(_level, msg);
						#endif
					}
				}
			} else {
				va_list arguments;
				va_start(arguments, _format);
				vsnprintf(buffer, size, _format, arguments);
				va_end(arguments);
				// Call all registered callbacks with dynamic string
				for (uint8_t i = 0; i < FF_TRACE_MAX_TRACE; i++) {
					if (callbacks[i] != NULL) {
						#ifndef FF_TRACE_NO_SOURCE_INFO
							(callbacks[i])(_level, _file, _line, _function, buffer);
						#else
							(callbacks[i])(_level, buffer);
						#endif
					}
				}
				free(buffer);
			}
		}
	}
}

/*!
 
	Set current message level

	/param	_level: minimum level required to display message

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

char * FF_Trace::textLevel(level) {
	if (level >= FF_TRACE_LEVEL_NONE && level <= FF_TRACE_LEVEL_VERBOSE) {
		return levelName[currentLevel];
	}
	return (char *) "????"
}

