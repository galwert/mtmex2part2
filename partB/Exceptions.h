//
// Created by galwe on 13/06/2021.
//

#ifndef SOLDIER_H_EXCEPTIONS_H
#define SOLDIER_H_EXCEPTIONS_H
#include <exception>
#include <string>
namespace mtm
{
    class Exception: public std::exception
    {

    };
    class IllegalArgument: public Exception
    {
    public:
        const char* what() const noexcept override;
    };
    class IllegalCell: public Exception
    {
    public:
        const char* what() const noexcept override;
    };
    class CellEmpty: public Exception
    {
    public:
        const char* what() const noexcept override;
    };
    class MoveTooFar: public Exception
    {
    public:
        const char* what() const noexcept override;
    };
    class CellOccupied: public Exception
    {
    public:
        const char* what() const noexcept override;
    };
    class OutOfRange: public Exception
    {
    public:
        const char* what() const noexcept override;
    };
    class OutOfAmmo: public Exception
    {
    public:
        const char* what() const noexcept override;
    };
    class IllegalTarget: public Exception
    {
    public:
        const char* what() const noexcept override;
    };
}



#endif //SOLDIER_H_EXCEPTIONS_H
