#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "NumberWithUnits.hpp"

namespace ariel
{
    NumberWithUnits::NumberWithUnits(double number, string unit)
    {
        this->number = number;
        this->unit = unit;
    }

    void NumberWithUnits::read_units(ifstream &input)
    {
        //meanwhile does nothing.
    }

    double NumberWithUnits::get_number() const
    {
        return number;
    }
    void NumberWithUnits::set_number(double num)
    {
        number = num;
    }

    string NumberWithUnits::get_unit() const
    {
        return unit;
    }
    void NumberWithUnits::set_unit(string s)
    {
        unit = s;
    }

    //Add two numbers.
    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits& aother)const
    {
        return NumberWithUnits(0, "m");
    }
    //Add to this.
    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &other)
    {
        return *this;
    }
    //Unary +. (Does nothing)
    NumberWithUnits &NumberWithUnits::operator+()
    {
        return *this;
    }

    // //Sub two numbers.
    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &other) const
    {
        return NumberWithUnits(0, "m");
    }

    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &other)
    {
        return *this;
    }
    //Unary -. (Change sign)
    NumberWithUnits &NumberWithUnits::operator-()
    {
        return *this;
    }

    //LET.
    const bool NumberWithUnits::operator<(const NumberWithUnits &other)
    {
        return true;
    }
    //LEQ.
    const bool NumberWithUnits::operator<=(const NumberWithUnits &other)
    {
        return true;
    }
    //Equals.
    const bool NumberWithUnits::operator==(const NumberWithUnits &other)
    {
        return true;
    }
    //GEQ.
    const bool NumberWithUnits::operator>=(const NumberWithUnits &other)
    {
        return true;
    }
    //GET.
    const bool NumberWithUnits::operator>(const NumberWithUnits &other)
    {
        return true;
    }
    //DIFF.
    const bool NumberWithUnits::operator!=(const NumberWithUnits &other)
    {
        return true;
    }
    //Pre-increment.
    const NumberWithUnits &NumberWithUnits::operator++()
    {
        number++;
        return *this;
    }
    //Post-increment.
    NumberWithUnits &NumberWithUnits::operator++(int)
    {
        NumberWithUnits copy = *this;
        number++;
        return *this;
    }

    //Pre-deccrement.
    const NumberWithUnits &NumberWithUnits::operator--()
    {
        number--;
        return *this;
    }
    //Post-deccrement.
    const NumberWithUnits &NumberWithUnits::operator--(int)
    {
        NumberWithUnits copy = *this;
        number--;
        return *this;
    }

    //Mult with double.
    const NumberWithUnits NumberWithUnits::operator*(double d)
    {
        this->number *= d;
        return *this;
    }
    const NumberWithUnits operator*(double d, NumberWithUnits &other)
    {
        other.set_number(d*other.number);
        return other;
    }

    // //Input-Output stream.
    ostream &operator<<(ostream &os, const NumberWithUnits &other)
    {
        return (os << other.get_number() << "[" << other.get_unit() << "]");
    }
    istream &operator>>(istream &in, NumberWithUnits &other)
    {
        string num;
        double number;
        string unit;

        string input;
        in >> input;

        size_t i = 0;
        //Iterate until the brackets to get the number.
        while (input.at(i) != '[')
        {
            if (input.at(i) != ' ')
            {
                num += (input.at(i));
            }
            i++;
        }
        number = stod(num);
        // Iterate untill the end of the brackets to get the unit.
        while (input.at(i) != ']')
        {
            if (input.at(i) != ' ')
            {
                unit += input.at(i);
            }
            i++;
        }
        // Assign our data to the object.
        other.set_number(number);
        other.set_unit(unit);
        return in;
    }
}