Selfhosted Interface {#selfhosted_interface}
--------------------

Selfhosted interfaces do not need any shared memory, they operate
only in the context of the calling program. 

This mode has been made to provide the possibility of 
coding games with the piga library, while still beeing 
able to run them on normal computers thanks to the piga::GameInput system.

Hosted Interface
----------------

Hosted interfaces need an external piga::Host. This external host 
provides the shared memory objects necessary to run the interface. 