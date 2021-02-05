#pragma once

#include <list>
#include <unordered_map>
#include <memory_resource>

namespace v4 {

template<typename T, std::size_t N>
class LRUCache {
    static constexpr std::size_t list_buffer_size = N*32;
    static constexpr std::size_t map_buffer_size = N*32;
    std::unique_ptr<std::byte[]> list_buffer;
    std::unique_ptr<std::byte[]> map_buffer;
    std::pmr::monotonic_buffer_resource list_pool;
    std::pmr::monotonic_buffer_resource map_pool;
    std::pmr::list<T> list_;
    std::pmr::unordered_map<T, typename std::pmr::list<T>::iterator> map_;
    using list_t = std::pmr::list<T>;

public:
    LRUCache() :
        list_buffer{std::make_unique<std::byte[]>(list_buffer_size)},
        map_buffer{std::make_unique<std::byte[]>(map_buffer_size)},
        list_pool{list_buffer.get(), list_buffer_size},
        map_pool{map_buffer.get(), map_buffer_size},
        list_{&list_pool},
        map_{&map_pool}
    {}
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
