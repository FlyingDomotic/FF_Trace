/*
	This example shows how to implement FF_Trace class the simplest way
*/

#include "FF_Trace.h"

trace_declare();											// Declare trace class

void setup() {
	Serial.begin(74880);
	trace_register(&traceCallback);							  // Register callback
	trace_info_P("Starting trace %d", millis());	// Write a trace message stored in flash as PSTR
	trace_info(PSTR("Version %s"), "V1.0.0");			// ... and a second one also stored in flash as PSTR
  trace_info("Started!");                       // ... and a last one stored in memory
}
void loop() {
}

/*
	Callback routine
		_level contains severity level
		_message contains message to display/send
*/
trace_callback(traceCallback) {
	Serial.println(_message);								// Print message on Serial
}
