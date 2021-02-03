#include <benchmark/benchmark.h>
#include "lru.hpp"

constexpr std::size_t lru_size=10000;

static void BM_Creation(benchmark::State& state) {
    for ([[maybe_unused]] auto _ : state) {
        v1::LRUCache<int,lru_size> lru;
    }
}
BENCHMARK(BM_Creation);

static void BM_InsertIntoEmpty(benchmark::State& state) {
    v1::LRUCache<std::uint64_t,lru_size> lru;

    for ([[maybe_unused]] auto _ : state) {
        for (std::uint64_t i = 0; i < lru_size; ++i) {
            lru.put(i);
        }
    }
}
BENCHMARK(BM_InsertIntoEmpty);

static void BM_CheckKey(benchmark::State& state) {
    v1::LRUCache<std::uint64_t,lru_size> lru;
    for (std::uint64_t i = 0; i < lru_size; ++i) {
        lru.put(i);
    }

    for ([[maybe_unused]] auto _ : state) {
        for (std::uint64_t i = 0; i < lru_size; ++i) {
            lru.has(i);
        }
    }
}
BENCHMARK(BM_CheckKey);

static void BM_PutOverflow(benchmark::State& state) {
    v1::LRUCache<std::uint64_t,lru_size> lru;
    for (std::uint64_t i = 0; i < lru_size; ++i) {
        lru.put(i);
    }

    for ([[maybe_unused]] auto _ : state) {
        for (std::uint64_t i = lru_size; i < lru_size+lru_size+1; ++i) {
            lru.put(i);
        }
    }
}
BENCHMARK(BM_PutOverflow);

BENCHMARK_MAIN();
