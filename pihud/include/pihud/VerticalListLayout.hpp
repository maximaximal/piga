#pragma once

#include <pihud/Layouter.hpp>

namespace PiH
{
    class VerticalListLayout : public Layouter
    {
        public:
            virtual void setBoxes(LayoutedWidgets &widgets);

            void setSpacing(int spacing);

            virtual void onEvent(const Event &e);

            int getSpacing();
        protected:
            virtual void updateBoundingBox();
        private:
            int m_spacing = 5;
            std::size_t m_currentlyFocused = 0;
    };
}
