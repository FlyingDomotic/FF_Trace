#include "class.h"
#include <FF_Trace.h>

MyClass::MyClass() {
}

void MyClass::setString(const char* str) {
    trace_info_P(PSTR("In MyClass, str = %s"), str);
}
