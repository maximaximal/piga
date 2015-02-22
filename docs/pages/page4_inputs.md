Inputs {#inputs}
------

The input system of piga is driven by the powerful [event system](@ref event_system) of the piga
library. 

Standard Inputs
--------------

Each console can have different inputs, depending on the used hardware. To make development 
easier, a standard set of inputs is defined as:

Input Name | Description | piga::GameControl
--------- | ---------- | -------------
Joystick Up | Analog arcade joystick; values: true & false | UP
Joystick Down | Analog arcade joystick; values: true & false | DOWN
Joystick Left | Analog arcade joystick; values: true & false | LEFT
Joystick Right | Analog arcade joystick; values: true & false | RIGHT
Joystick Action | Action button ontop of the joystick (pressable by thumb); values: true & false | ACTION
Button 1 | Analog push-button on the right of the joystick; values: true & false | BUTTON1
Button 2 | Analog push-button on the right of the joystick; values: true & false | BUTTON2
Button 3 | Analog push-button on the right of the joystick; values: true & false | BUTTON3
Button 4 | Analog push-button on the right of the joystick; values: true & false | BUTTON4
Button 5 | Analog push-button on the right of the joystick; values: true & false | BUTTON5
Button 6 | Analog push-button on the right of the joystick; values: true & false | BUTTON6

While developing games and applications for the console, you should consider using the integer or
float representation of the inputs. More custom console rigs could use analog controls for more
granular control, which should also work naturally with other games. 

Input Types (piga::GameControl)
----------------------------

The different input types are defined by the piga::GameControl enum. Each type
can be a natural value between 0 and 100000, a floating point value between 0 and 1, 
a boolean on or off value, or combinations of different methods. The inputs can be 
read from an instance of piga::event::GameInput. 

To get more information concerning the conversion and other conventions of the event and input 
system, see [@ref event_system].