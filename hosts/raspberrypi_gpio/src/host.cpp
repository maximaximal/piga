#include "../../host.h"

using namespace piga;

#include <piga/PlayerInput.hpp>
#include <wiringPi.h>

#include <iostream>

using std::cout;
using std::endl;

PlayerInputStruct *playerInputs;
int playerCount = 0;

int player1UpPin = 3;
int player1DownPin = 2;
int player1LeftPin = 0;
int player1RightPin = 7;
int player1ActionPin = 12;
int player1Button1Pin = 5;
int player1Button2Pin = 5;
int player1Button3Pin = 5;
int player1Button4Pin = 5;
int player1Button5Pin = 5;
int player1Button6Pin = 5;

int player2UpPin = 5;
int player2DownPin = 5;
int player2LeftPin = 5;
int player2RightPin = 5;
int player2ActionPin = 5;
int player2Button1Pin = 5;
int player2Button2Pin = 5;
int player2Button3Pin = 5;
int player2Button4Pin = 5;
int player2Button5Pin = 5;
int player2Button6Pin = 5;

int getIntFromState(int state)
{
    if(state == 0)
        return 0;
    return 100000;
}

void upHandler1()
{
    playerInputs[0].setUp(getIntFromState(1 - digitalRead(player1UpPin)));
}
void downHandler1()
{
    playerInputs[0].setDown(getIntFromState(1 - digitalRead(player1DownPin)));
}
void leftHandler1()
{
    playerInputs[0].setLeft(getIntFromState(1 - digitalRead(player1LeftPin)));
}
void rightHandler1()
{
    playerInputs[0].setRight(getIntFromState(1 - digitalRead(player1RightPin)));
}
void actionHandler1()
{
    playerInputs[0].setAction(1 - digitalRead(player1ActionPin));
}
void button1Handler1()
{
    playerInputs[0].setButton1(1 - digitalRead(player1Button1Pin));
}
void button2Handler1()
{
    playerInputs[0].setButton2(1 - digitalRead(player1Button2Pin));
}
void button3Handler1()
{
    playerInputs[0].setButton3(1 - digitalRead(player1Button3Pin));
}
void button4Handler1()
{
    playerInputs[0].setButton4(1 - digitalRead(player1Button4Pin));
}
void button5Handler1()
{
    playerInputs[0].setButton5(1 - digitalRead(player1Button5Pin));
}
void button6Handler1()
{
    playerInputs[0].setButton6(1 - digitalRead(player1Button6Pin));
}

void upHandler2()
{
    playerInputs[1].setUp(getIntFromState(1 - digitalRead(player2UpPin)));
}
void downHandler2()
{
    playerInputs[1].setDown(getIntFromState(1 - digitalRead(player2DownPin)));
}
void leftHandler2()
{
    playerInputs[1].setLeft(getIntFromState(1 - digitalRead(player2LeftPin)));
}
void rightHandler2()
{
    playerInputs[1].setRight(getIntFromState(1 - digitalRead(player2RightPin)));
}
void actionHandler2()
{
    playerInputs[1].setAction(1 - digitalRead(player2ActionPin));
}
void button1Handler2()
{
    playerInputs[1].setButton1(1 - digitalRead(player2Button1Pin));
}
void button2Handler2()
{
    playerInputs[1].setButton2(1 - digitalRead(player2Button2Pin));
}
void button3Handler2()
{
    playerInputs[1].setButton3(1 - digitalRead(player2Button3Pin));
}
void button4Handler2()
{
    playerInputs[1].setButton4(1 - digitalRead(player2Button4Pin));
}
void button5Handler2()
{
    playerInputs[1].setButton5(1 - digitalRead(player2Button5Pin));
}
void button6Handler2()
{
    playerInputs[0].setButton6(1 - digitalRead(player2Button6Pin));
}

extern "C"
{
    int init(int playerCount)
    {
        playerInputs = new PlayerInputStruct[playerCount];

        //Initialize the wiring pi GPIO functions.
        wiringPiSetup();

        //Set the interrupts
        wiringPiISR(player1UpPin, INT_EDGE_BOTH, &upHandler1);
        wiringPiISR(player1DownPin, INT_EDGE_BOTH, &downHandler1);
        wiringPiISR(player1LeftPin, INT_EDGE_BOTH, &leftHandler1);
        wiringPiISR(player1RightPin, INT_EDGE_BOTH, &rightHandler1);
        wiringPiISR(player1ActionPin, INT_EDGE_BOTH, &actionHandler1);

        //wiringPiISR(6, INT_EDGE_BOTH, &upHandler2);
        //wiringPiISR(7, INT_EDGE_BOTH, &downHandler2);
        //wiringPiISR(8, INT_EDGE_BOTH, &leftHandler2);
        //wiringPiISR(9, INT_EDGE_BOTH, &rightHandler2);
        //wiringPiISR(10, INT_EDGE_BOTH, &actionHandler2);


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

