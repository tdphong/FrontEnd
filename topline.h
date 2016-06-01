//
// Created by phtran on 13/05/2016.
//

#ifndef FRONTEND_TOPLINE_H
#define FRONTEND_TOPLINE_H

#include "component.h"

namespace UI
{

    class TopLine : public Component
    {
        class DrawAllEventHandler;

    public:
        TopLine();
        void draw() const;
        virtual TopLine* clone() const;
        virtual std::string name() const;
    };
}

#endif //FRONTEND_TOPLINE_H
