#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
#include <future>
#include <ranges>
#include <print>
 
using uf32 = std::uint_fast32_t;
using namespace std::chrono_literals;
 
uf32 find_max_in_range(const auto chunk) {
    return *std::ranges::max_element(chunk);
}
 
int main() {
    // Parámetros
    using clock = std::chrono::steady_clock;
    auto const start = clock::now();
    const std::size_t vector_size = 100'000'000;
    
    // Generación de datos aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uf32> dist(0, std::numeric_limits<uf32>::max());
    std::vector<uf32> data{};
    //Funcion para rellenar codigo:
    for(std::size_t i=0;i<vector_size;i++)
    {
        data.push_back(dist(gen));
    }

    const int hc = std::thread::hardware_concurrency();
    auto const max_chunk_sz = data.size()/hc;
    auto for_each = [&](auto chunk) -> uf32
    {
        return find_max_in_range(chunk);
    };

    auto first = data.begin();
    auto last = first + max_chunk_sz;
    auto futures = std::vector<std::future<uf32>>{};

    for (auto i = 0; i < hc-1; ++i)
    {
            futures.push_back(std::async(std::launch::async, for_each, std::ranges::subrange{first, last}));
            first = last;
            last += max_chunk_sz;
            std::println("El máximo de este vector es: {}", for_each(std::ranges::subrange{first, last}) );
    }

   futures.push_back(std::async(std::launch::async, for_each, std::ranges::subrange{first, data.end()}));

    std::vector<uf32> results;
    for (auto& f : futures) {
        results.push_back(f.get()); 
    }

    auto max_value = *std::ranges::max_element(results);


    auto const end = clock::now(); // graba el momento en el que se termina de ejecutar el programa
	
	
    std::println("");
    std::println("Número máximo en el vector: {}", max_value);
    std::println("duration: {} milisegundos", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());


    return 0;
}