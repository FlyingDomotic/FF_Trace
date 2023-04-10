#include "class.h"
#include <FF_Trace.h>

MyClass::MyClass() {
}

void MyClass::setString(const char* str) {
    trace_info(PSTR("In MyClass, str = %s"), str);
}
