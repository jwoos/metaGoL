#pragma once

#include <array>
#include <stddef.h>
#include <type_traits>

#include "utils.hpp"

template <size_t X, size_t Y> struct Coordinate {
  static constexpr size_t x = X;
  static constexpr size_t y = Y;
};

struct Null;

template <typename... Vals>
struct sequence {
	static constexpr size_t size = sizeof...(Vals);
};

template <typename T>
struct inner_sequence;

template <typename... Inner>
struct inner_sequence<sequence<Inner...>> : public sequence<Inner...> {
};

namespace detail {

	template <typename First, typename... Rest>
	struct head_impl {
		using type = First;
	};

	template <typename First, typename... Rest>
	struct tail_impl {
		using type = sequence<Rest...>;
	};

}

template <typename T>
struct head;

template <typename... Vals>
struct head<sequence<Vals...>> : public detail::head_impl<Vals...> {
};

template <typename T>
struct tail;

template <typename... Vals>
struct tail<sequence<Vals...>> : public detail::tail_impl<Vals...> {
};

namespace detail {
	template <typename First, typename Second>
	struct last_impl {
		using type = Second;
	};

	template <typename First>
	struct last_impl<First, Null> {
		using type = First;
	};

	template <typename First, typename... Rest>
		struct last_impl<First, sequence<Rest...>> {
			using type = last_impl<Rest...>;
		};

}

template <typename T>
struct last;

template <typename... Vals>
struct last<sequence<Vals...>> : public detail::last_impl<Vals...> {};

template <typename T>
struct tuple_to_sequence;

template <typename... Inner>
struct tuple_to_sequence<std::tuple<Inner...>> {
	using type = sequence<Inner...>;
};

template <typename T, typename U>
struct concat;

template <typename T, typename... Rest>
struct concat<sequence<T>, sequence<Rest...>> : public sequence<T, Rest...> {};

// template <typename T, size_t... Idx>
// struct repeat {
// 	// FIXME: this doesn't actually do what I want it to do...
// 	using type = repeat<T, Idx...>::type;
// };

// template <typename T>
// struct repeat<T, 0> {
// 	using type = sequence<T>;
// };

// template <typename T, size_t Size>
// struct array_to_sequence;
//
// template <typename T, size_t Size>
// struct array_to_sequence<std::array<T, Size>, Size> {
// 	using type = repeat<T, Size>;
// };

template <size_t Width, size_t Height> struct Dimensions {
	static constexpr size_t width = Width;
	static constexpr size_t height = Height;
};

namespace detail {

	template <typename T, typename U>
	struct tup_from_arr_impl;

	template <typename Arr, typename... Ts>
		struct tup_from_arr_impl<Arr, sequence<Ts...>> {
			using type = std::tuple<Ts...>;
		};

}

// template <typename T, size_t Size, typename Arr = std::array<T, Size>>
// struct tup_from_arr : public detail::tup_from_arr_impl<
// 											T,
// 											sequence<size_t, >
// 											> {
// };


template <typename T, typename U>
struct concat;


template <size_t Width, size_t Height> struct Grid {
  template <typename... Coords> static consteval Grid make(Coords &&...coords) {
    static_assert(
        (std::is_same_v<Coordinate<Coords::x, Coords::y>, Coords> && ...));
    Grid grid;
    (grid.set<Coords>(true), ...);
    return grid;
  }

	template <typename T, typename Val>
	static consteval void fill(T grid, Val val) {
    std::for_each(grid.begin(), grid.end(), [&](auto &row) {
      std::for_each(row.begin(), row.end(), [&](auto &cell) { cell = val; });
    });
	}

  constexpr Grid() : grid() {
		fill(grid, false);
  }

  template <typename Coord> constexpr void set(bool val) {
    static_assert((Coord::x < width));
    static_assert((Coord::y < height));
    grid[Coord::x][Coord::y] = val;
  }

	// advances the frame
	constexpr void next() {
		std::array<std::array<uint8_t, width>, height> state;
		fill(state, 0);

		for (auto x = 0; x < width; ++x) {
			for (auto y = 0; y < height; ++y) {
				
			}
		}
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
