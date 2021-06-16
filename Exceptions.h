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
        const char* what() noexcept
        {
            return "A game related error has occurred: IllegalArgument";
        }
    };
    class IllegalCell: public Exception
    {
    public:
        const char* what() noexcept
        {
            return "A game related error has occurred: IllegalCell";
        }
    };
    class CellEmpty: public Exception
    {
    public:
        const char* what() noexcept
        {
            return "A game related error has occurred: CellEmpty";
        }
    };
    class MoveTooFar: public Exception
    {
    public:
        const char* what() noexcept
        {
            return "A game related error has occurred: MoveTooFar";
        }
    };
    class CellOccupied: public Exception
    {
    public:
        const char* what() noexcept
        {
            return "A game related error has occurred: CellOccupied";
        }
    };
    class OutOfRange: public Exception
    {
    public:
        const char* what() noexcept
        {
            return "A game related error has occurred: OutOfRange";
        }
    };
    class OutOfAmmo: public Exception
    {
    public:
        const char* what() noexcept
        {
            return "A game related error has occurred: OutOfAmmo";
        }
    };
    class IllegalTarget: public Exception
    {
    public:
        const char* what() noexcept
        {
            return "A game related error has occurred: IllegalTarget";
        }
    };
}



#endif //SOLDIER_H_EXCEPTIONS_H
