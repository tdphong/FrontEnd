//
// Created by phtran on 14/05/2016.
//

#ifndef FRONTEND_SCREEN_H
#define FRONTEND_SCREEN_H

#include <vector>
#include <list>

#include "screenform.h"
#include "basescreenvalidator.h"
#include "topline.h"

#include <iostream>
namespace UI
{
class Screen : public Component
{
public:
    class WarningException;
    class UserConfirmationException;
    class ValidationException;
    class EndUserInputEventHandler;
    using value_type = std::shared_ptr<ScreenField>;
    using Fields = std::vector<value_type>;
    using iterator = Fields::iterator;
    using const_iterator = Fields::const_iterator;
    Screen();
    Screen(const std::string&);
    ScreenField& operator[] (const unsigned int);
    const ScreenField& operator[] (const unsigned int) const;
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    iterator cursor();
    const_iterator cursor() const;
    iterator focus();
    const_iterator focus() const;
    iterator focus( iterator );
    iterator firstEditable();
    iterator stepForward();
    iterator stepBackward();
    virtual void draw() const;
    void drawForm() const;
    void drawFields() const;
    void drawMessages() const;
    void clearFields();
    void title( const std::string& );
    const std::string& title() const;
    const ScreenForm& form() const { return frameWork_; }
    virtual Screen* clone() const {
        return new Screen( *this );
    }
    void validate();
    void validateNoWarnings();
    void addValidator( const BaseScreenValidator& );
    void addWarningValidator( const BaseScreenValidator& );
    virtual std::string name() const;
    virtual std::shared_ptr<BaseEventHandler> endUserInputEventHandler();

private:

    void notifyNoRecurse(iterator, const BaseEvent&);
    void validateFields();
    iterator cursor(iterator);
    void load(const std::string&);
    void drawTitle() const;
    std::shared_ptr<TopLine> topLine_;
    ScreenForm frameWork_;
    std::string title_;
    Fields fields_;
    iterator focus_;
    iterator cursor_;
    using ValidatorPtr = std::shared_ptr<BaseScreenValidator>;
    using Validators = std::list<ValidatorPtr>;
    Validators validators_;
    Validators warningValidators_;
};
}

#endif //FRONTEND_SCREEN_H
