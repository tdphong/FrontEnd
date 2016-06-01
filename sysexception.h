//
// Created by phtran on 10/05/2016.
//

#ifndef FRONTEND_SYSEXCEPTION_H
#define FRONTEND_SYSEXCEPTION_H

#include <exception>
#include <sstream>

class ApplicationException : public std::exception
{
public:
    ApplicationException(const ApplicationException&)
    { }
    virtual const char* what() const throw()
    {
        outputmsg_ = msg_.str();
        return outputmsg_.c_str();
    }
    virtual ~ApplicationException() throw()
    { }

protected:
    ApplicationException()
    { }
    ApplicationException& operator=(const ApplicationException& rhs)
    {
        if (this != &rhs) {
            msg_.str("");
            msg_ << rhs.msg_.str();
        }
        return *this;
    }
    std::ostringstream msg_;
    mutable std::string outputmsg_;
};

class ArgumentsException : public ApplicationException
{
public:
    ArgumentsException() : ApplicationException()
    { }
};

class TerminateException : public ApplicationException
{
public:
    TerminateException() : ApplicationException()
    { }
};

class ValidationException : public ApplicationException
{
public:
    ValidationException() : ApplicationException()
    { }
};

class ScreenValidationException : public ValidationException
{
    const unsigned fieldnumber_;
    const unsigned pagenumber_;
public:
    ScreenValidationException(unsigned pagenumber, unsigned fieldnumber)
            : ValidationException()
            , pagenumber_(pagenumber)
            , fieldnumber_(fieldnumber)
    { }
    virtual ~ScreenValidationException() throw()
    { }
    unsigned fieldNumber() const
    {
        return fieldnumber_;
    }
    unsigned pagenumber() const
    {
        return pagenumber_;
    }
};

class ScreenErrorValidationException : public ScreenValidationException
{
public:
    ScreenErrorValidationException(unsigned pagenumber, unsigned fieldnumber)
            : ScreenValidationException(pagenumber, fieldnumber)
    { }
};

class ScreenWarningValidationException : public ScreenValidationException
{
public:
    ScreenWarningValidationException(unsigned pagenumber, unsigned fieldnumber)
            : ScreenValidationException(pagenumber, fieldnumber)
    { }
};

class FileException : public ApplicationException
{
public:
    FileException() : ApplicationException()
    { }
};

class FileOpenException : public FileException
{
public:
    FileOpenException() : FileException()
    { }
};

class FileInputException : public FileException
{
public:
    FileInputException() : FileException()
    { }
};

class MemoryException : public ApplicationException
{
public:
    MemoryException() : ApplicationException()
    { }
};

class InternalException : public ApplicationException
{
public:
    InternalException() : ApplicationException()
    { }
};

class AbortException : public ApplicationException {
public:
    AbortException() : ApplicationException()
    { }
};
#endif //FRONTEND_SYSEXCEPTION_H
