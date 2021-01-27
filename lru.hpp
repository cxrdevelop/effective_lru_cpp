#ifndef LRU_HPP
#define LRU_HPP

#include <list>
#include <unordered_map>
#include <iostream>

template<typename T, std::size_t N>
class LRUCache {
    std::list<T> dq;
    std::unordered_map<T, typename std::list<T>::iterator> ma;
    using list_t = std::list<T>;

public:
    using iterator = typename list_t::iterator;
    using const_iterator = typename list_t::const_iterator;

    constexpr const_iterator cbegin() const noexcept(noexcept(std::cbegin(std::list<T>{}))) {
        return std::cbegin(dq);
    }
    constexpr const_iterator cend() const noexcept(noexcept(std::cend(std::list<T>{}))) {
        return std::cend(dq);
    }

    constexpr const_iterator begin() const noexcept(noexcept(std::begin(std::list<T>{}))) {
        return std::begin(dq);
    }
    constexpr const_iterator end() const noexcept(noexcept(std::end(std::list<T>{}))) {
        return std::end(dq);
    }

    /*constexpr iterator begin() noexcept(noexcept(std::begin(std::list<T>{}))) {
        return std::begin(dq);
    }
    constexpr iterator end() noexcept(noexcept(std::end(std::list<T>{}))) {
        return std::end(dq);
    }*/

    void refer(T x) {
        // not present in cache
        if (ma.find(x) == ma.end()) {
            if (dq.size() == N) {
                // delete least recently used element
                const T& last = dq.back();
                // Erase the last
                ma.erase(last);

                // Pops the last element
                dq.pop_back();
            }
        } else {
            dq.erase(ma[x]);
        }

        // update reference
        dq.push_front(x);
        ma[x] = dq.begin();
    }
};

#endif // LRU_HPP
