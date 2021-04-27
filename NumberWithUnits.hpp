#ifndef NUMBER_WITH_UNITS_H
#define NUMBER_WITH_UNITS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include<map>
using namespace std;

namespace ariel{
    
    class NumberWithUnits{
        private:
            double number;
            std::string unit;
            static map<string, map<string, double>> table;
        
        public:
            NumberWithUnits(double number, string unit);

            static void read_units(ifstream& input);
            //Getters&Setters.
            double get_number() const;
            void set_number(double num);

            string get_unit() const;
            void set_unit(string s);

            //Add two numbers.
            NumberWithUnits operator+(const NumberWithUnits& aother);
            //Add to this.
            NumberWithUnits& operator+=(const NumberWithUnits& other);
            //Unary +. (Does nothing)
            NumberWithUnits& operator+();

            //Sub two numbers.
            NumberWithUnits operator-(const NumberWithUnits& other);
            //Sub to this.
            NumberWithUnits& operator-=(const NumberWithUnits& other);
            //Unary -. (Change sign)
            NumberWithUnits& operator-();

            //LET.
            friend bool operator< (const NumberWithUnits &current, const NumberWithUnits &other);
            //LEQ.
            friend bool operator<= (const NumberWithUnits &current, const NumberWithUnits &other);
            //Equals.
            friend bool operator== (const NumberWithUnits &current, const NumberWithUnits &other);
            //GEQ.
            friend bool operator>= (const NumberWithUnits &current, const NumberWithUnits &other);
            //GET.
            friend bool operator> (const NumberWithUnits &current, const NumberWithUnits &other);
            //DIFF.
            friend bool operator!= (const NumberWithUnits &current, const NumberWithUnits &other);

            //Pre-increment.
            NumberWithUnits& operator++();
            //Post-increment.
            NumberWithUnits& operator++(int);

            //Pre-deccrement.
            NumberWithUnits& operator--();
            //Post-deccrement.
            NumberWithUnits& operator--(int);

            //Mult with double.
            NumberWithUnits operator*(double d);
            friend NumberWithUnits operator*(double d, const NumberWithUnits& other);

            //Input-Output stream.
            friend ostream& operator<< (ostream& os, const NumberWithUnits& other);
            friend istream& operator>> (istream& in, NumberWithUnits& other);

            static NumberWithUnits* helper(string s);
            static pair< pair<string, pair<string, double>>, pair<string, pair<string, double>>> helper1(string s);
            static double ifReachable (const NumberWithUnits &a, const NumberWithUnits &b, map<string, map<string, double>> table);
            static double NumberWithUnits::ifReachable (string a, const string b, map<string, map<string, double>> table, set<string> s);
    };
ostream& operator<< (ostream& os, const NumberWithUnits& other);
istream& operator>> (istream& in, NumberWithUnits& other);}

#endif