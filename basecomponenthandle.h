//
// Created by phtran on 07/05/2016.
//

#ifndef FRONTEND_BASECOMPONENTHANDLE_H
#define FRONTEND_BASECOMPONENTHANDLE_H
namespace UI
{
    class BaseComponent;
    class BaseComponentHandle
    {
    public:
        virtual ~BaseComponentHandle() { }
        virtual BaseComponent& obj() = 0;
        virtual const BaseComponent& obj() const = 0;
        virtual BaseComponentHandle* clone() const = 0;
    };
}
#endif //FRONTEND_BASECOMPONENTHANDLE_H
