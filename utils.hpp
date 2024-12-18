#pragma once

#include <type_traits>

consteval bool isSame(auto a, auto b) {
  return std::is_same_v<decltype(a), decltype(b)>;
}
