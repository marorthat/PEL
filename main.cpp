#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
#include <future>
#include <ranges>

using uf32 = std::uint_fast32_t;

uf32 find_max_in_range(auto chunk) {
    return *std::ranges::max_element(chunk);
}

/*
uf32 find_max_in_range(const std::vector<uf32>& data, std::size_t begin, std::size_t end) {
    return *std::ranges::max_element(data.begin() + begin, data.begin() + end);
}
*/
int main() {
    // Parámetros
    const std::size_t vector_size = 100'000'000;
    const int num_threads = std::thread::hardware_concurrency();
    //Abreviaciones
    


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

    //Creamos una caja inicialmente vacia donde se introducira el resultado de cada hilo:
    auto futuros = std::vector<std::future<uf32>>{};

    for(int f=0;f<num_threads-1;f++)
    {
        futuros.push_back(std::async(std::launch::async,find_max_in_range(data),.....));
    }




   

    // Tiempo de ejecución
    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);

    // Impresión del resultado
    
    std::cout << "Tiempo de ejecución: " << duration.count() << " ms" << std::endl;

    return 0;
}