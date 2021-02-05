#include <benchmark/benchmark.h>
#include <type_traits>

template<typename LRU>
static void BM_Creation(benchmark::State& state) {
    for ([[maybe_unused]] auto _ : state) {
        LRU lru;
    }
}

template<typename LRU>
static void BM_InsertIntoEmpty(benchmark::State& state) {
    LRU lru;

    for ([[maybe_unused]] auto _ : state) {
        for (typename LRU::size_type i = 0; i < LRU::size; ++i) {
            if constexpr (std::is_same_v<typename LRU::value_type,std::string>) {
                lru.put(std::to_string(i));
            } else {
                lru.put(i);
            }
        }
    }
}

template<typename LRU>
static void BM_CheckKey(benchmark::State& state) {
    LRU lru;

    for (typename LRU::size_type i = 0; i < LRU::size; ++i) {
        if constexpr (std::is_same_v<typename LRU::value_type,std::string>) {
            lru.put(std::to_string(i));
        } else {
            lru.put(i);
        }
    }

    for ([[maybe_unused]] auto _ : state) {
        for (typename LRU::size_type i = 0; i < LRU::size; ++i) {
            if constexpr (std::is_same_v<typename LRU::value_type,std::string>) {
                lru.has(std::to_string(i));
            } else {
                lru.has(i);
            }
        }
    }
}

template<typename LRU>
static void BM_PutOverflow(benchmark::State& state) {
    LRU lru;
    for (typename LRU::size_type i = 0; i < LRU::size; ++i) {
        if constexpr (std::is_same_v<typename LRU::value_type,std::string>) {
            lru.put(std::to_string(i));
        } else {
            lru.put(i);
        }
    }

    for ([[maybe_unused]] auto _ : state) {
        for (typename LRU::size_type i = LRU::size; i < LRU::size+LRU::size+1; ++i) {
            if constexpr (std::is_same_v<typename LRU::value_type,std::string>) {
                lru.put(std::to_string(i));
            } else {
                lru.put(i);
            }
        }
    }
}
