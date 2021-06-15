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
        const char* what() noexcept
        {
            return "A game related error has occurred: IllegalArgument";
        }
    };
    class IllegalCell
    {
    };
    class CellEmpty
    {
    };
    class MoveTooFar
    {

    };
    class CellOccupied
    {
    };
    class OutOfRange
    {
    };
    class OutOfAmmo
    {

    };
    class IllegalTarget
    {
    };
}



#endif //SOLDIER_H_EXCEPTIONS_H
