#pragma once

#include <vector>

#include <pihud/Widget.hpp>

namespace PiH
{
    class Layouter : public Widget
    {
        public:
            Layouter();
            Layouter(const Layouter &layouter);
            virtual ~Layouter();

            virtual void setBoxes(std::vector<Widget> &widgets);
    };
}
