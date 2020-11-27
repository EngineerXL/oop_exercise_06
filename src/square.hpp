#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <iostream>
#include <tuple>

template<class T>
struct square_t {
	/* cords of left bottom corner, side */
	std::pair<T, T> cord;
	T side;

	square_t() : cord(), side() {}
	square_t(const std::pair<T, T> & xy, T l) : cord(xy), side(l) {}
};

template<class T>
T calc_square(const square_t<T> & Sq) {
	return Sq.side * Sq.side;
}

template<class T>
std::ostream & operator << (std::ostream & out, const square_t<T> & sq) {
	out << "Square {";
	out << std::pair<T, T>(sq.cord.first, sq.cord.second) << ", ";
	out << std::pair<T, T>(sq.cord.first, sq.cord.second + sq.side) << ", ";
	out << std::pair<T, T>(sq.cord.first + sq.side, sq.cord.second + sq.side) << ", ";
	out << std::pair<T, T>(sq.cord.first + sq.side, sq.cord.second);
	out << "}";
	return out;
}

template<class T1, class T2>
std::ostream & operator << (std::ostream & out, const std::pair<T1, T2> & p) {
	out << "(" << p.first << ", " << p.second << ")";
	return out;
}

#endif /* SQUARE_HPP */