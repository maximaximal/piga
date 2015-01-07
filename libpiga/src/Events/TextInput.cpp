#include <piga/Events/TextInput.hpp>

namespace piga
{
    namespace event
    {
        TextInput::TextInput(const std::string &text)
            : m_text(text)
        {

        }
        TextInput::~TextInput()
        {

        }
        void TextInput::setText(const std::string &text)
        {
            m_text = text;
        }
        const std::string &TextInput::text() const
        {
            return m_text;
        }
        bool TextInput::operator==(const std::string &otherText) const
        {
            return m_text == otherText;
        }
        TextInput &TextInput::operator=(const TextInput &otherInput)
        {
            m_text = otherInput.text();
            return *this;
        }
    }
}
