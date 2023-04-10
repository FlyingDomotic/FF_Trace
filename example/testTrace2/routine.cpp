#include "routine.h"
#include <FF_Trace.h>

void myRoutine(uint8_t _value) {
	trace_info("In myRoutine, value = %d", _value);
}
