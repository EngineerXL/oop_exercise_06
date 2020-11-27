#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

#include <list>

template<class T, std::size_t BLOCK_SIZE>
class linear_allocator_t {
private:
	std::list<T*> lst;
	T* buffer;
public:
	/*
	 * std::allocator_traits
	 */
	using allocator_type = linear_allocator_t;
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using const_reference = const T&;
	using size_type = std::size_t;

	T* allocate(const std::size_t & n) {
		if (lst.empty()) {
			buffer = new T[BLOCK_SIZE];
			for (std::size_t i = 0; i < BLOCK_SIZE; ++i) {
				lst.push_back(&buffer[i]);
			}
		}
		printf("Allocatind %lu bytes in block with %lu free bytes\n", n, lst.size());
		if (lst.size() < n) {
			throw(std::bad_alloc());
		} else {
			T* p = lst.front();
			for (std::size_t i = 0; i < n; ++i) {
				lst.pop_front();
			}
			return p;
		}
	}

	/*
	 * Allocator can't call constructor,
	 * so programm should call it manually
	 * OTHER_T is type of allocating variable
	 * ARGS... is arguments for constructor
	 */
	template<class OTHER_T, class... ARGS>
	void construct(OTHER_T* p, ARGS... arguments) {
		*p =  OTHER_T(std::forward<ARGS>(arguments)...);
	}

	/*
	 * Linear allocator can't call delete
	 * at the middle of allocated memory
	 */
	void deallocate(pointer, std::size_t) {
		;
	}

	linear_allocator_t() : lst(), buffer(nullptr) {
		static_assert(BLOCK_SIZE > 0);
	}

	explicit linear_allocator_t(const linear_allocator_t<T, BLOCK_SIZE> & another_allocator) : linear_allocator_t() {
		buffer = new T[BLOCK_SIZE];
		for (std::size_t i = 0; i < BLOCK_SIZE; ++i) {
			buffer[i] = another_allocator.buffer[i];
			lst.push_back(&buffer[i]);
		}
	}

	~linear_allocator_t() {
		delete[] buffer;
	}

	/*
	 * This method is used to get
	 * another allocator type
	 */
	template<class OTHER_T>
	class rebind {
	public:
		using other = linear_allocator_t<OTHER_T, BLOCK_SIZE>;
	};
};

#endif /* ALLOCATOR_HPP */