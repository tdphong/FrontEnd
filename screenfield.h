//
// Created by phtran on 14/05/2016.
//

#ifndef FRONTEND_SCREENFIELD_H
#define FRONTEND_SCREENFIELD_H

#include "component.h"
#include "basescreenfieldformatter.h"

namespace UI
{
    class BaseScreenFieldValidator;

    class ScreenField : public Component
    {
    public:
        ScreenField();
        virtual void gainFocus();
        virtual void loseFocus();
        virtual char receiveKey(const char);
        virtual const std::string& get() const;
        virtual const std::string& set(const std::string&);
        virtual unsigned int setUInt(const unsigned int);
        virtual double setDouble(const double);
        virtual int setInt(const int);
        virtual unsigned int length() const;
        virtual unsigned int length(const unsigned int);
        virtual const std::string& defaultValue() const;
        virtual const std::string& defaultValue(const std::string&);
        virtual std::string setToDefaultValue();
        bool isBlank() const;
        static void clearField(ScreenField*);
        static void drawField(ScreenField*);
        void clear();
        void draw() const;
        void toupper();
        const BaseScreenFieldFormatter& formatter() const;
        const BaseScreenFieldFormatter& formatter(const BaseScreenFieldFormatter&);
        virtual unsigned int xCoordinate() const
        {
            return xCoordinate_;
        }
        virtual unsigned int yCoordinate() const
        {
            return yCoordinate_;
        }
        unsigned int decimalPlaces() const
        {
            return decimalPlaces_;
        }
        const std::string& hint() const
        {
            return hint_;
        }
        const std::string& label() const
        {
            return label_;
        }
        bool mandatory() const
        {
            return isMandatory_;
        }
        virtual void xCoordinate(const unsigned int newXloc)
        {
            xCoordinate_ = newXloc;
        }
        virtual void yCoordinate(const unsigned int newYloc)
        {
            yCoordinate_ = newYloc;
        }
        void decimalPlaces(const unsigned int decimalPlaces)
        {
            decimalPlaces_  = decimalPlaces;
        }
        void mandatory(bool flag)
        {
            isMandatory_ = flag;
        }
        void hint(std::string val)
        {
            hint_.swap(val);
        }

        void label(std::string label)
        {
            label_.swap(label);
        }
        void addValidator(const BaseScreenFieldValidator&);
        void removeValidators();
        using ValidatorPtr = std::shared_ptr<BaseScreenFieldValidator>;
        using Validators = std::list<ValidatorPtr>;
        const Validators& validators() const;
        void validate() const;
        bool readonly() const;
        bool readonly( const bool );
        void moveCursorLeft() const;
        void moveCursorRight() const;
        virtual bool contentHasChanged() const;
        void deleteCharacter();
        void backspaceCharacter();
        unsigned int cursorIndex() const;
        bool cursorAtFirst() const;
        bool cursorAtLast() const;
        void escapeEscapePressed() const;

    protected:
        void drawHintMessage() const;
        virtual std::string contentBeforeEdit() const;
        bool isBlank( const std::string& ) const;

    private:
        ScreenField& operator=(const ScreenField&) { return *this; }
        ScreenField(const ScreenField&) { }
        virtual ScreenField* clone() const { return 0; }
        std::string content_;
        std::string contentBeforeEdit_;
        unsigned int xCoordinate_;
        unsigned int yCoordinate_;
        unsigned int length_;
        bool isReadonly_;
        unsigned int decimalPlaces_;
        std::string label_;
        bool isMandatory_;
        std::string hint_;
        Validators validators_;
        using FormatterPtr = std::shared_ptr<BaseScreenFieldFormatter>;
        FormatterPtr formatter_;
        std::string defaultValue_;
        bool hasOwnedInputFocus_;
    };
}

#endif //FRONTEND_SCREENFIELD_H
