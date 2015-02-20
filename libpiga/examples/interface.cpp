#include <piga/Interface.hpp>

#include <Example.hpp>

int main()
{
    cout << LOG_PRESTRING << "Trying to connect to interface." << endl;
    
    //Create a not selfhosted interface instance. 
    //This only works of a host is already running! The interface needs the shared memory 
    //provided by the Host class. 
    piga::Interface interface(false);

    while(true)
    {
        //Update the interface
        //This requests new events from the host.
        interface.update();

        //Poll events from the interface. 
        piga::GameEvent e;
        while(interface.pollEvent(e))
        {
            cout << LOG_PRESTRING << "Input happened! Type: " << e.type() << ". PlayerID: " << e.playerID() << endl;
        }

        //Update logic of your own game. 
    }

    //The interface cleanup happens automaticly. 
    return 0;
}
