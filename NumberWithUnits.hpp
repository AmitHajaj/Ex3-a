#ifndef NUMBER_WITH_UNITS_H
#define NUMBER_WITH_UNITS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include<map>
using namespace std;

namespace ariel{
    
    class NumberWithUnits{
        private:
            double number;
            std::string unit;
            map<string, string> table;
        
        public:
            NumberWithUnits(double number, string unit);

            static void read_units(ifstream& input);
            //Getters&Setters.
            double get_number() const;
            void set_number(double num);

            string get_unit() const;
            void set_unit(string s);

            //Add two numbers.
            NumberWithUnits operator+(const NumberWithUnits& aother)const;
            //Add to this.
            NumberWithUnits& operator+=(const NumberWithUnits& other);
            //Unary +. (Does nothing)
            NumberWithUnits& operator+();

            //Sub two numbers.
            NumberWithUnits operator-(const NumberWithUnits& other) const;
            //Sub to this.
            NumberWithUnits& operator-=(const NumberWithUnits& other);
            //Unary -. (Change sign)
            NumberWithUnits& operator-();

            //LET.
            const bool operator< (const NumberWithUnits &other);
            //LEQ.
            const bool operator<= (const NumberWithUnits &other);
            //Equals.
            const bool operator== (const NumberWithUnits &other);
            //GEQ.
            const bool operator>= (const NumberWithUnits &other);
            //GET.
            const bool operator> (const NumberWithUnits &other);
            //DIFF.
            const bool operator!= (const NumberWithUnits &other);

            //Pre-increment.
            const NumberWithUnits& operator++();
            //Post-increment.
            NumberWithUnits& operator++(int);

            //Pre-deccrement.
            const NumberWithUnits& operator--();
            //Post-deccrement.
            const NumberWithUnits& operator--(int);

            //Mult with double.
            const NumberWithUnits operator*(double d);
            friend const NumberWithUnits operator*(double d, NumberWithUnits& other);

            //Input-Output stream.
            friend ostream& operator<< (ostream& os, const NumberWithUnits& other);
            friend istream& operator>> (istream& in, NumberWithUnits& other);
    };
ostream& operator<< (ostream& os, const NumberWithUnits& other);
istream& operator>> (istream& in, NumberWithUnits& other);}

#endif