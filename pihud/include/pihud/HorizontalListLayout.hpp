#pragma once

#include <pihud/Layouter.hpp>

namespace PiH
{
    class HorizontalListLayout : public Layouter
    {
        public:
            virtual void setBoxes(LayoutedWidgets &widgets);

            void setSpacing(int spacing);

            virtual void onEvent(const Event &e);

            int getSpacing();
            
            std::shared_ptr<Widget> getCurrentlyFocusedWidget();
        protected:
            virtual void updateBoundingBox();
            virtual void focusGained(int playerID) {}
            virtual void focusLost(int playerID) {}
        private:
            int m_spacing = 5;
            std::size_t m_currentlyFocused = 0;
    };
}
