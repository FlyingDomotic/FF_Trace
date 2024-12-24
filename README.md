# FF_Trace
 Implements central message tracing over multiple supports

## What's for?

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
	- Messages are sent by trace_<level>(), where level can be error, warn, info, debug or verbose.

Having multiple callbacks make sense if you want, for example, write messages to serial and send them to syslog and/or MQTT.

You may also want to have only one callback to centralize messages and decide here what to do with them.

As of now, the following macros are defined:
	trace_declare(): declare trace class, to be inserted in root source code.
	trace_register(callback): declare a callback routine to register
	trace_callback(callback): routine code to be called when a message has to be sent/printed.
	trace_setLevel(level): set minimum severity level of messages to be sent/printed. Can be FF_TRACE_LEVEL_NONE/ERROR/WARD/INFO/DEBUG/VERBOSE.
	trace_getLevel(): return minimum severity level of messages to be sent/printed. Can be any FF_TRACE_LEVEL_???
	trace_warn(format, parameters...): print/send a warning message (with printf syntax), using format and paramaters
	trace_info(format, parameters...): print/send an information message (with printf syntax), using format and paramaters
	trace_debug(format, parameters...): print/send a debug message (with printf syntax), using format and paramaters
	trace_verbose(format, parameters...): print/send a verbose message (with printf syntax), using format and paramaters

Note that callback routine won't be called if message severity level if higher than current severity level set.

Callback routines will be called with the following arguments:
	_level: severity level of message (can be any FF_TRACE_LEVEL_xxxx value)
	_file: calling source file name with extension
	_line: calling source file line
	_function: calling calling source function name
	_message: text message to send

## Prerequisites

Can be used directly with Arduino IDE or PlatformIO.

Your compiler/libraries must support vsnprintf statement.

## Installation

Clone repository somewhere on your disk.
```
cd <where_you_want_to_install_it>
git clone https://github.com/FlyingDomotic/FF_Trace.git FF_Trace
```

Note that <where_you_want_to_install_it> could ingeniously be your compiler libraries folder ;-)

## Update

Go to code folder and pull new version:
```
cd <where_you_installed_FF_Trace>
git pull
```

Note: if you did any changes to files and `git pull` command doesn't work for you anymore, you could stash all local changes using:
```
git stash
```
or
```
git checkout <modified file>
```

## Documentation

Documentation could be built using doxygen, either using makedoc.sh (for Linux) or makedoc.bat (for Windows), or running
```
doxygen doxyfile
```

HTML and RTF versions will then be available in `documentation` folder.
