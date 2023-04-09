# FF_Trace
 
Implements message tracing over multiple supports

This class allows to have a centralized place to display trace message on multiple supports.
	Message is sent by anycode having something to report using trace.printf() call.
	Class with then generate message and send it to all routines declared by trace.registerCallback().
	Routines could then look at message level and message contents to decide if it should display/send it (or not).