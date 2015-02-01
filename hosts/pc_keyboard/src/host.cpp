#include "../../host.h"

using namespace piga;

#include <piga/PlayerInput.hpp>
#include <SDL2/SDL.h>

int playerCount = 0;

extern "C"
{
    int init(int playerCount)
    {
        return HOST_RETURNCODE_USEFIXEDFUNCTION;
    }
}
extern "C"
{
    int getButtonState(int player, int button)
    {
        bool state = false;

        const uint8_t* keyboard = SDL_GetKeyboardState(NULL);

        int val = -1;
        switch(button)
        {
            case HOST_UP:
                if(player == 0) {
                    state = keyboard[SDL_SCANCODE_W];
                } else {
                    state = keyboard[SDL_SCANCODE_UP];
                }
                break;
            case HOST_DOWN:
                if(player == 0) {
                    state = keyboard[SDL_SCANCODE_S];
                } else {
                    state = keyboard[SDL_SCANCODE_DOWN];
                }
                break;
            case HOST_LEFT:
                if(player == 0) {
                    state = keyboard[SDL_SCANCODE_A];
                } else {
                    state = keyboard[SDL_SCANCODE_LEFT];
                }
                break;
            case HOST_RIGHT:
                if(player == 0) {
                    state = keyboard[SDL_SCANCODE_D];
                } else {
                    state = keyboard[SDL_SCANCODE_RIGHT];
                }
                break;
            case HOST_ACTION:
                if(player == 0) {
                    state = keyboard[SDL_SCANCODE_SPACE];
                } else {
                    state = keyboard[SDL_SCANCODE_L];
                }
                break;
            case HOST_BUTTON1:
                if(player == 0) {
                    state = keyboard[SDL_SCANCODE_1];
                } else {
                    state = keyboard[SDL_SCANCODE_M];
                }
                break;
            case HOST_BUTTON2:
                if(player == 0) {
                    state = keyboard[SDL_SCANCODE_2];
                } else {
                    state = keyboard[SDL_SCANCODE_N];
                }
                break;
            case HOST_BUTTON3:
                if(player == 0) {
                    state = keyboard[SDL_SCANCODE_3];
                } else {
                    state = keyboard[SDL_SCANCODE_B];
                }
                break;
            case HOST_BUTTON4:
                if(player == 0) {
                    state = keyboard[SDL_SCANCODE_4];
                } else {
                    state = keyboard[SDL_SCANCODE_K];
                }
                break;
            case HOST_BUTTON5:
                if(player == 0) {
                    state = keyboard[SDL_SCANCODE_5];
                } else {
                    state = keyboard[SDL_SCANCODE_J];
                }
                break;
            case HOST_BUTTON6:
                if(player == 0) {
                    state = keyboard[SDL_SCANCODE_6];
                } else {
                    state = keyboard[SDL_SCANCODE_H];
                }
                break;
        }
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
        return "PC-Keyboard Mapping";
    }
    const char* getDescription()
    {
        return "This host maps the normal keyboard to piga controls.";
    }
    const char* getAuthor()
    {
        return "maximaximal";
    }
}

int destroy()
{
    //Nothing to do.
}

