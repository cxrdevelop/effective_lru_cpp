#include <iostream>

#include "lru.hpp"

int main() {

    LRUCache<std::string,4> ca;

    ca.refer("1");
    ca.refer("2");
    ca.refer("3");
    ca.refer("4");
    ca.refer("5");
    ca.refer("6");
    ca.refer("4");

    for (const auto &s : ca) {
        std::cout << s << ", ";
    }
    std::cout << std::endl;

    return 0;
}
