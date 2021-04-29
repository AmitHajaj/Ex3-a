#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <map>
#include "NumberWithUnits.hpp"

#define EPSILON 0.0001

using namespace std;


namespace ariel
{
    map<string, int> NumberWithUnits::unitsName;
    int NumberWithUnits::id;
    Graph NumberWithUnits::tabla;

    NumberWithUnits::NumberWithUnits(double number, string unit)
    {
        //If there is not units on the table.
        if(unitsName.size() == 0){
            throw exception();
        }

        //If the given unit, exist on the table.
        if(unitsName.find(unit) != unitsName.end()){
            this->unit = unit;
            this->number = number;
        }
        else{
            throw exception();
        }
    }

//    void NumberWithUnits::printTable(){
//        for(int i=0; i<id; i++ ){
//            for(int j=0; j<id; j++){
//                cout << tabla.vertArr[i][j]<<" |";
//            }
//            cout << "\n"<<endl;
//        }
//        cout<< "Number of units: " << id;
//    }
    void NumberWithUnits::read_units (ifstream& input)
    {
        string word, leftUnit, rightUnit, equal;
        double leftVal, rightVal;

        while (input >> leftVal >> leftUnit >> equal >> rightVal>> rightUnit){
            // if one of the units is new, add it to the list, with a unique id.
            if(unitsName.find(leftUnit) == unitsName.end()){
                unitsName.emplace(leftUnit, id++);
                tabla.addNode();

            }
            if(unitsName.find(rightUnit) == unitsName.end()){
                unitsName.emplace(rightUnit, id++);
                tabla.addNode();
            }


            //now add this to the graph with the right edge weight.
            tabla.add_edge(unitsName[leftUnit], unitsName[rightUnit], rightVal);
            tabla.add_edge(unitsName[rightUnit], unitsName[leftUnit], 1/rightVal);

        }
    }

    double NumberWithUnits::getRatio(string otherUnit) const {
        if(this->unit == otherUnit){
            return 1;
        }
        else if(unitsName.find(this->unit) != unitsName.end() && unitsName.find(otherUnit) != unitsName.end()) {
            int src = unitsName.find(this->unit)->second;
            int dest = unitsName.find(otherUnit)->second;
            double ratio = tabla.dijkstra(src, dest);
            if(ratio > 0){
                if(ratio == 1 && this->unit != otherUnit){
                    throw invalid_argument("Units do not match - [" + otherUnit + "] cannot be converted to [" + unit + "]");
                }
//                cout<<"From: " << this->unit << "To: " << otherUnit << "MultBy: " << ratio<<endl;
                return 1/ratio;
            }
        }
        else{
            throw invalid_argument("unit do not exist");
        }
        throw invalid_argument("Units do not match - [" + otherUnit + "] cannot be converted to [" + unit + "]");
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
    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits& other)
    {
        double ratio = getRatio(other.unit);
        return NumberWithUnits(this->number+(other.number*ratio), this->unit);

    }
    //Add to this.
    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &other)
    {
        double ratio = getRatio(other.unit);
        this->number+=(other.number*ratio);
        return *this;
    }
    //Unary +. (Does nothing)
    NumberWithUnits &NumberWithUnits::operator+()
    {
        return *this;
    }

    // //Sub two numbers.
    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &other)
    {
        double ratio = getRatio(other.unit);
        return NumberWithUnits(this->number-(other.number*ratio), this->unit);
    }

    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &other)
    {
        double ratio = getRatio(other.unit);
        this->number-=(other.number*ratio);
        return *this;
    }
    //Unary -. (Change sign)
    NumberWithUnits &NumberWithUnits::operator-()
    {
        NumberWithUnits* copy = this;
        copy->number = (-1)*(this->number);
        return *copy;
    }

    //LET.
    bool operator<(const NumberWithUnits &current, const NumberWithUnits &other)
    {
        double ratio = current.getRatio(other.unit);

        if(current.get_number()-other.get_number()*ratio < -EPSILON){
            return true;
        }
        else{
            return false;
        }
    }
    //LEQ.
    bool operator<=(const NumberWithUnits &current, const NumberWithUnits &other)
    {
        double ratio = current.getRatio(other.unit);
        if(current.get_number()-other.get_number()*ratio < -EPSILON){
            return true;
        }
        else if(current.get_number() - (other.get_number()*ratio) < EPSILON &&
                current.get_number() - (other.get_number()*ratio) > -EPSILON){
            return true;
        }
        else{
            return false;
        }
    }
    //Equals.
    bool operator==(const NumberWithUnits &current, const NumberWithUnits &other)
    {
        double ratio = current.getRatio(other.unit);
        return current.get_number() - (other.get_number()*ratio) < EPSILON &&
                current.get_number() - (other.get_number()*ratio) > -EPSILON;
    }
    //GEQ.
    bool operator>=(const NumberWithUnits &current, const NumberWithUnits &other)
    {
        double ratio = current.getRatio(other.unit);
        if(current.get_number()-other.get_number()*ratio > EPSILON){
            return true;
        }
        else if(current.get_number() - (other.get_number()*ratio) < EPSILON &&
                current.get_number() - (other.get_number()*ratio) > -EPSILON){
            return true;
        }
        else{
            return false;
        }
    }
    //GET.
    bool operator>(const NumberWithUnits &current, const NumberWithUnits &other)
    {
        double ratio = current.getRatio(other.unit);
        if(current.get_number()-other.get_number()*ratio > EPSILON){
            return true;
        }
        else{
            return false;
        }
    }
    //DIFF.
    bool operator!=(const NumberWithUnits &current, const NumberWithUnits &other)
    {
        double ratio = current.getRatio(other.unit);
        return !(current.get_number() - (other.get_number()*ratio) < EPSILON &&
               current.get_number() - (other.get_number()*ratio) > -EPSILON);
    }
    //Pre-increment.
    NumberWithUnits &NumberWithUnits::operator++()
    {
        static NumberWithUnits copy = *this;
        copy.number = ++number;
        return copy;
    }
    //Post-increment.
    NumberWithUnits &NumberWithUnits::operator++(int)
    {
        static NumberWithUnits copy = *this;
        copy.number = number++;
        return copy;
    }

    //Pre-deccrement.
    NumberWithUnits &NumberWithUnits::operator--()
    {
        static NumberWithUnits copy = *this;
        copy.number = --number;
        return copy;
    }
    //Post-deccrement.
    NumberWithUnits &NumberWithUnits::operator--(int)
    {
        static NumberWithUnits copy = *this;
        copy.number = number--;
        return copy;
    }

    //Mult with double.
    NumberWithUnits NumberWithUnits::operator*(double d)
    {
        NumberWithUnits temp{this->number*d, this->unit};
        return temp;
    }
    NumberWithUnits operator*(double d, const NumberWithUnits &other)
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
        string unit;
        double num;
        string equal;

        in >> num >> equal >> unit;
        other.number = num;
        other.unit = unit;
        return in;
    }

}