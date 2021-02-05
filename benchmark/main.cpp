#include <benchmark/benchmark.h>
#include "lru_v1.h"
#include "lru_v2.h"
#include "lru_v3.h"
#include "lru_v4.h"
#include "bench.hpp"

BENCHMARK_MAIN();

constexpr std::size_t lru_size=100000000;
using testing_type = std::int32_t;

using type_v1 = v1::LRUCache<testing_type,lru_size>;
using type_v2 = v2::LRUCache<testing_type,lru_size>;
using type_v3 = v3::LRUCache<testing_type,lru_size>;
using type_v4 = v4::LRUCache<testing_type,lru_size>;

BENCHMARK_TEMPLATE(BM_Creation, type_v1);
BENCHMARK_TEMPLATE(BM_Creation, type_v2);
BENCHMARK_TEMPLATE(BM_Creation, type_v3);
BENCHMARK_TEMPLATE(BM_Creation, type_v4);


BENCHMARK_TEMPLATE(BM_InsertIntoEmpty, type_v1);
BENCHMARK_TEMPLATE(BM_InsertIntoEmpty, type_v2);
BENCHMARK_TEMPLATE(BM_InsertIntoEmpty, type_v3);
BENCHMARK_TEMPLATE(BM_InsertIntoEmpty, type_v4);

BENCHMARK_TEMPLATE(BM_CheckKey, type_v1);
BENCHMARK_TEMPLATE(BM_CheckKey, type_v2);
BENCHMARK_TEMPLATE(BM_CheckKey, type_v3);
BENCHMARK_TEMPLATE(BM_CheckKey, type_v4);


BENCHMARK_TEMPLATE(BM_PutOverflow, type_v1);
BENCHMARK_TEMPLATE(BM_PutOverflow, type_v2);
BENCHMARK_TEMPLATE(BM_PutOverflow, type_v3);
BENCHMARK_TEMPLATE(BM_PutOverflow, type_v4);
