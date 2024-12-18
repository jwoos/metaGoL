#pragma once

#include <array>
#include <stddef.h>
#include <type_traits>

#include "utils.hpp"

template <size_t X, size_t Y> struct Coordinate {
  static constexpr size_t x = X;
  static constexpr size_t y = Y;
};

template <size_t Width, size_t Height> struct Grid {
  template <typename... Coords> static consteval Grid make(Coords &&...coords) {
    static_assert(
        (std::is_same_v<Coordinate<Coords::x, Coords::y>, Coords> && ...));
    Grid grid;
    (grid.set<Coords>(true), ...);
    return grid;
  }

  constexpr Grid() : grid() {
    std::for_each(grid.begin(), grid.end(), [](auto &row) {
      std::for_each(row.begin(), row.end(), [](auto &cell) { cell = false; });
    });
  }

  template <typename Coord> constexpr void set(bool val) {
    static_assert((Coord::x < width));
    static_assert((Coord::y < height));
    grid[Coord::x][Coord::y] = val;
  }

  /**
   *   0 1 2 3 4 - width
   * 0 x x x x x
   * 1 x x x x x
   * 2 x x x x x
   * 3 x x x x x
   * 4 x x x x x
   * - height
   */
  static_assert(Width > 0 && Height > 0,
                "width and height of the grid must be > 0");
  static constexpr size_t width = Width;
  static constexpr size_t height = Height;
  std::array<std::array<bool, Width>, Height> grid;
};
