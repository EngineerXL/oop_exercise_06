#include <algorithm>
#include "allocator.hpp"
#include "stack.hpp"
#include "square.hpp"

/*
 * Инютин М А М8О-207Б-19
 * Создать шаблон динамической коллекцию, согласно варианту
 * задания:
 * 1. Коллекция должна быть реализована с помощью умных указателей
 * (std::shared_ptr, std::weak_ptr). Опционально использование
 * std::unique_ptr;
 * 2. В качестве параметра шаблона коллекция должна принимать тип
 * данных – фигуры;
 * 3. Коллекция должна содержать метод доступа: pop, push, top;
 * 4. Реализовать аллокатор, который выделяет фиксированный размер
 * памяти (количество блоков памяти – является параметром шаблона
 * аллокатора). Внутри аллокатор должен хранить указатель на
 * используемый блок памяти и динамическую коллекцию указателей на
 * свободные блоки. Динамическая коллекция должна соответствовать
 * варианту задания (Динамический массив, Список, Стек, Очередь).
 * 5. Коллекция должна использовать аллокатор для выделения и
 * освобождения памяти для своих элементов.
 * 6. Аллокатор должен быть совместим с контейнерами std::map и
 * std::list (опционально – vector).
 * 7. Реализовать программу, которая:
 * - позволяет вводить с клавиатуры фигуры (с типом int в качестве
 *   параметра шаблона фигуры) и добавлять в коллекцию;
 * - позволяет удалять элемент из коллекции по номеру элемента;
 * - выводит на экран введенные фигуры c помощью std::for_each;
 */

const std::size_t BLOCK_SIZE = 256;

int main() {
	auto Print = [](const auto & elem) {
		std::cout << elem << std::endl;
	};
	size_t n;
	std::cout << "Input number of squares in stack" << std::endl;
	std::cin >> n;
	int cordX, cordY, side;
	stack_t< square_t<int>, linear_allocator_t< square_t<int>, BLOCK_SIZE > > st;
	for (size_t i = 0; i < n; ++i) {
		size_t n;
		std::cout << "Input index to insert a square" << std::endl;
		std::cin >> n;
		std::cout << "Input square as follows: x y a" << std::endl;
		std::cout << "x, y is a left bottom corner cords" << std::endl;
		std::cout << "a is square side" << std::endl;
		std::cin >> cordX >> cordY >> side;
		try {
			stack_t< square_t<int>, linear_allocator_t< square_t<int>, BLOCK_SIZE > >::iterator it = st.begin();
			while (n--) {
				++it;
			}
			st.insert(it, square_t<int>(std::pair<int, int>(cordX, cordY), side));
		} catch (std::runtime_error & exception) {
			std::cout << exception.what() << std::endl;
		}
	}
	std::cout << "Your input:" << std::endl;
	std::for_each(st.begin(), st.end(), Print);
	std::cout << "Input index to erase from stack" << std::endl;
	std::cin >> n;
	try {
		stack_t< square_t<int>, linear_allocator_t< square_t<int>, BLOCK_SIZE > >::iterator it = st.begin();
		while (n > 1) {
			++it;
			--n;
		}
		st.erase(it);
	} catch (std::runtime_error & exception) {
		std::cout << exception.what() << std::endl;
	}
	std::cout << "After erase:" << std::endl;
	std::for_each(st.begin(), st.end(), Print);
	return 0;
}