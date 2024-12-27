#include "centralTrace.h"

/*
	Callback routine
		_level contains severity level
		_file contains calling source file name with extension
		_line contains calling source file line
		_function contains calling calling source function name
		_message contains message to display/send
*/
trace_callback(centralTraceCallback) {
	Serial.print("Central trace: _level=");
	Serial.print(_level);
	Serial.print(", _file=");
	Serial.print(_file);
	Serial.print(", _line=");
	Serial.print(_line);
	Serial.print(", _function=");
	Serial.print(_function);
	Serial.print(", _message=");
	Serial.println(_message);
}
