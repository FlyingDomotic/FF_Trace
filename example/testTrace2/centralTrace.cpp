#include "centralTrace.h"

/*
	Callback routine
		_level contains severity level
		_message contains message to display/send
*/
trace_callback(centralTraceCallback) {
	Serial.print("Central trace: _level=");
	Serial.print(_level);
	Serial.print(", _message=");
	Serial.println(_message);
}
