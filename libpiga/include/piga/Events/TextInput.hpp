#ifndef LIBPIGA_PIGA_EVENTS_TEXTINPUT_HPP_INCLUDED
#define LIBPIGA_PIGA_EVENTS_TEXTINPUT_HPP_INCLUDED

#include <string>

namespace piga
{
    namespace event
    {
        class TextInput
        {
            public:
                TextInput(const std::string &text = "");
                ~TextInput();

                void setText(const std::string &text);

                const std::string& text() const;

                bool operator==(const std::string &otherText) const;
                TextInput& operator=(const TextInput &otherInput);
            private:
                std::string m_text;
        };
    }
}

#endif
