#include "Map.hpp"
#include <cassert>


/*
 * Function to test new Map implementation
 */
int main() {

    // Testing default constructor --- double as Key
    cs540::Map<double, double> map0_1;
    assert(map0_1.empty());
    map0_1.insert({2.2, 30.0});
    map0_1.insert({1.1, 29.0});
    assert(!map0_1.empty());

    // Testing initializer list --- string as Key
    cs540::Map<std::string, std::string> map1_1{{"Last Name",  "L"},
                                                {"First Name", "F"}};
    cs540::Map<std::string, std::string> map1_2{map1_1};
    assert(!map1_1.empty());
    assert(!map1_2.empty());

    // // Testing assignment operator --- boolean as Key
    cs540::Map<bool, std::string> map2_1{{true,  "TRUE"},
                                         {false, "FALSE"}};
    cs540::Map<bool, std::string> map2_2{{true, "N"}};
    map2_1 = map2_1; // Self assignment
    map2_2 = map2_1; // Different assignment
    assert(!map2_1.empty());
    assert(!map2_2.empty());

    // Testing erase functionality --- passing Key as parameter
    cs540::Map<float, std::string> map3_1{{6.0, "PST"},
                                          {5.0, "OOPS"},
                                          {4.0, "OS"},
                                          {3.0, "COA"},
                                          {2.0, "PL"},
                                          {1.0, "DAA"}};
    assert(map3_1.size() == 6);
    map3_1.erase(1.0);
    assert(map3_1.size() == 5);
    map3_1.erase(6.0);
    assert(map3_1.size() == 4);
    map3_1.erase(3.0);
    assert(map3_1.size() == 3);
    map3_1.erase(2.0);
    map3_1.erase(4.0);
    map3_1.erase(5.0);
    assert(map3_1.empty());

    return 0;

}


