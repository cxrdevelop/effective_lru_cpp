#ifndef LRU_HPP
#define LRU_HPP

#include <list>
#include <unordered_map>
#include <iostream>

namespace v1 {

template<typename T, std::size_t N>
class LRUCache {
    std::list<T> list_;
    std::unordered_map<T, typename std::list<T>::iterator> map_;
    using list_t = std::list<T>;

public:
    using iterator = typename list_t::iterator;
    using const_iterator = typename list_t::const_iterator;

    constexpr const_iterator cbegin() const noexcept(noexcept(std::cbegin(std::list<T>{}))) {
        return std::cbegin(list_);
    }
    constexpr const_iterator cend() const noexcept(noexcept(std::cend(std::list<T>{}))) {
        return std::cend(list_);
    }

    constexpr const_iterator begin() const noexcept(noexcept(std::begin(std::list<T>{}))) {
        return std::begin(list_);
    }
    constexpr const_iterator end() const noexcept(noexcept(std::end(std::list<T>{}))) {
        return std::end(list_);
    }

    bool has(const T& key) {
        auto it = map_.find(key);
        if (it == std::end(map_)) return false;

        auto list_it = it->second;
        list_.erase(list_it);
        it->second = list_.insert(list_.end(), key);
        return true;
    }

    bool put(const T& key) {
        auto it = map_.find(key);
        if (it != std::end(map_)) {
            list_.erase(it->second);
            it->second = list_.insert(std::end(list_), key);

            //list_.splice(std::end(list_), list_, it->second);
            return false;
        }

        if (list_.size() == N) {
            T last = list_.front();
            list_.pop_front();
            map_.erase(last);
            map_[key] = list_.insert(std::end(list_), key);
        } else {
            map_[key] = list_.insert(std::end(list_), key);
        }
        return true;
    }

    void refer(T x) {
        // not present in cache
        if (map_.find(x) == map_.end()) {
            if (list_.size() == N) {
                // delete least recently used element
                const T& last = list_.back();
                // Erase the last
                map_.erase(last);

                // Pops the last element
                list_.pop_back();
            }
        } else {
            list_.erase(map_[x]);
        }

        // update reference
        list_.push_front(x);
        map_[x] = list_.begin();
    }
};
}
#endif // LRU_HPP
