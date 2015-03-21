#ifndef LIBPIGA_PIGA_EVENTS_GAMEINPUT_HPP_INCLUDED
#define LIBPIGA_PIGA_EVENTS_GAMEINPUT_HPP_INCLUDED

#include <piga/GameControl.hpp>

namespace piga
{
    namespace event
    {
        /**
         * @brief A structure for handling game events like buttons and joysticks. 
         * 
         * This structure tries to simplify the handling of game events. Game events are explained 
         * on the @ref event_system "event system page".
         */
        class GameInput
        {
            public:
                /**
                 * @brief Constructs the GameInput instance. 
                 * 
                 */
                GameInput();
                /**
                 * @brief Construct the GameInput instance with a defined GameControl and a state. (true/false inputs)
                 * 
                 * Value of the internal int value:
                 * 
                 * <table>
                 * <tr>
                 * <th>State</th>
                 * <th>Value</th>
                 * </tr>
                 * <tr>
                 * <td>true</td>
                 * <td>100000</td>
                 * </tr>
                 * <tr>
                 * <td>false</td>
                 * <td>0</td>
                 * </tr>
                 * </table>
                 * 
                 * @param control The GameControl-value of the input. 
                 * @param state The state of the input. True means, that the button has been pressed, false means the opposite. 
                 */
                GameInput(GameControl control, bool state);
                /**
                 * @brief Construct the GameInput instance with a defined GameControl and a value (analog inputs).
                 * 
                 * @param control The GameControl-value of the input.
                 * @param value The value of the input. 0 equals the state false, 100000 equals the state true.
                 */
                GameInput(GameControl control, int value);
                /**
                 * @brief Destructor of the GameInput instance. 
                 */
                ~GameInput();

                /**
                 * @brief Returns the state of the GameControl of the player. 
                 * 
                 * This interprets the internal int value of the GameControl. Everything except 0
                 * will be returned as true.  
                 * 
                 * @return The state of the GameControl. 
                 */
                bool state() const;
                /**
                 * @brief Returns the value of the GameControl of the player. 
                 * 
                 * @return The raw value of the GameControl. 
                 */
                int value() const;
                /**
                 * @brief Returns the value as a float variable between 0 and 1. 
                 * 
                 * This function maps the integer value to a float value. 
                 * 
                 * @return The float value generated from the integer value.
                 */
                float fValue() const;
                /**
                 * @brief Returns the control of the GameInput event. 
                 * 
                 * @return The control of this GameInput event. 
                 */
                GameControl control() const;

                /**
                 * @brief Sets the internal int value of the event to the desired state. 
                 * 
                 * Value of the internal int value:
                 * 
                 * <table>
                 * <tr>
                 * <th>State</th>
                 * <th>Value</th>
                 * </tr>
                 * <tr>
                 * <td>true</td>
                 * <td>100000</td>
                 * </tr>
                 * <tr>
                 * <td>false</td>
                 * <td>0</td>
                 * </tr>
                 * </table>
                 * 
                 * @param state ...
                 * @return void
                 */
                void setState(bool state);
                /**
                 * @brief Sets the internal value directly. 
                 * 
                 * @param value The value of the GameInput event to be set. 
                 */
                void setValue(int value);
                /**
                 * @brief Sets the value from a float variable ranging between 0 and 1. 
                 * 
                 * @param value The float representation of the int value between 0 and 1. 
                 */
                void setFValue(float value);
                /**
                 * @brief Sets the control of the GameEvent. 
                 * 
                 * @param control The GameControl of the GameEvent.
                 * @return void
                 */
                void setControl(GameControl control);

                bool operator==(const GameControl &rightControl) const;
                GameInput& operator=(const GameInput &otherInput);
                /**
                 * @brief Shorter function in operator form for the GameInput::state() method. 
                 * 
                 * @return True if the GameInput::state() function returned true, false otherwise. 
                 */
                operator bool() const;
            private:
                GameControl m_control;
                int m_value;
        };
    }
}

#endif
