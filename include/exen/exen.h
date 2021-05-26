/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

// clang-format off

#ifndef __EXEN_ENUM_NAME
  #error No enum name defined! Define __EXEN_ENUM_NAME before include "exen/exen.h". (e.g. --> #define __EXEN_ENUM_NAME MySuperStatemachineStates)
#endif //__EXEN_ENUM_NAME

#include <string>
#include <array>
#include <limits>
#include <algorithm>

#ifndef __EXEN_PREPROCESSOR_DEFINES
  #define __EXEN_PREPROCESSOR_DEFINES

  #define __EXEN_FUNC_CHOOSER(_f0, _f1, _f2, ...) _f2
  #define __EXEN_FUNC_RECOMPOSER(argsWithParentheses) __EXEN_FUNC_CHOOSER argsWithParentheses
  #define __EXEN_CHOOSE_FROM_ARG_COUNT(F, ...) __EXEN_FUNC_RECOMPOSER((__VA_ARGS__, F##_2, F##_1, ))
  #define __EXEN_NO_ARG_EXPANDER(FUNC) ,,,FUNC ## _0
  #define __EXEN_MACRO_CHOOSER(FUNC, ...) __EXEN_CHOOSE_FROM_ARG_COUNT(FUNC, __EXEN_NO_ARG_EXPANDER __VA_ARGS__ (FUNC))
  #define __EXEN_VARIABLE_MACRO_ARGUMENTS(FUNC, ...) __EXEN_MACRO_CHOOSER(FUNC, __VA_ARGS__)(__VA_ARGS__)

  #define __EXEN_PPCAT_NX(A, B) A##B
  #define __EXEN_PPCAT(A, B) __EXEN_PPCAT_NX(A, B)
  #define __EXEN_PPSTR_NX(A) #A
  #define __EXEN_PPSTR(A) __EXEN_PPSTR_NX(A)
  #define __EXEN_PP2STRS(A, B) __EXEN_PPSTR_NX(A::B)

  #define __EXEN_ENUM_P_DECL(_ce_name) __EXEN_PPCAT(private_, _ce_name)
  #define __EXEN_INCLUDE_ENUM(_ce_file) __EXEN_PPSTR(_ce_file.enum)
  #define __EXEN_ENUM_ENTRY(...) __EXEN_VARIABLE_MACRO_ARGUMENTS(__EXEN_ENUM_ENTRY, __VA_ARGS__)
#endif //__EXEN_PREPROCESSOR_DEFINES

#ifdef __EXEN_NAMESPACE
namespace __EXEN_NAMESPACE {
#endif //__EXEN_NAMESPACE
namespace __EXEN_ENUM_NAME {
namespace detail {
#define __EXEN_ENUM_P __EXEN_ENUM_P_DECL(__EXEN_ENUM_NAME)
enum class __EXEN_ENUM_P
{
  #define __EXEN_ENUM_ENTRY_1(__enum_entry) __enum_entry,
  #define __EXEN_ENUM_ENTRY_2(__enum_entry, __enum_value) __enum_entry = __enum_value,
  #include __EXEN_INCLUDE_ENUM(__EXEN_ENUM_NAME)
  #undef __EXEN_ENUM_ENTRY_1
  #undef __EXEN_ENUM_ENTRY_2
};

constexpr auto min = std::min({
    #define __EXEN_ENUM_ENTRY_1(__enum_entry) __EXEN_ENUM_P::__enum_entry,
    #define __EXEN_ENUM_ENTRY_2(__enum_entry, __enum_value) __EXEN_ENUM_P::__enum_entry,
    #include __EXEN_INCLUDE_ENUM(__EXEN_ENUM_NAME)
    #undef __EXEN_ENUM_ENTRY_1
    #undef __EXEN_ENUM_ENTRY_2
  });
constexpr auto max = std::max({
    #define __EXEN_ENUM_ENTRY_1(__enum_entry) __EXEN_ENUM_P::__enum_entry,
    #define __EXEN_ENUM_ENTRY_2(__enum_entry, __enum_value) __EXEN_ENUM_P::__enum_entry,
    #include __EXEN_INCLUDE_ENUM(__EXEN_ENUM_NAME)
    #undef __EXEN_ENUM_ENTRY_1
    #undef __EXEN_ENUM_ENTRY_2
  });

using optimal_unsigned_integer_size_type =
  std::conditional<std::numeric_limits<std::uint8_t>::max() >= static_cast<std::uint64_t>(max), std::uint8_t,
    std::conditional<std::numeric_limits<std::uint16_t>::max() >= static_cast<std::uint64_t>(max), std::uint16_t,
      std::conditional<std::numeric_limits<std::uint32_t>::max() >= static_cast<std::uint64_t>(max), std::uint32_t,
        std::uint64_t
      >::type
    >::type
  >::type;
} // namespace detail

/** Enumeration __EXEN_ENUM_NAME */
enum __EXEN_ENUM_NAME : detail::optimal_unsigned_integer_size_type
{
  #define __EXEN_ENUM_ENTRY_1(__enum_entry) __enum_entry,
  #define __EXEN_ENUM_ENTRY_2(__enum_entry, __enum_value) __enum_entry = __enum_value,
  #include __EXEN_INCLUDE_ENUM(__EXEN_ENUM_NAME)
  #undef __EXEN_ENUM_ENTRY_1
  #undef __EXEN_ENUM_ENTRY_2
};

namespace detail {
constexpr std::array private_array{
    #define __EXEN_ENUM_ENTRY_1(__enum_entry) __EXEN_ENUM_NAME::__enum_entry,
    #define __EXEN_ENUM_ENTRY_2(__enum_entry, __enum_value) __EXEN_ENUM_NAME::__enum_entry,
    #include __EXEN_INCLUDE_ENUM(__EXEN_ENUM_NAME)
    #undef __EXEN_ENUM_ENTRY_1
    #undef __EXEN_ENUM_ENTRY_2
  };
} // namespace detail

/** Returns a std::array containing all enumeration entries. */
constexpr auto array() {
  return detail::private_array;
}

/** Returns the first enumeration entry. */
constexpr __EXEN_ENUM_NAME first() {
  return array().front();
}
/** Returns the last enumeration entry. */
constexpr __EXEN_ENUM_NAME last() {
  return array().back();
}

/** Returns the smallest enumeration entry. */
constexpr __EXEN_ENUM_NAME min() {
  return static_cast<__EXEN_ENUM_NAME>(detail::min);
}

/** Returns the biggest enumeration entry. */
constexpr __EXEN_ENUM_NAME max() {
  return static_cast<__EXEN_ENUM_NAME>(detail::max);
}

/** Returns the count of enumeration entries. */
constexpr std::uint64_t count() { return array().size(); }

/** Returns the name of the enumeration type itself. */
constexpr std::string_view type_name() {
#ifdef __EXEN_NAMESPACE
  return std::string_view(__EXEN_PP2STRS(__EXEN_NAMESPACE, __EXEN_ENUM_NAME));
#else //__EXEN_NAMESPACE
  return std::string_view(__EXEN_PPSTR(__EXEN_ENUM_NAME));
#endif //__EXEN_NAMESPACE
}

namespace detail {
static_assert(count() != 0,
              __EXEN_PPSTR(There are no enumerator entries in the __EXEN_INCLUDE_ENUM(__EXEN_ENUM_NAME) file));

template<typename _Tp>
constexpr inline bool unique_entries(const _Tp array) {
  for (std::size_t outer = 1; outer < array.size(); ++outer) {
    for (std::size_t inner = 0; inner < outer; ++inner) {
      if (array[outer] == array[inner]) {
        return false;
      }
    }
  }
  return true;
}

static_assert(unique_entries(array()),
              __EXEN_PPSTR(The enumerator entries must be unique: check enum __EXEN_NAMESPACE::__EXEN_ENUM_NAME));

constexpr auto enum_names = std::array {
  #define __EXEN_ENUM_ENTRY_1(__enum_entry) std::string_view(#__enum_entry),
  #define __EXEN_ENUM_ENTRY_2(__enum_entry, __enum_value) std::string_view(#__enum_entry),
  #include __EXEN_INCLUDE_ENUM(__EXEN_ENUM_NAME)
  #undef __EXEN_ENUM_ENTRY_1
  #undef __EXEN_ENUM_ENTRY_2
};
template<typename _Tp>
constexpr inline std::size_t index_of(_Tp array, const Car::Color::Color val) {
  for(std::size_t idx = 0; idx < array.size(); ++idx) {
    if (array[idx] == val) {
      return idx;
    }
  }
  return -1;
}
} // namespace detail

/** Returns the string representation of the given enumeration entry. */
constexpr std::string_view name(__EXEN_ENUM_NAME entry) {
  return detail::enum_names[detail::index_of(array(), entry)];
}
} // namespace __EXEN_ENUM_NAME
#ifdef __EXEN_NAMESPACE
} // namespace __EXEN_NAMESPACE
#endif //__EXEN_NAMESPACE

#ifdef __EXEN_NAMESPACE
std::ostream& operator<<(std::ostream& stream, __EXEN_NAMESPACE::__EXEN_ENUM_NAME::__EXEN_ENUM_NAME rhs)
{
  stream << __EXEN_NAMESPACE::__EXEN_ENUM_NAME::name(rhs);
  return stream;
}
#else //__EXEN_NAMESPACE
std::ostream& operator<<(std::ostream& stream, __EXEN_ENUM_NAME::__EXEN_ENUM_NAME rhs)
{
  stream << __EXEN_ENUM_NAME::name(rhs);
  return stream;
}
#endif //__EXEN_NAMESPACE

#undef __EXEN_ENUM_P
#undef __EXEN_ENUM_NAME
#undef __EXEN_NAMESPACE

// clang-format on
