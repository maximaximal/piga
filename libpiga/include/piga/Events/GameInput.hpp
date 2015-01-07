#ifndef LIBPIGA_PIGA_EVENTS_GAMEINPUT_HPP_INCLUDED
#define LIBPIGA_PIGA_EVENTS_GAMEINPUT_HPP_INCLUDED

#include <piga/GameControl.hpp>

namespace piga
{
    namespace event
    {
        class GameInput
        {
            public:
                GameInput();
                GameInput(GameControl control, bool state);
                GameInput(GameControl control, int value);
                virtual ~GameInput();

                bool state() const;
                int value() const;
                GameControl control() const;

                void setState(bool state);
                void setValue(int value);
                void setControl(GameControl control);

                bool operator==(const GameControl &rightControl) const;
                GameInput& operator=(const GameInput &otherInput);
                operator bool() const;
            private:
                GameControl m_control;
                int m_value;
        };
    }
}

#endif
