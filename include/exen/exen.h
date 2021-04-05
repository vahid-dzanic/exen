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

#ifndef __EXEN_PREPROCESSOR_DEFINES
  #define __EXEN_PREPROCESSOR_DEFINES

  #define __EXEN_PPCAT_NX(A, B) A##B
  #define __EXEN_PPCAT(A, B) __EXEN_PPCAT_NX(A, B)
  #define __EXEN_PPSTR_NX(A) #A
  #define __EXEN_PPSTR(A) __EXEN_PPSTR_NX(A)

  #define __EXEN_ENUM_P_DECL(_ce_name) __EXEN_PPCAT(private_, _ce_name)
  #define __EXEN_INCLUDE_ENUM(_ce_file) __EXEN_PPSTR(_ce_file.enum)
#endif //__EXEN_PREPROCESSOR_DEFINES

#ifdef __EXEN_NAMESPACE
namespace __EXEN_NAMESPACE {
#endif //__EXEN_NAMESPACE
namespace __EXEN_ENUM_NAME {
namespace detail {
#define __EXEN_ENUM_P __EXEN_ENUM_P_DECL(__EXEN_ENUM_NAME)
enum class __EXEN_ENUM_P
{
  #define __EXEN_ENUM_ENTRY(__enum_entry) __enum_entry,
  #include __EXEN_INCLUDE_ENUM(__EXEN_ENUM_NAME)
  #undef __EXEN_ENUM_ENTRY
  COUNT
};
} // namespace detail
/** Returns the count of enumeration entries. */
constexpr std::uint64_t count() { return static_cast<std::uint64_t>(detail::__EXEN_ENUM_P::COUNT); }

namespace detail {
static_assert(count() != 0,
              __EXEN_PPSTR(There are no enumerator entries in the __EXEN_INCLUDE_ENUM(__EXEN_ENUM_NAME) file));

using optimal_unsigned_integer_size_type =
  std::conditional<std::numeric_limits<std::uint8_t>::max() >= count(), std::uint8_t,
    std::conditional<std::numeric_limits<std::uint16_t>::max() >= count(), std::uint16_t,
      std::conditional<std::numeric_limits<std::uint32_t>::max() >= count(), std::uint32_t,
        std::uint64_t
      >::type
    >::type
  >::type;
} // namespace detail

/** Enumeration __EXEN_ENUM_NAME */
enum __EXEN_ENUM_NAME : detail::optimal_unsigned_integer_size_type
{
  #define __EXEN_ENUM_ENTRY(__enum_entry) __enum_entry,
  #include __EXEN_INCLUDE_ENUM(__EXEN_ENUM_NAME)
  #undef __EXEN_ENUM_ENTRY
};

/** Returns a std::array containing all enumeration entries. */
constexpr std::array<__EXEN_ENUM_NAME, count()> array() {
  return std::array<__EXEN_ENUM_NAME, count()>{{
    #define __EXEN_ENUM_ENTRY(__enum_entry) __EXEN_ENUM_NAME::__enum_entry,
    #include __EXEN_INCLUDE_ENUM(__EXEN_ENUM_NAME)
    #undef __EXEN_ENUM_ENTRY
  }};
}

/** Returns the first enumeration entry. */
constexpr __EXEN_ENUM_NAME first() {
  return static_cast<__EXEN_ENUM_NAME>(0); // with c++17 use array().front();
}
/** Returns the last enumeration entry. */
constexpr __EXEN_ENUM_NAME last() {
  return static_cast<__EXEN_ENUM_NAME>(count() - 1); // with c++17 use array().back();
}

namespace detail {
//with c++17 use std::string_view instead of const char*
constexpr std::array<const char*, count()> enum_names =
{{
  #define __EXEN_ENUM_ENTRY(__enum_entry) #__enum_entry,
  #include __EXEN_INCLUDE_ENUM(__EXEN_ENUM_NAME)
  #undef __EXEN_ENUM_ENTRY
}};
} // namespace detail

/** Returns the string representation of the given enumeration value. */
constexpr const char* name(__EXEN_ENUM_NAME value) {
  //with c++17 return std::string_view instead of const char*
  return detail::enum_names[static_cast<std::uint64_t>(value)];
}
} // namespace __EXEN_ENUM_NAME
#ifdef __EXEN_NAMESPACE
} // namespace __EXEN_NAMESPACE
#endif //__EXEN_NAMESPACE

#ifdef __EXEN_NAMESPACE
std::ostream& operator<<(std::ostream& stream, __EXEN_NAMESPACE::__EXEN_ENUM_NAME::__EXEN_ENUM_NAME rhs)
{
  stream << std::string(__EXEN_NAMESPACE::__EXEN_ENUM_NAME::name(rhs));
  return stream;
}
#else //__EXEN_NAMESPACE
std::ostream& operator<<(std::ostream& stream, __EXEN_ENUM_NAME::__EXEN_ENUM_NAME rhs)
{
  stream << std::string(__EXEN_ENUM_NAME::name(rhs));
  return stream;
}
#endif //__EXEN_NAMESPACE

#undef __EXEN_ENUM_P
#undef __EXEN_ENUM_NAME
#undef __EXEN_NAMESPACE

// clang-format on
