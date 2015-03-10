#pragma once

#include <pihud/Layouter.hpp>

namespace PiH
{
    class VerticalListLayout : public Layouter
    {
        public:
            virtual void setBoxes(LayoutedWidgets &widgets);

            void setSpacing(int spacing);
            void setCentered(bool centered);

            virtual void onEvent(const Event &e);

            int getSpacing();
            bool getCentered();

            std::shared_ptr<Widget> getCurrentlyFocusedWidget();
        protected:
            virtual void updateBoundingBox();
            virtual void focusGained(int playerID) {}
            virtual void focusLost(int playerID) {}
        private:
            int m_spacing = 5;
            bool m_centered = false;
            std::size_t m_currentlyFocused = 0;
    };
}
