#!/usr/bin/env wish

wm title . "Test Tk"
grid [label .myLabel  -text "Button with text" -textvariable labelText]
grid [ttk::button .mybutton -text "Stuff" -width 10]

