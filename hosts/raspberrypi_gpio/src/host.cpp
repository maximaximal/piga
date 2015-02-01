#include "../../host.h"

using namespace piga;

#include <piga/PlayerInput.hpp>
#include <wiringPi.h>

PlayerInputStruct *playerInputs;
int playerCount = 0;

void upHandler1()
{
    playerInputs[0].invertUp();
}
void downHandler1()
{
    playerInputs[0].invertDown();
}
void leftHandler1()
{
    playerInputs[0].invertLeft();
}
void rightHandler1()
{
    playerInputs[0].invertRight();
}
void actionHandler1()
{
    playerInputs[0].invertAction();
}
void button1Handler1()
{
    playerInputs[0].invertButton1();
}
void button2Handler1()
{
    playerInputs[0].invertButton2();
}
void button3Handler1()
{
    playerInputs[0].invertButton3();
}
void button4Handler1()
{
    playerInputs[0].invertButton4();
}
void button5Handler1()
{
    playerInputs[0].invertButton5();
}
void button6Handler1()
{
    playerInputs[0].invertButton6();
}

void upHandler2()
{
    playerInputs[1].invertUp();
}
void downHandler2()
{
    playerInputs[1].invertDown();
}
void leftHandler2()
{
    playerInputs[1].invertLeft();
}
void rightHandler2()
{
    playerInputs[1].invertRight();
}
void actionHandler2()
{
    playerInputs[1].invertAction();
}
void button1Handler2()
{
    playerInputs[1].invertButton1();
}
void button2Handler2()
{
    playerInputs[1].invertButton2();
}
void button3Handler2()
{
    playerInputs[1].invertButton3();
}
void button4Handler2()
{
    playerInputs[1].invertButton4();
}
void button5Handler2()
{
    playerInputs[1].invertButton5();
}
void button6Handler2()
{
    playerInputs[1].invertButton6();
}

extern "C"
{
    int init(int playerCount)
    {
        playerInputs = new PlayerInputStruct[playerCount];

        //Initialize the wiring pi GPIO functions.
        wiringPiSetup();

        //Set the interrupts
        wiringPiISR(1, INT_EDGE_BOTH, &upHandler1);
        wiringPiISR(2, INT_EDGE_BOTH, &downHandler1);
        wiringPiISR(3, INT_EDGE_BOTH, &leftHandler1);
        wiringPiISR(4, INT_EDGE_BOTH, &rightHandler1);
        wiringPiISR(5, INT_EDGE_BOTH, &actionHandler1);

        wiringPiISR(6, INT_EDGE_BOTH, &upHandler2);
        wiringPiISR(7, INT_EDGE_BOTH, &downHandler2);
        wiringPiISR(8, INT_EDGE_BOTH, &leftHandler2);
        wiringPiISR(9, INT_EDGE_BOTH, &rightHandler2);
        wiringPiISR(10, INT_EDGE_BOTH, &actionHandler2);


        return HOST_RETURNCODE_USEFIXEDFUNCTION;
    }
}
extern "C"
{
    int getButtonState(int playerID, int button)
    {
        bool state = false;
        int val = -1;
        switch(button)
        {
            case HOST_UP:
                val = playerInputs[playerID].up();
                break;
            case HOST_DOWN:
                val = playerInputs[playerID].down();
                break;
            case HOST_LEFT:
                val = playerInputs[playerID].left();
                break;
            case HOST_RIGHT:
                val = playerInputs[playerID].right();
                break;
            case HOST_ACTION:
                state = playerInputs[playerID].action();
                break;
            case HOST_BUTTON1:
                state = playerInputs[playerID].button1();
                break;
            case HOST_BUTTON2:
                state = playerInputs[playerID].button2();
                break;
            case HOST_BUTTON3:
                state = playerInputs[playerID].button3();
                break;
            case HOST_BUTTON4:
                state = playerInputs[playerID].button4();
                break;
            case HOST_BUTTON5:
                state = playerInputs[playerID].button5();
                break;
            case HOST_BUTTON6:
                state = playerInputs[playerID].button6();
                break;
        }
        if(val != -1)
            return val;
        if(state)
            return 100000;
        else
            return 0;
    }
}
extern "C"
{
    void setGameInput(piga::GameInput *gameInput)
    {
        //Nothing to do, using the fixed function pipeline.
    }
}
extern "C"
{
    const char* getName()
    {
        return "WiringPI Raspberry Pi GPIO Input Mapping";
    }
    const char* getDescription()
    {
        return "This host maps the GPIO connections of a Raspberry Pi to piga controls.";
    }
    const char* getAuthor()
    {
        return "maximaximal";
    }
}

int destroy()
{
    delete[] playerInputs;
}

