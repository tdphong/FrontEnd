//
// Created by phtran on 08/05/2016.
//

#ifndef FRONTEND_TERMINAL_H
#define FRONTEND_TERMINAL_H

#include <list>

#include "container.h"
#include "countedpointer.h"
#include "basecomponent.h"

class BaseEvent;

namespace UI
{
    class Terminal
    {
        static Terminal* singleTerm_;
        Container root_;
        unsigned int xCoordinate_;
        unsigned int yCoordinate_;
        int getKey();
        using ComponentPtr = std::shared_ptr<BaseComponent>;
        std::vector<ComponentPtr> dispose_;

    protected:
        Terminal();

    public:
        typedef short int AttributeMask;
        static const AttributeMask dim;
        static const AttributeMask bold;
        static const AttributeMask blink;
        static const AttributeMask hidden;
        static const AttributeMask normal;
        static const AttributeMask inverse;
        static const AttributeMask underline;
        static const AttributeMask graphics;

        enum Colour
        {
            black,
            red,
            green,
            yellow,
            blue,
            magenta,
            cygan,
            white
        };

        static Terminal& instance();
        void parkCursor();
        void eraseEol();
        void eraseEos();
        void startMainLoop();
        unsigned int width() const;
        unsigned int height() const;
        void write(const char);
        void write(const std::string&);
        Container& root();
        void attributes(AttributeMask);
        void drawAll();
        void gotoxy(const unsigned int, const unsigned int);
        unsigned int xCoordinate() const;
        unsigned int yCoordinate() const;
        void endEnhanced();
        void startBold();
        void startUnderline();
        void startInverse();
        std::list<char> allPrintableCharacters() const;
        void saveCursorPosition();
        void restoreCursorPosition();
        void dispose(ComponentPtr&);

    private:
        AttributeMask attributeMask_;
        Colour foreground_;
        Colour background_;
        unsigned int savedXCoordinate_;
        unsigned int savedYCoordinate_;
    };

    Terminal& terminal();
}

#endif //FRONTEND_TERMINAL_H
