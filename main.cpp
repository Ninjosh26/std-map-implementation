#include "Map.h"
#include <iostream>
#include <string>

// Used for printing out pairs
template<typename Key, typename Val>
std::ostream& operator<<(std::ostream& os, const std::pair<Key, Val>& p) {
    os << "{" << p.first << ", " << p.second << "}";
    return os;
}

// Used for printing out map
template<typename Key, typename Val>
std::ostream& operator<<(std::ostream& os, const Map<Key, Val>& m) {
    for (auto i = m.begin(); i != m.end(); i++) {
        os << *i << " ";
    }

    return os;
}

int main() {
    // Aliasing map iterator types
    using iterator = Map<int, std::string>::iterator;
    using const_iterator = Map<int, std::string>::const_iterator;
    using reverse_iterator = Map<int, std::string>::reverse_iterator;
    using const_reverse_iterator = Map<int, std::string>::const_reverse_iterator;

    // Creating a default map
    Map<int, std::string> m1;

    // Printing out default map
    std::cout << "Size of m1: " << m1.size() << std::endl;
    std::cout << "Contents of m1: " << m1 << std::endl << std::endl;

    // Adding pair explicitly
    std::pair<int, std::string> p = {3, "Three"};
    m1.insert(p);
    std::cout << "Added 3" << std::endl;

    // Adding pair implicitly
    m1.insert({7, "Seven"});
    std::cout << "Added 7" << std::endl << std::endl;

    // Printing out map
    std::cout << "Size of m1: " << m1.size() << std::endl;
    std::cout << "Contents of m1: " << m1 << std::endl << std::endl;

    // Constructing map from initializer list
    Map<int, std::string> m2({{2, "Apple"}, {5, "Orange"}, {1, "Grape"}, {4, "Banana"}});
    std::cout << "Size of m2: " << m2.size() << std::endl;
    std::cout << "Contents of m2: " << m2 << std::endl << std::endl;

    // Swapping maps
    m1.swap(m2);
    std::cout << "Maps swapped" << std::endl << std::endl;

    std::cout << "Size of m1: " << m1.size() << std::endl;
    std::cout << "Contents of m1: " << m1 << std::endl << std::endl;

    std::cout << "Size of m2: " << m2.size() << std::endl;
    std::cout << "Contents of m2: " << m2 << std::endl << std::endl;




    // Copy constructor
    Map<int, std::string> m3(m2);
    std::cout << "Copied m2 into m3" << std::endl << std::endl;

    std::cout << "Size of m2: " << m2.size() << std::endl;
    std::cout << "Contents of m2: " << m2 << std::endl << std::endl;

    std::cout << "Size of m3: " << m3.size() << std::endl;
    std::cout << "Contents of m3: " << m3 << std::endl << std::endl;

    // Changes to one, don't affect copy
    m2.insert({5, "Five"});
    std::cout << "Added 5 to m2" << std::endl << std::endl;

    // Erase by key
    m3.erase(3);
    std::cout << "Removed 3 from m3" << std::endl << std::endl;

    std::cout << "Size of m2: " << m2.size() << std::endl;
    std::cout << "Contents of m2: " << m2 << std::endl << std::endl;

    std::cout << "Size of m3: " << m3.size() << std::endl;
    std::cout << "Contents of m3: " << m3 << std::endl << std::endl;




    // Copy assignment
    m3 = m1;
    std::cout << "Copied m1 into m3" << std::endl << std::endl;

    std::cout << "Size of m3: " << m3.size() << std::endl;
    std::cout << "Contents of m3: " << m3 << std::endl << std::endl;




    // Move constructor
    Map<int, std::string> m4(std::move(m2));
    std::cout << "Moved m2 into m4" << std::endl << std::endl;

    std::cout << "Size of m2: " << m2.size() << std::endl;
    std::cout << "Contents of m2: " << m2 << std::endl << std::endl;

    std::cout << "Size of m4: " << m4.size() << std::endl;
    std::cout << "Contents of m4: " << m4 << std::endl << std::endl;




    // Move assignment
    std::cout << "Size of m1: " << m1.size() << std::endl;
    std::cout << "Contents of m1: " << m1 << std::endl << std::endl;

    m1 = std::move(m4);
    std::cout << "Moved m4 into m1" << std::endl << std::endl;

    std::cout << "Size of m1: " << m1.size() << std::endl;
    std::cout << "Contents of m1: " << m1 << std::endl << std::endl;

    std::cout << "Size of m4: " << m4.size() << std::endl;
    std::cout << "Contents of m4: " << m4 << std::endl << std::endl;




    // Range constructor
    iterator x = m1.begin();
    x++;
    x++;
    Map<int, std::string> m5(m1.begin(), x);
    std::cout << "Copied first two elements of m1 into m5" << std::endl << std::endl;

    std::cout << "Size of m5: " << m5.size() << std::endl;
    std::cout << "Contents of m5: " << m5 << std::endl << std::endl;




    // Reverse iterator
    std::cout << "Reverse contents of m3: ";
    for (reverse_iterator i = m3.rbegin(); i != m3.rend(); i++) {
        std::cout << *i << " ";
    }
    std::cout << std::endl << std::endl;




    // Empty
    std::cout << "m3 is empty: " << std::boolalpha << m3.empty() << std::endl << std::endl;




    // [] operator
    std::cout << "m3[4] = " << m3[4] << std::endl << std::endl;
    m3[4] = "Lemon";
    std::cout << "Changed 4 to Lemon" << std::endl << std::endl;

    std::cout << "Size of m3: " << m3.size() << std::endl;
    std::cout << "Contents of m3: " << m3 << std::endl << std::endl;

    m3[3] = "Lime";
    std::cout << "Set 3 to Lime" << std::endl << std::endl;

    std::cout << "Size of m3: " << m3.size() << std::endl;
    std::cout << "Contents of m3: " << m3 << std::endl << std::endl;




    // at()
    std::cout << "m3.at(2) = " << m3.at(2) << std::endl << std::endl;

    try {
        std::cout << "Attempting m3.at(7)..." << std::endl;
        m3.at(7) = "Mango";
        std::cout << "No error!" << std::endl << std::endl;
    } catch (std::out_of_range) {
        std::cout << "at() errors if the key doesn't exist yet!" << std::endl << std::endl;
    }




    // Erase with iterator
    std::cout << "Removing all even keys from m3..." << std::endl;
    for (iterator iter = m3.begin(); iter != m3.end();) {
        if (iter->first % 2 == 0) {
            iter = m3.erase(iter);
        } else {
            iter++;
        }
    }

    std::cout << "Size of m3: " << m3.size() << std::endl;
    std::cout << "Contents of m3: " << m3 << std::endl << std::endl;





    // size_t erase
    std::cout << "Attempting to remove 5..." << std::endl;
    if (m3.erase(5)) {
        std::cout << "Erase successful!" << std::endl << std::endl; 
    } else {
        std::cout << "Erase failed" << std::endl << std::endl;
    }

    std::cout << "Size of m3: " << m3.size() << std::endl;
    std::cout << "Contents of m3: " << m3 << std::endl << std::endl;

    std::cout << "Attempting to remove 4..." << std::endl;
    if (m3.erase(5)) {
        std::cout << "Erase successful!" << std::endl << std::endl; 
    } else {
        std::cout << "Erase failed" << std::endl << std::endl;
    }

    std::cout << "Size of m3: " << m3.size() << std::endl;
    std::cout << "Contents of m3: " << m3 << std::endl << std::endl;





    // Range erase
    Map<int, std::string> m6 = {
        {1, "One"},
        {2, "Two"},
        {3, "Three"},
        {4, "Four"},
        {5, "Five"}, 
        {6, "Six"},
        {7, "Seven"}
    };

    std::cout << "Size of m6: " << m6.size() << std::endl;
    std::cout << "Contents of m6: " << m6 << std::endl << std::endl;

    const_iterator three = ++(++(m6.cbegin()));
    const_iterator six = --(--(m6.cend()));
    std::cout << *three << std::endl;
    std::cout << *six << std::endl;

    std::cout << "Erasing [3, 6)..." << std::endl;
    m6.erase(three, six);

    std::cout << "Size of m6: " << m6.size() << std::endl;
    std::cout << "Contents of m6: " << m6 << std::endl << std::endl;




    // find
    std::cout << "Searching for 7..." << std::endl;
    iterator seven = m6.find(7);
    std::cout << "Found: " << *seven << std::endl << std::endl;





    // count
    if (m6.count(4)) {
        std::cout << "Four is in the map" << std::endl << std::endl;
    } else {
        std::cout << "Four is not in the map" << std::endl << std::endl;
    }




    // lower bound
    std::cout << "Looking for element with lower bound of 3..." << std::endl;
    std::cout << "Found: " << *(m6.lower_bound(3)) << std::endl << std::endl; 




    // upper bound
    std::cout << "Looking for element with upper bound of 5..." << std::endl;
    std::cout << "Found: " << *(m6.upper_bound(5)) << std::endl << std::endl; 




    // equal range
    std::cout << "Looking for range of elements with key = 7..." << std::endl;
    std::cout << "Found: ";
    auto range = m6.equal_range(7);
    for (const_iterator i = range.first; i != range.second; i++) {
        std::cout << *i << " ";
    }
    std::cout << std::endl << std::endl;




    // clear
    std::cout << "Clearing m6..." << std::endl;
    m6.clear();
    std::cout << "Size of m6: " << m6.size() << std::endl;
    std::cout << "Contents of m6: " << m6 << std::endl << std::endl;





    // Destructor
    std::cout << "Deleting all maps..." << std::endl;
}