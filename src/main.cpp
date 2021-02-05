#include <iostream>

#include "lru_v1.h"

int main() {

    v1::LRUCache<std::string,4> ca;

    ca.put("1");
    ca.put("2");
    ca.put("3");
    ca.put("4");
    ca.put("5");
    ca.put("6");
    ca.put("4");

    for (const auto &s : ca) {
        std::cout << s << ", ";
    }
    std::cout << std::endl;

    return 0;
}
