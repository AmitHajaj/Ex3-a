#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "NumberWithUnits.hpp"

namespace ariel
{

    // Function to remove all spaces from a given string
    void removeSpaces(string str)
    {
        // To keep track of non-space character count
        size_t count = 0;
    
        // Traverse the given string. If current character
        // is not space, then place it at index 'count++'
        for (size_t i = 0; str[i]; i++)
            if (str[i] != ' ')
                str[count++] = str[i]; // here count is
                                    // incremented
        str[count] = '\0';
    }
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
        NumberWithUnits temp{this->number*d, this->unit};
        return temp;
    }
    const NumberWithUnits operator*(double d, NumberWithUnits &other)
    {
        NumberWithUnits temp{other.number*d, other.unit};
        return temp;
    }

    //Input-Output stream.
    ostream &operator<<(ostream &os, const NumberWithUnits &other)
    {
        return (os << other.get_number() << "[" << other.get_unit() << "]");
    }
    istream &operator>>(istream &in, NumberWithUnits &other)
    {
        // in >> other.unit;
        return in;
        string num;
        double number;
        string unit;

        string input;
        in >> input;
        removeSpaces(input);
        size_t firstCut = input.find('[');
        size_t secondCut =  input.find('[');

        num = input.substr(0, firstCut);
        unit = input.substr(firstCut+1, secondCut);

        // size_t i = 0;
        // //Iterate until the brackets to get the number.
        // while (input.at(i) != '[')
        // {
        //     if (input.at(i) != ' ')
        //     {
        //         num += (input.at(i));
        //     }
        //     i++;
        // }
        number = stod(num);
        // // Iterate untill the end of the brackets to get the unit.
        // while (input.at(i) != ']')
        // {
        //     if (input.at(i) != ' ')
        //     {
        //         unit += input.at(i);
        //     }
        //     i++;
        // }
        // Assign our data to the object.
        other.set_number(number);
        other.set_unit(unit);
        return in;
    }
}