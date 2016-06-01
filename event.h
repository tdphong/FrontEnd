//
// Created by phtran on 13/05/2016.
//

#ifndef FRONTEND_EVENT_H
#define FRONTEND_EVENT_H

#include "baseevent.h"
#include "keydefs.h.h"
#include "sysexception.h"

namespace UI
{
    class Event : public ::BaseEvent
    {
    public:
        virtual bool operator< (const ::BaseEvent& rhs) const
        {
            return name() < rhs.name();
        }
        virtual bool operator== (const ::BaseEvent& rhs) const
        {
            return name() == rhs.name();
        }
    };

    class AbandonEvent : public Event
    {
    public:
        virtual std::string name() const
        {
            return std::string("AbandonEvent");
        }
        virtual AbandonEvent* clone() const
        {
            return new AbandonEvent(*this);
        }
    };

    class ContinueEditEvent : public Event
    {
    public:
        virtual std::string name() const
        {
            return std::string("ContinueEditEvent");
        }
        virtual ContinueEditEvent* clone() const
        {
            return new ContinueEditEvent(*this);
        }
    };

    class GainFocusEvent : public Event
    {
    public:
        virtual std::string name() const
        {
            return std::string("GainFocusEvent");
        }
        virtual GainFocusEvent* clone() const
        {
            return new GainFocusEvent(*this);
        }
    };

    class GainFocusForwardEvent : public Event
    {
    public:
        virtual std::string name() const
        {
            return std::string("GainFocusForwardEvent");
        }

        virtual GainFocusForwardEvent* clone() const
        {
            return new GainFocusForwardEvent(*this);
        }
    };

    class GainFocusBackwardEvent : public Event
    {
    public:
        virtual std::string name() const
        {
            return std::string( "GainFocusBackwardEvent" );

        }
        virtual GainFocusBackwardEvent* clone() const
        {
            return new GainFocusBackwardEvent(*this);
        }
    };

    class HideEvent : public Event
    {
        virtual std::string name() const
        {
            return std::string("HideEvent");
        }
        virtual HideEvent* clone() const
        {
            return new HideEvent(*this);
        }
    };

    class UnhideEvent : public Event
    {
    public:
        virtual std::string name() const
        {
            return std::string("UnhideEvent");
        }
        virtual UnhideEvent* clone() const
        {
            return new UnhideEvent(*this);
        }
    };

    class LooseFocusForwardEvent : public Event
    {
    public:
        virtual std::string name() const
        {
            return std::string("LooseFocusForwardEvent");
        }
        virtual LooseFocusForwardEvent* clone() const
        {
            return new LooseFocusForwardEvent(*this);
        }
    };

    class LooseFocusBackwardEvent : public Event
    {
    public:
        virtual std::string name() const
        {
            return std::string("LooseFocusBackwardEvent");
        }
        virtual LooseFocusBackwardEvent* clone() const
        {
            return new LooseFocusBackwardEvent(*this);
        }
    };

    class SaveRequestEvent : public Event
    {
    public:
        virtual std::string name() const
        {
            return std::string("SaveRequestEvent");
        }
        virtual SaveRequestEvent* clone() const
        {
            return new SaveRequestEvent(*this);
        }
    };

    class StepFocusForwardEvent : public Event
    {
    public:
        virtual std::string name() const
        {
            return std::string("StepFocusForwardEvent");
        }
        virtual StepFocusForwardEvent* clone() const
        {
            return new StepFocusForwardEvent(*this);
        }
    };

    class StepFocusBackwardEvent : public Event
    {
    public:
        virtual std::string name() const
        {
            return std::string("StepFocusBackwardEvent");
        }
        virtual StepFocusBackwardEvent* clone() const
        {
            return new StepFocusBackwardEvent(*this);
        }
    };

    class EndUserInputEvent : public Event
    {
    public:
        virtual std::string name() const
        {
            return std::string("EndUserInputEvent");
        }
        virtual EndUserInputEvent* clone() const
        {
            return new EndUserInputEvent(*this);
        }
    };

    class TerminalGeometryChangedEvent : public Event
    {
    public:
        virtual std::string name() const
        {
            return std::string("TerminalGeometryChangedEvent");
        }
        virtual TerminalGeometryChangedEvent* clone() const
        {
            return new TerminalGeometryChangedEvent(*this);
        }
    };

    class DrawAllEvent : public Event
    {
    public:
        virtual std::string name() const
        {
            return std::string( "DrawAllEvent" );
        }
        virtual DrawAllEvent* clone() const
        {
            return new DrawAllEvent( *this );
        }
    };

    class RemoveComponentEvent : public Event
    {
    public:
        virtual std::string name() const
        {
            return std::string("RemoveComponentEvent");
        }
        virtual RemoveComponentEvent* clone() const
        {
            return new RemoveComponentEvent(*this);
        }
    };

    class RequeryRequestEvent : public Event
    {
    public:
        virtual std::string name() const
        {
            return std::string("RequeryRequestEvent");
        }

        virtual RequeryRequestEvent* clone() const
        {
            return new RequeryRequestEvent(*this);
        }
    };

    class LooseFocusEvent : public Event
    {
    public:
        virtual std::string name() const
        {
            return std::string( "LooseFocusEvent" );
        }
        virtual LooseFocusEvent* clone() const
        {
            return new LooseFocusEvent(*this);
        }
    };

    class KeyStrokeEvent : public Event
    {
    public:
        virtual int keyStroke() const = 0;
        virtual KeyStrokeEvent* clone() const = 0;
    };

    class EscEscEvent : public KeyStrokeEvent
    {
        int keyStroke_;
        int shiftKeyStroke_;

    public:
        EscEscEvent() : keyStroke_(ESCESC), shiftKeyStroke_(ESCESC)
        { }
        virtual int keyStroke() const
        {
            return keyStroke_;
        }
        virtual int shiftKeyStroke() const
        {
            return shiftKeyStroke_;
        }
        virtual std::string name() const
        {
            return std::string( "EscEscEvent" );
        }
        virtual EscEscEvent* clone() const
        {
            return new EscEscEvent(*this);
        }
    };

    class BackSpaceEvent : public KeyStrokeEvent
    {
        int keyStroke_;
        int shiftKeyStroke_;

    public:
        BackSpaceEvent() : keyStroke_(BACK_SPACE), shiftKeyStroke_(BACK_SPACE)
        { }
        virtual int keyStroke() const
        {
            return keyStroke_;
        }
        virtual int shiftKeyStroke() const
        {
            return shiftKeyStroke_;
        }
        virtual std::string name() const
        {
            return std::string("BackSpaceEvent");
        }
        virtual BackSpaceEvent* clone() const
        {
            return new BackSpaceEvent(*this);
        }
    };

    class DeleteEvent : public KeyStrokeEvent
    {
        int keyStroke_;
        int shiftKeyStroke_;

    public:
        DeleteEvent() : keyStroke_(DELETE), shiftKeyStroke_(DELETE)
        { }
        virtual int keyStroke() const
        {
            return keyStroke_;
        }
        virtual int shiftKeyStroke() const
        {
            return shiftKeyStroke_;
        }
        virtual std::string name() const
        {
            return std::string("DeleteEvent");
        }
        virtual DeleteEvent* clone() const
        {
            return new DeleteEvent(*this);
        }
    };

    class EnterEvent : public KeyStrokeEvent
    {
        int keyStroke_;
        int shiftKeyStroke_;

    public:
        EnterEvent() : keyStroke_(RETURN), shiftKeyStroke_(RETURN)
        { }
        virtual int keyStroke() const
        {
            return keyStroke_;
        }
        virtual int shiftKeyStroke() const
        {
            return shiftKeyStroke_;
        }
        virtual std::string name() const
        {
            return std::string("EnterEvent");
        }
        virtual EnterEvent* clone() const
        {
            return new EnterEvent(*this);
        }
    };

    class TabEvent : public KeyStrokeEvent
    {
        int keyStroke_;
        int shiftKeyStroke_;

    public:
        TabEvent() : keyStroke_(TAB_KEY), shiftKeyStroke_(TAB_KEY)
        { }
        virtual int keyStroke() const
        {
            return keyStroke_;
        }
        virtual int shiftKeyStroke() const
        {
            return shiftKeyStroke_;
        }
        virtual std::string name() const
        {
            return std::string("TabEvent");
        }
        virtual TabEvent* clone() const
        {
            return new TabEvent(*this);
        }
    };

    class UpArrowEvent : public KeyStrokeEvent
    {
        int keyStroke_;

    public:

        UpArrowEvent() : keyStroke_(UP_ARROW)
        { }
        virtual int keyStroke() const
        {
            return keyStroke_;
        }
        virtual std::string name() const
        {
            return std::string("UpArrowEvent");
        }
        virtual UpArrowEvent* clone() const
        {
            return new UpArrowEvent(*this);
        }
    };

    class DownArrowEvent : public KeyStrokeEvent
    {
        int keyStroke_;
        int shiftKeyStroke_;

    public:
        DownArrowEvent() : keyStroke_(DOWN_ARROW), shiftKeyStroke_(DOWN_ARROW)
        { }
        virtual int keyStroke() const
        {
            return keyStroke_;
        }
        virtual int shiftKeyStroke() const
        {
            return shiftKeyStroke_;
        }
        virtual std::string name() const
        {
            return std::string("DownArrowEvent");
        }
        virtual DownArrowEvent* clone() const
        {
            return new DownArrowEvent( *this );
        }
    };

    class LeftArrowEvent : public KeyStrokeEvent
    {
        int keyStroke_;
        int shiftKeyStroke_;

    public:

        LeftArrowEvent() : keyStroke_(LEFT_ARROW), shiftKeyStroke_(LEFT_ARROW)
        { }
        virtual int keyStroke() const
        {
            return keyStroke_;
        }
        virtual int shiftKeyStroke() const
        {
            return shiftKeyStroke_;
        }
        virtual std::string name() const
        {
            return std::string("LeftArrowEvent");
        }
        virtual LeftArrowEvent* clone() const
        {
            return new LeftArrowEvent( *this );
        }
    };

    class RightArrowEvent : public KeyStrokeEvent
    {
        int keyStroke_;
        int shiftKeyStroke_;

    public:

        RightArrowEvent() : keyStroke_(RIGHT_ARROW), shiftKeyStroke_(RIGHT_ARROW)
        { }
        virtual int keyStroke() const
        {
            return keyStroke_;
        }
        virtual int shiftKeyStroke() const
        {
            return shiftKeyStroke_;
        }
        virtual std::string name() const
        {
            return std::string("RightArrowEvent");
        }
        virtual RightArrowEvent* clone() const
        {
            return new RightArrowEvent( *this );
        }
    };

    class PrintableKeyEvent : public KeyStrokeEvent
    {
        char keyStroke_;

    public:
        PrintableKeyEvent( const char k) : keyStroke_(k)
        {
            if (!isprint(keyStroke_))
            {
                throw InternalException();
            }
        }
        virtual int keyStroke() const
        {
            return keyStroke_;
        }
        virtual std::string name() const
        {
            std::ostringstream s;
            s << "keyStroke_" << static_cast<int>(keyStroke());
            return s.str();
        }
        virtual PrintableKeyEvent* clone() const
        {
            return new PrintableKeyEvent(*this);
        }
    };

    class AKeyEvent : public PrintableKeyEvent
    {
        int keyStroke_;

    public:
        AKeyEvent() : PrintableKeyEvent('A')
        { }
        virtual AKeyEvent* clone() const
        {
            return new AKeyEvent(*this);
        }
    };

    class EKeyEvent : public PrintableKeyEvent
    {
        int keyStroke_;

    public:
        EKeyEvent() : PrintableKeyEvent('E')
        { }
        virtual EKeyEvent* clone() const
        {
            return new EKeyEvent(*this);
        }
    };

    class SKeyEvent : public PrintableKeyEvent
    {
        int keyStroke_;

    public:
        SKeyEvent() : PrintableKeyEvent('S')
        { }
        virtual SKeyEvent* clone() const
        {
            return new SKeyEvent(*this);
        }
    };

    class QuestionEvent: public PrintableKeyEvent
    {
        int keyStroke_;

    public:
        QuestionEvent() : PrintableKeyEvent('?')
        { }
        virtual QuestionEvent* clone() const
        {
            return new QuestionEvent(*this);
        }
    };
}

#endif //FRONTEND_EVENT_H
