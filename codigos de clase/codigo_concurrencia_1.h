#include <chrono>
#include <future> // Contiene la función std::async
#include <thread>
#include <print>

using namespace std::chrono_literals;
/*

auto do_something_1 (int i) -> int  // función que toma un entero, le suma uno y lo devuelve
{
	std::println("starting ds1");
	std::this_thread::sleep_for(5s); // le hacemos esperar unos segundos para simular operaciones de alto rendimiento
	std::println("ending ds1");
	return i + 1;
}

auto do_something_2() -> void
{
	std::println("starting ds2");
	std::this_thread::sleep_for(8s);
	std::println("ending ds2");
}

auto main() -> int
{
	using clock = std::chrono::steady_clock;
	
		auto const start = clock.now(); // graba el momento en el que se empieza a ejecutar el programa
	std::future<int> ftr = std::async(std::launch::async, do_something_1, 9); // crea un objeto de tipo future que llame a la función ds1 creando un hilo meidante async (que toma como parámetros la política de creación de hilos, qué hacer con el hilo, y parámetros que necesite)
	do_something_2();
	auto j = ftr:get(); // guarda lo obtenido en ftr (es decir, lo obtenido de la función do_something_1)
	auto const end = clock.now(); // graba el momento en el que se termina de ejecutar el programa
	std::println("j = {}", j);
	
	std::println("duration: {} segundos", std::chrono::duration_cast<std::chrono::seconds>(end - start).count());	
}*/