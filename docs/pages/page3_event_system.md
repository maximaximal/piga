Event System {#event_system}
-----------

The event system is divided into several different modules:

  1. The piga::GameEvent class.
  2. The piga::event Namespace and contained classes. (piga::event::GameInput, piga::event::TextInput)
  3. The piga::GameControl enumeration which provides the type of events. 
  4. The piga::Interface and piga::Host classes for event dispatching 
     between apps/games and the host application.
     
### State vs Value

The piga::event::GameInput class has 2 variants of describing inputs: 

  1. A boolean state value. 
  2. An integer value. 

#### State (bool)

The state abstraction serves the purpose of an easier method to hande inputs. Some games
only need boolean inputs and can use this function without heavier comparison operators. 

In addition, the state abstraction is easier for pigaco developers. Keyboard inputs or digital 
buttons only need a true and a false value which is comppletely handled by a boolean. The 
piga::event::GameInput class maps the state directly to the integer value with only a minimal
performance drop, which means that this abstraction does not hurt anybody. 

#### Value (int)

The integer value is the internal representation of the input value in the piga::event::GameInput class. 
This is an integer to provide the possibility of floating point inputs (analog joysticks or similar devices) without 
the introduction of another event type. 

#### Translation

States can be translated into values (and values into states) using this conversion
table:

State | Value
----- |  -----
true  | 100000
false | 0

