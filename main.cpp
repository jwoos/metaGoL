#include <iostream>

#if !defined(GRID_WIDTH) || !defined(GRID_HEIGHT)
#error "GRID_WIDTH and GRIND_HEIGHT must be defined";
#endif

#include "grid.hpp"

// TODO use the macro
using GridImpl = Grid<10, 10>;

int main() {
	auto grid = GridImpl::make(
			Coordinate<0, 0>(),
			Coordinate<1, 1>()
			);

	for (const auto& row : grid.grid) {
		for (const auto& cell : row) {
			std::cout << (cell ? "o" : "x");
		}
		std::cout << std::endl;
	}
}
