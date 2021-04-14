#include "doctest.h"
#include "NumberWithUnits.hpp"
using namespace ariel;

#include <iostream>
#include <stdexcept>
using namespace std;

TEST_CASE("Good case for (+)"){
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    ariel::NumberWithUnits a{1, "km"};
    ariel::NumberWithUnits b{1000, "m"};
    ariel::NumberWithUnits c{100, "cm"};

    //(+) for meteric units
    CHECK((a+b).get_number() == 2);
    CHECK((a+b).get_unit() == "km");

    CHECK((a+c).get_number() == 1.001);
    CHECK((a+c).get_unit() == "km");

    CHECK((b+a).get_number() == 2000);
    CHECK((b+a).get_unit() == "m");

    CHECK((b+c).get_number() == 1001);
    CHECK((b+c).get_unit() == "m");

    CHECK((c+a).get_number() == 100100);
    CHECK((c+a).get_unit() == "cm");

    CHECK((c+b).get_number() == 100100);
    CHECK((c+b).get_unit() == "cm");

    //(+) for gram's.
    a = ariel::NumberWithUnits {1, "ton"};
    b = ariel::NumberWithUnits {1000, "kg"};
    c = ariel::NumberWithUnits {1000, "g"};

    CHECK((a+b).get_number() == 2);
    CHECK((a+b).get_unit() == "ton");

    CHECK((a+c).get_number() == 1.001);
    CHECK((a+c).get_unit() == "ton");

    CHECK((b+a).get_number() == 2000);
    CHECK((b+a).get_unit() == "kg");

    CHECK((b+c).get_number() == 1001);
    CHECK((b+c).get_unit() == "kg");

    CHECK((c+a).get_number() == 1001000);
    CHECK((c+a).get_unit() == "g");

    CHECK((c+b).get_number() == 1001000);
    CHECK((c+b).get_unit() == "g");

    //(+) for time.
    a = ariel::NumberWithUnits{1, "hour"};
    b = ariel::NumberWithUnits{60, "min"};
    c= ariel::NumberWithUnits{360, "sec"};

    CHECK((a+b).get_number() == 2);
    CHECK((a+b).get_unit() == "hour");

    CHECK((a+c).get_number() == 1.1);
    CHECK((a+c).get_unit() == "hour");

    CHECK((b+a).get_number() == 120);
    CHECK((b+a).get_unit() == "min");

    CHECK((b+c).get_number() == 66);
    CHECK((b+c).get_unit() == "min");

    CHECK((c+a).get_number() == 3960);
    CHECK((c+a).get_unit() == "sec");

    CHECK((c+b).get_number() == 3960);
    CHECK((c+b).get_unit() == "sec");

    //(+) for currency
    a = ariel::NumberWithUnits{3.33, "ILS"};
    b = ariel::NumberWithUnits{1, "USD"};

    CHECK((a+b).get_number() == 6.66);
    CHECK((a+b).get_unit() == "ILS");

    CHECK((b+a).get_number() == 2);
    CHECK((b+a).get_unit() == "USD");
}

TEST_CASE("Bad case for (+)"){

}
TEST_CASE("Good case for (+=)"){
ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    ariel::NumberWithUnits a{1, "km"};
    ariel::NumberWithUnits b{1000, "m"};
    ariel::NumberWithUnits c{100, "cm"};

    //(+=) for meteric units
    a+=b;
    CHECK(a.get_number() == 2);
    CHECK(b.get_unit() == "km");
    a-=b;
    a+=c;
    CHECK(a.get_number() == 1.001);
    CHECK(a.get_unit() == "km");
    a-=c;
    b+=a;
    CHECK(b.get_number() == 2000);
    CHECK(b.get_unit() == "m");
    b-=a;
    b+=c;
    CHECK(b.get_number() == 1001);
    CHECK(b.get_unit() == "m");
    b-=c;
    c+=a;
    CHECK(c.get_number() == 100100);
    CHECK(c.get_unit() == "cm");
    c-=a;
    c+=b;
    CHECK(c.get_number() == 100100);
    CHECK(c.get_unit() == "cm");
    c-=a;
    //(+) for gram's.
    a = ariel::NumberWithUnits {1, "ton"};
    b = ariel::NumberWithUnits {1000, "kg"};
    c = ariel::NumberWithUnits {1000, "g"};
    a+=b;
    CHECK(a.get_number() == 2);
    CHECK(a.get_unit() == "ton");
    a-=b;
    a+=c;
    CHECK(a.get_number() == 1.001);
    CHECK(a.get_unit() == "ton");
    a-=c;
    b+=a;
    CHECK(b.get_number() == 2000);
    CHECK(b.get_unit() == "kg");
    b-=a;
    b+=c;
    CHECK(b.get_number() == 1001);
    CHECK(b.get_unit() == "kg");
    b-=c;
    c+=a;
    CHECK(c.get_number() == 1001000);
    CHECK(c.get_unit() == "g");
    c-=a;
    c+=b;
    CHECK(c.get_number() == 1001000);
    CHECK(c.get_unit() == "g");
    c-=b;
    //(+) for time.
    a = ariel::NumberWithUnits{1, "hour"};
    b = ariel::NumberWithUnits{60, "min"};
    c= ariel::NumberWithUnits{360, "sec"};
    a+=b;
    CHECK(a.get_number() == 2);
    CHECK(a.get_unit() == "hour");
    a-=b;
    a+=c;
    CHECK(a.get_number() == 1.1);
    CHECK(a.get_unit() == "hour");
    a-=c;
    b+=a;
    CHECK(b.get_number() == 120);
    CHECK(b.get_unit() == "min");
    b-=a;
    b+=c;
    CHECK(b.get_number() == 66);
    CHECK(b.get_unit() == "min");
    b-=c;
    c+=a;
    CHECK(c.get_number() == 3960);
    CHECK(c.get_unit() == "sec");
    c-=a;
    c+=b;
    CHECK(c.get_number() == 3960);
    CHECK(c.get_unit() == "sec");
    c-=b;
    //(+) for currency
    a = ariel::NumberWithUnits{3.33, "ILS"};
    b = ariel::NumberWithUnits{1, "USD"};
    a+=b;
    CHECK(a.get_number() == 6.66);
    CHECK(a.get_unit() == "ILS");
    a-=b;
    b+=a;
    CHECK(b.get_number() == 2);
    CHECK(b.get_unit() == "USD");
}

TEST_CASE("Bad case for (+=)"){

}
TEST_CASE("Good case for (-)"){
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    ariel::NumberWithUnits a{1, "km"};
    ariel::NumberWithUnits b{1000, "m"};
    ariel::NumberWithUnits c{100, "cm"};

    //(+) for meteric units
    CHECK((a-b).get_number() == 0);
    CHECK((a-b).get_unit() == "km");

    CHECK((a-c).get_number() == 0.999);
    CHECK((a-c).get_unit() == "km");

    CHECK((b-a).get_number() == 0);
    CHECK((b-a).get_unit() == "m");

    CHECK((b-c).get_number() == 999);
    CHECK((b-c).get_unit() == "m");

    CHECK((c-a).get_number() == -99900);
    CHECK((c-a).get_unit() == "cm");

    CHECK((c-b).get_number() == -99900);
    CHECK((c-b).get_unit() == "cm");

    //(+) for gram's.
    a = ariel::NumberWithUnits {1, "ton"};
    b = ariel::NumberWithUnits {1000, "kg"};
    c = ariel::NumberWithUnits {1000, "g"};

    CHECK((a-b).get_number() == 0);
    CHECK((a-b).get_unit() == "ton");

    CHECK((a-c).get_number() == 0.999);
    CHECK((a-c).get_unit() == "ton");

    CHECK((b-a).get_number() == 0);
    CHECK((b-a).get_unit() == "kg");

    CHECK((b-c).get_number() == 999);
    CHECK((b-c).get_unit() == "kg");

    CHECK((c-a).get_number() == -999999);
    CHECK((c-a).get_unit() == "g");

    CHECK((c-b).get_number() == -999999);
    CHECK((c-b).get_unit() == "g");

    //(+) for time.
    a = ariel::NumberWithUnits{1, "hour"};
    b = ariel::NumberWithUnits{60, "min"};
    c= ariel::NumberWithUnits{360, "sec"};

    CHECK((a-b).get_number() == 0);
    CHECK((a-b).get_unit() == "hour");

    CHECK((a-c).get_number() == 0.9);
    CHECK((a-c).get_unit() == "hour");

    CHECK((b-a).get_number() == 0);
    CHECK((b-a).get_unit() == "min");

    CHECK((b-c).get_number() == 54);
    CHECK((b-c).get_unit() == "min");

    CHECK((c-a).get_number() == -3240);
    CHECK((c-a).get_unit() == "sec");

    CHECK((c-b).get_number() == -3240);
    CHECK((c-b).get_unit() == "sec");

    //(+) for currency
    a = ariel::NumberWithUnits{3.33, "ILS"};
    b = ariel::NumberWithUnits{1, "USD"};

    CHECK((a-b).get_number() == 0);
    CHECK((a-b).get_unit() == "ILS");

    CHECK((b-a).get_number() == 0);
    CHECK((b-a).get_unit() == "USD");
}

TEST_CASE("Bad case for (-)"){

}
TEST_CASE("Good case for (-=)"){
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    ariel::NumberWithUnits a{1, "km"};
    ariel::NumberWithUnits b{1000, "m"};
    ariel::NumberWithUnits c{100, "cm"};

    //(+) for meteric units
    a-=b;
    CHECK(a.get_number() == 0);
    CHECK(a.get_unit() == "km");
    a+=b;
    a-=c;
    CHECK(a.get_number() == 0.999);
    CHECK(a.get_unit() == "km");
    a+=c;
    b-=a;
    CHECK(b.get_number() == 0);
    CHECK(b.get_unit() == "m");
    b+=a;
    b-=c;
    CHECK(b.get_number() == 999);
    CHECK(b.get_unit() == "m");
    b+=c;
    c-=a;
    CHECK(c.get_number() == -99900);
    CHECK(c.get_unit() == "cm");
    c+=a;
    c-=b;
    CHECK(c.get_number() == -99900);
    CHECK(c.get_unit() == "cm");
    c+=b;
    //(+) for gram's.
    a = ariel::NumberWithUnits {1, "ton"};
    b = ariel::NumberWithUnits {1000, "kg"};
    c = ariel::NumberWithUnits {1000, "g"};
    a-=b;
    CHECK(a.get_number() == 0);
    CHECK(a.get_unit() == "ton");
    a+=b;
    a-=c;
    CHECK(a.get_number() == 0.999);
    CHECK(a.get_unit() == "ton");
    a+=c;
    b-=a;
    CHECK(b.get_number() == 0);
    CHECK(b.get_unit() == "kg");
    b+=a;
    b-=c;
    CHECK(b.get_number() == 999);
    CHECK(b.get_unit() == "kg");
    b+=c;
    c-=a;
    CHECK(c.get_number() == -999999);
    CHECK(c.get_unit() == "g");
    c+=a;
    c-=b;
    CHECK(c.get_number() == -999999);
    CHECK(c.get_unit() == "g");
    c+=b;
    //(+) for time.
    a = ariel::NumberWithUnits{1, "hour"};
    b = ariel::NumberWithUnits{60, "min"};
    c= ariel::NumberWithUnits{360, "sec"};
    a-=b;
    CHECK(a.get_number() == 0);
    CHECK(a.get_unit() == "hour");
    a+=b;
    a-=c;
    CHECK(a.get_number() == 0.9);
    CHECK(a.get_unit() == "hour");
    a+=c;
    b-=a;
    CHECK(b.get_number() == 0);
    CHECK(b.get_unit() == "min");
    b+=a;
    b-=c;
    CHECK(b.get_number() == 54);
    CHECK(b.get_unit() == "min");
    b+=c;
    c-=a;
    CHECK(c.get_number() == -3240);
    CHECK(c.get_unit() == "sec");
    c+=a;
    c-=b;
    CHECK(c.get_number() == -3240);
    CHECK(c.get_unit() == "sec");
    c+=b;
    //(+) for currency
    a = ariel::NumberWithUnits{3.33, "ILS"};
    b = ariel::NumberWithUnits{1, "USD"};
    a-=b;
    CHECK(a.get_number() == 0);
    CHECK(a.get_unit() == "ILS");
    a+=b;
    b-=a;
    CHECK(b.get_number() == 0);
    CHECK(b.get_unit() == "USD");
}

TEST_CASE("Bad case for (-=)"){

}
TEST_CASE("Good case for (-). Change sign"){
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    //(-) fro metric.
    ariel::NumberWithUnits a{1, "km"};
    ariel::NumberWithUnits b{1000, "m"};
    ariel::NumberWithUnits c{100, "cm"};

    a = -a; b = -b; c = -c;
    CHECK((a).get_number() == -1);
    CHECK((b).get_number() == -1000);
    CHECK((c).get_number() == -100);

    a = -a; b = -b; c = -c;
    CHECK((a).get_number() == 1);
    CHECK((b).get_number() == 1000);
    CHECK((c).get_number() == 100);

    // (-) for weight
    a = ariel::NumberWithUnits {1, "ton"};
    b = ariel::NumberWithUnits {1000, "kg"};
    c = ariel::NumberWithUnits {1000, "g"};

    a = -a; b = -b; c = -c;
    CHECK((a).get_number() == -1);
    CHECK((b).get_number() == -1000);
    CHECK((c).get_number() == -100);

    a = -a; b = -b; c = -c;
    CHECK((a).get_number() == 1);
    CHECK((b).get_number() == 1000);
    CHECK((c).get_number() == 100);

    //(-) for time
    a = ariel::NumberWithUnits{1, "hour"};
    b = ariel::NumberWithUnits{60, "min"};
    c= ariel::NumberWithUnits{360, "sec"};

    a = -a; b = -b; c = -c;
    CHECK((a).get_number() == -1);
    CHECK((b).get_number() == -60);
    CHECK((c).get_number() == -60);

    a = -a; b = -b; c = -c;
    CHECK((a).get_number() == 1);
    CHECK((b).get_number() == 60);
    CHECK((c).get_number() == 60);

    //(-) for currency.
    a = ariel::NumberWithUnits{3.33, "ILS"};
    b = ariel::NumberWithUnits{1, "USD"};
    a = -a; b = -b;
    CHECK((a).get_number() == -1);
    CHECK((b).get_number() == -1000);

    a = -a; b = -b;
    CHECK((a).get_number() == 1);
    CHECK((b).get_number() == 1000);
}

TEST_CASE("Bad case for (-). Change sign"){

}
TEST_CASE("Good case for comparisons"){
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    //Comparison for length.
    ariel::NumberWithUnits a{1, "km"};
    ariel::NumberWithUnits b{1000, "m"};
    ariel::NumberWithUnits c{100, "cm"};

    CHECK((a==b) == true);
    CHECK((a>c) == true);
    CHECK((b>c) == true);

    //Comparison for weight.
    a = ariel::NumberWithUnits {1, "ton"};
    b = ariel::NumberWithUnits {1000, "kg"};
    c = ariel::NumberWithUnits {1000, "g"};

    CHECK((a==b) == true);
    CHECK((a>c) == true);
    CHECK((b>c) == true);

    //Comparison for time
    a = ariel::NumberWithUnits{1, "hour"};
    b = ariel::NumberWithUnits{60, "min"};
    c= ariel::NumberWithUnits{360, "sec"};

    CHECK((a==b) == true);
    CHECK((a>c) == true);
    CHECK((b>c) == true);  

    //Comparison for currency.
    a = ariel::NumberWithUnits{3.33, "ILS"};
    b = ariel::NumberWithUnits{1, "USD"};

    CHECK((b>a) == true);
}

TEST_CASE("Bad case for comparisons"){

}
TEST_CASE("Good case for (++)"){
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    //(++) for length.
    ariel::NumberWithUnits a{1, "km"};
    ariel::NumberWithUnits b{1000, "m"};
    ariel::NumberWithUnits c{100, "cm"};

    a++; b++; c++;
    CHECK(a.get_number() == 2);
    CHECK(b.get_number() == 1001);
    CHECK(c.get_number() == 101);

    //(++) for weight.
    a = ariel::NumberWithUnits {1, "ton"};
    b = ariel::NumberWithUnits {1000, "kg"};
    c = ariel::NumberWithUnits {1000, "g"};

    a++; b++; c++;
    CHECK(a.get_number() == 2);
    CHECK(b.get_number() == 1001);
    CHECK(c.get_number() == 101);

    //(++) for time
    a = ariel::NumberWithUnits{1, "hour"};
    b = ariel::NumberWithUnits{60, "min"};
    c= ariel::NumberWithUnits{60, "sec"};

    a++; b++; c++;
    CHECK(a.get_number() == 2);
    CHECK(b.get_number() == 61);
    CHECK(c.get_number() == 61);

    //(++) for currency.
    a = ariel::NumberWithUnits{3.33, "ILS"};
    b = ariel::NumberWithUnits{1, "USD"};

    a++; b++;
    CHECK(a.get_number() == 2);
    CHECK(b.get_number() == 1001);
}

TEST_CASE("Bad case for (++)"){

}
TEST_CASE("Good case for (--)"){
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    //(++) for length.
    ariel::NumberWithUnits a{1, "km"};
    ariel::NumberWithUnits b{1000, "m"};
    ariel::NumberWithUnits c{100, "cm"};

    a--; b--; c--;
    CHECK(a.get_number() == 0);
    CHECK(b.get_number() == 999);
    CHECK(c.get_number() == 99);

    //(++) for weight.
    a = ariel::NumberWithUnits {1, "ton"};
    b = ariel::NumberWithUnits {1000, "kg"};
    c = ariel::NumberWithUnits {1000, "g"};

    a--; b--; c--;
    CHECK(a.get_number() == 0);
    CHECK(b.get_number() == 999);
    CHECK(c.get_number() == 99);

    //(++) for time
    a = ariel::NumberWithUnits{1, "hour"};
    b = ariel::NumberWithUnits{60, "min"};
    c= ariel::NumberWithUnits{60, "sec"};

    a--; b--; c--;
    CHECK(a.get_number() == 0);
    CHECK(b.get_number() == 59);
    CHECK(c.get_number() == 59);

    //(++) for currency.
    a = ariel::NumberWithUnits{3.33, "ILS"};
    b = ariel::NumberWithUnits{1, "USD"};

    a--; b--;
    CHECK(a.get_number() == 0);
    CHECK(b.get_number() == 999);
}

TEST_CASE("Bad case for (--)"){

}
TEST_CASE("Good case for (*). left is number"){
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    //(*) for length.
    ariel::NumberWithUnits a{1, "km"};
    ariel::NumberWithUnits b{1000, "m"};
    ariel::NumberWithUnits c{100, "cm"};

    2.5*a; 2.5*b; 2.5*c;
    CHECK(a.get_number() == 2.5);
    CHECK(b.get_number() == 2500);
    CHECK(c.get_number() == 250);

    //(*) for weight.
    a = ariel::NumberWithUnits {1, "ton"};
    b = ariel::NumberWithUnits {1000, "kg"};
    c = ariel::NumberWithUnits {1000, "g"};

    2.5*a; 2.5*b; 2.5*c;
    CHECK(a.get_number() == 2.5);
    CHECK(b.get_number() == 2500);
    CHECK(c.get_number() == 250);

    //(*) for time
    a = ariel::NumberWithUnits{1, "hour"};
    b = ariel::NumberWithUnits{60, "min"};
    c= ariel::NumberWithUnits{60, "sec"};

    2.5*a; 2.5*b; 2.5*c;
    CHECK(a.get_number() == 2.5);
    CHECK(b.get_number() == 150);
    CHECK(c.get_number() == 150);

    //(*) for currency.
    a = ariel::NumberWithUnits{1000, "ILS"};
    b = ariel::NumberWithUnits{1, "USD"};

    2.5*a; 2.5*b;
    CHECK(a.get_number() == 2.5);
    CHECK(b.get_number() == 2500);
}

TEST_CASE("Bad case for (*). left is number"){

}
TEST_CASE("Good case for (*). right is number"){
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    //(*) for length.
    ariel::NumberWithUnits a{1, "km"};
    ariel::NumberWithUnits b{1000, "m"};
    ariel::NumberWithUnits c{100, "cm"};

    a*2.5; b*2.5; c*2.5;
    CHECK(a.get_number() == 2.5);
    CHECK(b.get_number() == 2500);
    CHECK(c.get_number() == 250);

    //(*) for weight.
    a = ariel::NumberWithUnits {1, "ton"};
    b = ariel::NumberWithUnits {1000, "kg"};
    c = ariel::NumberWithUnits {1000, "g"};

    a*2.5; b*2.5; c*2.5;
    CHECK(a.get_number() == 2.5);
    CHECK(b.get_number() == 2500);
    CHECK(c.get_number() == 250);

    //(*) for time
    a = ariel::NumberWithUnits{1, "hour"};
    b = ariel::NumberWithUnits{60, "min"};
    c= ariel::NumberWithUnits{60, "sec"};

    a*2.5; b*2.5; c*2.5;
    CHECK(a.get_number() == 2.5);
    CHECK(b.get_number() == 150);
    CHECK(c.get_number() == 150);

    //(*) for currency.
    a = ariel::NumberWithUnits{1000, "ILS"};
    b = ariel::NumberWithUnits{1, "USD"};

    a*2.5; b*2.5;
    CHECK(a.get_number() == 2.5);
    CHECK(b.get_number() == 2500);
}

TEST_CASE("Bad case for (*). right is number"){

}