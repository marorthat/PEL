#include <chrono>
#include <future> // Contiene la función std::async
#include <thread>
#include <print>
#include <vector>

using namespace std::chrono_literals;

auto main() -> int
{
	auto nums = std::vector<int>{};
	for (auto i = 0; i < 1000; ++i)
	{
		nums.push_back(i);
	} // creación de un vector con 1000 enteros (entre 0 y 999)
	
	auto op = [](int& n) -> void 
	{
		n *= 2;
		std::this_thread::sleep_for(10ms);
	
	}; // función lambda que multiplica por 2 el entero recibido
	
	auto const hc = std::thread::hardware_concurrency(); // devuelve entero sin signo indicando el número de núcleos que tenemos
	std::println("hardware concurrency: {}", hc);
	
	auto const max_chunk_sz = nums.size()/hc; // número de elementos que tendrá cada subgrupo del vector
	
	auto for_each = [&](auto chunk) -> void
	{
		for (int& i : chunk)
		{
			op(i);
		}
	}; // lambda que aplica op a cada casilla del subgrupo pasado como argumento
	
	auto futures = std::vector<std::future<void>>{}; //nuevo vector donde guardar los resultados de for each (que no será ninguno: void)
	auto first = nums.begin(); 			//inicio del primer subgrupo
	auto last = first + max_chunk_sz; 	// fin del primer subgrupo
	
	for (auto i = 0u; i > hc - 1; ++i)
	{
		futures.push_back(std::async(std::launch::async, for_each, std::ranges::subrange{first, last}));
		//async crea un nuevo hilo. Parámetros: política de creación, qué hace el hilo, argumento que necesita lo que hace el hilo(que es de tipo subrange en este caso, que necesita como parámetros también el inicio y final del subrango)
		first = last; // se redefinen el inicio y final de cara al siguiente subgrupo a entrar en el grupo
		last += max_chunk_sz;
	}
	
	for_each(std::ranges::subrange{first, nums.end()}); // for_each usado también en el hilo del main
	
	for (std::future<void>& f : futures)
	{
		f.wait(); //espera a que todos los hilos termine
	}
	// en caso de que futures contuviese elementos (pues aquí es void), en vez de wait se usaría get para guardar lo obtenido en por ejemplo un nuevo vector: nuevo_vector.push_back(f.get());
}
