#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <map>
#include <set>
using namespace std;

#include "NumberWithUnits.hpp"

namespace ariel
{

    map<string, map<string, double>> NumberWithUnits::table;

    // Function to remove all spaces from a given string
    string removeSpaces(string str)
    {
        // To keep track of non-space character count
        size_t count = 0;
        string ans = "";
    
        // Traverse the given string. If current character
        // is not space, then place it at index 'count++'
        for (size_t i = 0;i< str.size(); i++){
            if (str[i] != ' '){
                ans += str[i]; // here count is
            }  
        }                      // incremented
        return ans;
    }

    NumberWithUnits::NumberWithUnits(double number, string unit)
    {
        map<string, map<string, double>> map;

        
        //If there is not units on the table.
        if(NumberWithUnits::table.size() == 0){
            throw exception();
        }

        //If the given unit, not exist on the table.
        if(NumberWithUnits::table.find(unit) != NumberWithUnits::table.end()){
            this->unit = unit;
            this->number = number;
        }
     
        throw std::bad_exception();
    }

    map<string, map<string, double>> read_units (ifstream& input)
    {
        map<string, map<string, double>> table;
        // string content ((std::istreambuf_iterator < char >(input)),
            //(std::istreambuf_iterator < char >()));


        //Get the text file line by line
        string str;
        while (getline (input, str))
            {
            str = removeSpaces(str);
            pair< pair<string, pair<string, double>>, pair<string, pair<string, double>> > p = (NumberWithUnits::helper1 (str));
            if(table.find(p.first.first) != table.end()){
                table.find(p.first.first)->second.insert(p.first.second);
            }
            if(table.find(p.second.first) != table.end()){
                table.find(p.second.first)->second.insert(p.second.second);
            }
        }
        
        return table;
    }
    // void NumberWithUnits::read_units(ifstream &input)
    // {
    //     string content( (std::istreambuf_iterator<char>(input) ),
    //                    (std::istreambuf_iterator<char>()    ) );


    //     //Get the text file line by line
    //     string str; 
    //     while (getline(input, str))
    //     {
    //         str = removeSpaces(str);
    //         NumberWithUnits::table.emplace(NumberWithUnits::helper1(str));
    //     }

    //     // // Here i will split my string by the equal sigh to get the units.
    //     // string delimiter = "=";
    //     // size_t pos = 0;
    //     // vector<string> token;
    //     // while ((pos = content.find(delimiter)) != string::npos) {
            
    //     //     token.push_back(content.substr(0, pos));
    //     //     content.erase(0, pos + delimiter.length());
    //     // }

    //     // // Now I put my data in a table.
    //     // vector<pair<NumberWithUnits*, NumberWithUnits*>> unitTable;
    //     // for(size_t i=0; i<token.size()-1; i++){
    //     //     unitTable.emplace_back(std::make_pair(NumberWithUnits::helper(token.at(2*i)), NumberWithUnits::helper(token.at(2*i+1))));
    //     //     //Here we will make a pair to the other side.
    //     //     NumberWithUnits* tempa = NumberWithUnits::helper(token.at(2*i));
    //     //     NumberWithUnits* tempb = NumberWithUnits::helper(token.at(2*i+1));

    //     //     tempa->set_number((tempa->get_number())/tempb->get_number());
    //     //     tempb->set_number(1);

    //     //     unitTable.emplace_back(std::make_pair(tempb, tempa));
    // }

    pair< pair<string, pair<string, double>>, pair<string, pair<string, double>>> NumberWithUnits::helper1 (string str)
    {
        string delimiter = "=";
        size_t pos = str.find (delimiter) - 1;
        string num;
        double number;
        if (pos != string::npos)
            {
            pair < string, pair < string, double >>entry;
            pair < string, pair < string, double >>entry1;
            entry.first = str.substr (1, pos);
            entry1.second.first = str.substr (1, pos);
            str.erase (0, pos + 1 + delimiter.length ());

            pos = 0;
            while (0 <= str.at (pos) - '0' && str.at (pos) - '0' <= 9)
            {
                num += str.at (pos);
                pos++;
            }
            number = stod (num);
            entry.second.second = number;
            entry1.second.second = 1/number;
            entry.second.first = str.substr (pos, str.size ());
            entry1.first = str.substr (pos, str.size ());
            pair< pair<string, pair<string, double>>, pair<string, pair<string, double>>> p;
            p.first = entry;
            p.second = entry1;
            return p;
        }
    }

    NumberWithUnits* NumberWithUnits::helper(string s){
        int decimalCnt = 0;
        size_t i=0;
        double unitNum = 0;
        s = removeSpaces(s);
        
        while((0<= (s.at(i) - '0')) && ((s.at(i) - '0')<=9)){
            unitNum += (s.at(i) - '0')*decimalCnt;
            i++;
            decimalCnt++;
        }
        static NumberWithUnits ans{unitNum, s.substr(i)};
        return &ans;
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
        if(this->unit == other.unit){
            NumberWithUnits temp{number + other.get_number(), this->unit};
            return temp;
        }
        double multBy = NumberWithUnits::ifReachable(*this, other, NumberWithUnits::table);
        if(multBy != -1){
            NumberWithUnits temp{number + other.get_number()*multBy, this->unit};
            return temp; 
        }
        else{
            throw std::bad_exception();
        }
        
    }
    //Add to this.
    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &other)
    {
        if(this->unit == other.unit){
            this->number += (other.get_number());
            return *this; 
        }
        double multBy = NumberWithUnits::ifReachable(*this, other, this->table);
        if(multBy != -1){
            this->number += (multBy*other.get_number());
            return *this; 
        }
        else{
            throw std::bad_exception();
        }
    }
    //Unary +. (Does nothing)
    NumberWithUnits &NumberWithUnits::operator+()
    {
        return *this;
    }

    // //Sub two numbers.
    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &other)
    {
        if(this->unit == other.unit){
            return NumberWithUnits(number - other.get_number(), this->unit);
        }
        double multBy = NumberWithUnits::ifReachable(*this, other, this->table);
        if(multBy != -1){
            return NumberWithUnits(this->number - other.get_number()*multBy, this->unit); 
        }
        else{
            throw std::bad_exception();
        }
    }

    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &other)
    {
        if(this->unit == other.unit){
            this->number -= (other.get_number());
            return *this; 
        }
        double multBy = NumberWithUnits::ifReachable(*this, other, this->table);
        if(multBy != -1){
            this->number -= (multBy*other.get_number());
            return *this; 
        }
        else{
            throw std::bad_exception();
        }
    }
    //Unary -. (Change sign)
    NumberWithUnits &NumberWithUnits::operator-()
    {
        this->number = -(this->number);
        return *this;
    }

    //LET.
    bool operator<(const NumberWithUnits &current, const NumberWithUnits &other)
    {
        if(current.unit == other.unit){
            return current.number < other.number;
        }
        double multBy = NumberWithUnits::ifReachable(current, other, current.table);
        if(multBy != -1){
            NumberWithUnits temp {other.get_number()*multBy, current.unit};
            return current.number < temp.number;
        }
        else{
            throw std::bad_exception();
        }
    }
    //LEQ.
    bool operator<=(const NumberWithUnits &current, const NumberWithUnits &other)
    {
        if(current.unit == other.unit){
            return current.number <= other.number;
        }
        double multBy = NumberWithUnits::ifReachable(current, other, current.table);
        if(multBy != -1){
            NumberWithUnits temp {other.get_number()*multBy, current.unit};
            return current.number <= temp.number;
        }
        else{
            throw std::bad_exception();
        }
    }
    //Equals.
    bool operator==(const NumberWithUnits &current, const NumberWithUnits &other)
    {
        if(current.unit == other.unit){
            return current.number == other.number;
        }
        double multBy = NumberWithUnits::ifReachable(current, other, current.table);
        if(multBy != -1){
            NumberWithUnits temp {other.get_number()*multBy, current.unit};
            return current.number == temp.number;
        }
        else{
            throw std::bad_exception();
        }
    }
    //GEQ.
    bool operator>=(const NumberWithUnits &current, const NumberWithUnits &other)
    {
        if(current.unit == other.unit){
            return current.number >= other.number;
        }
        double multBy = NumberWithUnits::ifReachable(current, other, current.table);
        if(multBy != -1){
            NumberWithUnits temp {other.get_number()*multBy, current.unit};
            return current.number >= temp.number;
        }
        else{
            throw std::bad_exception();
        }
    }
    //GET.
    bool operator>(const NumberWithUnits &current, const NumberWithUnits &other)
    {
        if(current.unit == other.unit){
            return current.number > other.number;
        }
        double multBy = NumberWithUnits::ifReachable(current, other, current.table);
        if(multBy != -1){
            NumberWithUnits temp {other.get_number()*multBy, current.unit};
            return current.number > temp.number;
        }
        else{
            throw std::bad_exception();
        }
    }
    //DIFF.
    bool operator!=(const NumberWithUnits &current, const NumberWithUnits &other)
    {
        if(current.unit == other.unit){
            return current.number != other.number;
        }
        double multBy = NumberWithUnits::ifReachable(current, other, current.table);
        if(multBy != -1){
            NumberWithUnits temp {other.get_number()*multBy, current.unit};
            return current.number != temp.number;
        }
        else{
            throw std::bad_exception();
        }
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
        // in >> other.unit;
        return in;
        string num;
        double number;
        string unit;

        string input;
        in >> input;
        input = removeSpaces(input);
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

    //checks if there is path between the two units.
    double NumberWithUnits::ifReachable (const NumberWithUnits &a, const NumberWithUnits &b, map<string, map<string, double>> table){
        double multBy = 1;
        string tempUnit = a.get_unit();
        set<string> units;
        units.insert(a.get_unit());

        bool flag = true;
        map<string, map<string, double>>::iterator it = table.find(tempUnit);
        while(flag){
            if(it != table.end()){
                map<string, double>::iterator it2 = it->second.find(b.unit);
                if(it2 != it->second.end()){
                    return it2->second;
                }
                else{
                    if(units.find(it2->first) != units.end()){

                    }
                    else{
                        units.insert(it2->first);
                        it = table.find(it2->first);
                    }
                }
            }
            else{
                return -1;
            }
        }
        for(size_t i=0; i<table.size(); i++){
            map<string, map<string, double>>::iterator it = table.find(tempUnit);
            if(it != table.end()){
                map<string, double>::iterator it2 = it->second.find(b.unit);
                if(it2 != it->second.end()){
                    return it2->second;
                }
                else{

                }
            }






            if(table.at(i).first->get_unit() == tempUnit){
                if(table.at(i).second->get_unit() == b.get_unit()){
                    return table.at(i).second->get_number();
                }
                else{
                    tempUnit = table.at(i).second->get_unit();
                    if(units.find(tempUnit) == units.end()){
                        i = 0;
                        units.insert(table.at(i).second->get_unit());
                        multBy *= table.at(i).second->get_number();
                    }
                    else{
                        continue;
                    }
                }
            }
        }
        if(multBy != 1){
            return multBy;
        }
        else{
            return -1;
        }
    }

    double NumberWithUnits::ifReachable (string a, const string b, map<string, map<string, double>> table, set<string> s){
        double multBy = 1;
        set<string> units;
        units.insert(a);
        bool flag = true;
        map<string, map<string, double>>::iterator it = table.find(a);
        while(flag){
            if(it != table.end()){//If this string mapp to anything.
                map<string, double>::iterator it2 = it->second.find(b);
                if(it2 != it->second.end()){//if it has mapping to our goal.
                    return it2->second;
                }
                else{//search in different units
                    while(units.find(it2->first) == units.end() && it2 != it->second.end()){
                        if(units.find(it2->first) == units.end()){
                            double temp = NumberWithUnits::ifReachable(it2->first, b, table, units);
                            if(temp != -1){
                                return multBy*=temp;
                            }
                        }
                    }

                    if(it2 == it->second.end()){//If we iterate over all the mappings.
                        return -1;
                    }
                    else{
                        units.insert(it2->first);
                        it = table.find(it2->first);
                    }
                }
            }
            else{
                return -1;
            }
        }
    }

}