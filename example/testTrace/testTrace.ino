#include "FF_Trace.h"
#include <stdarg.h>

FF_Trace trace;

void setup() {
  Serial.begin(74880);
  trace.registerCallback(&traceCallback);
  trace.printf(FF_TRACE_LEVEL_INFO, "Starting trace %d", millis());
  trace.printf(FF_TRACE_LEVEL_INFO, PSTR("Version %s"), "V1.0.0");
}
void loop() {
}

void traceCallback(const traceLevel_t _level, const char* _message) {
  Serial.println(_message);
}
