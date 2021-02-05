#pragma once

#include <list>
#include <unordered_map>

namespace v3 {

template<typename T, std::size_t N>
class LRUCache {
    std::list<T> list_;
    std::unordered_map<T, typename std::list<T>::iterator> map_;
    using list_t = std::list<T>;

public:
    using iterator = typename list_t::iterator;
    using const_iterator = typename list_t::const_iterator;
    using value_type = T;
    using size_type = decltype(N);
    static constexpr std::size_t size = N;

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
        list_.splice(list_.end(), list_, list_it);
        return true;
    }

    bool put(const T& key) {
        auto it = map_.find(key);
        if (it != std::end(map_)) {
            auto list_it = it->second;
            list_.splice(list_.end(), list_, list_it);
            return false;
        }

        if (list_.size() == N) {
            T last = list_.front();
            auto node = map_.extract(last);
            list_.front() = key;
            list_.splice(std::end(list_), list_, std::begin(list_));
            node.key() = key;
            node.mapped() = --std::end(list_);
            map_.insert(std::move(node));
        } else {
            map_[key] = list_.insert(std::end(list_), key);
        }
        return true;
    }
};
}
