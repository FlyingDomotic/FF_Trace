/*
	This example show implementation of FF_Trace class with :
		a main code (testTrace2.ino), a class (class.cpp) and a module (routine.cpp) that send messages
		a main code (testTrace2.ino) and a module (centralTrace.cpp) that receive messages and display them on Serial

	Note that in real life centralTrace module should probably send message to MQTT or syslog instead of Serial
*/

#include "FF_Trace.h"                                 // Include FF_Trace definition

#include "routine.h"                                  // Include routine definitions
#include "class.h"                                    // Include class definitions
#include "centralTrace.h"                             // Include central trace definitions

trace_declare();                                      // Declare trace class for this project
trace_callback(mainCallback);                         // Declare main callback
MyClass myClass;                                      // Define myClass

void setup() {
  Serial.begin(74880);                                // Set serial speed & init
  trace_register(&mainCallback);                      // Register main callback
  trace_register(&centralTraceCallback);              // Register central trace callback
  trace_info("Starting trace %d", millis());          // Send a "starting" message
  myRoutine(12345);                                   // Call myRoutine
  myClass.setString("Hello!");                        // Call myClass
}

void loop() {
}

/*
	Callback routine
		_level contains severity level
		_message contains message to display/send
*/
trace_callback(mainCallback) {
  Serial.print("Main callback: ");
  Serial.println(_message);
}
