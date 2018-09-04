/**
 * @brief base16 base32 base58 base64
 *
 * @file format.h
 * @author liuyujun@fingera.cn
 * @date 2018-09-04
 */
#pragma once

#include <fingera/predef.h>
#include <fingera_libc/hex.h>
#include <array>
#include <string>
#include <type_traits>
#include <vector>

namespace fingera {

namespace format_detail {

// 非指针类型
template <typename T>
static inline const void *pointer(const T &value,
                                  P_IF(!std::is_pointer<T>::value)) {
  return &value;
}
template <typename T>
static inline void *pointer(T &value, size_t,
                            P_IF(!std::is_pointer<T>::value)) {
  return &value;
}
template <typename T>
static inline size_t size(const T &value, P_IF(!std::is_pointer<T>::value)) {
  return sizeof(T);
}

// 指针类型
template <typename T>
static inline const void *pointer(const T &value,
                                  P_IF(std::is_pointer<T>::value)) {
  return value;
}
template <typename T>
static inline void *pointer(T &value, size_t, P_IF(std::is_pointer<T>::value)) {
  return value;
}
template <typename T>
static inline size_t size(const T &value, P_IF(std::is_pointer<T>::value)) {
  static_assert(std::is_trivial<typename std::remove_pointer<T>::type>::value,
                "");
  return sizeof(*value);
}

// std::vector 特化
template <typename T>
static inline const void *pointer(const std::vector<T> &value) {
  return value.data();
}
template <typename T>
static inline void *pointer(std::vector<T> &value, size_t size) {
  value.resize(size / sizeof(T));
  return value.data();
}
template <typename T>
static inline size_t size(const std::vector<T> &value) {
  static_assert(std::is_trivial<typename std::remove_pointer<T>::type>::value,
                "");
  return value.size() * sizeof(T);
}

// std::array 特化
template <typename T, size_t N>
static inline const void *pointer(const std::array<T, N> &value) {
  return value.data();
}
template <typename T, size_t N>
static inline void *pointer(std::array<T, N> &value, size_t) {
  return value.data();
}
template <typename T, size_t N>
static inline size_t size(const std::array<T, N> &value) {
  static_assert(std::is_trivial<typename std::remove_pointer<T>::type>::value,
                "");
  return value.size() * sizeof(T);
}

}  // namespace format_detail

template <typename T>
static inline void hex_dump(const T &value, bool upper = false) {
  fingera_hex_dump(format_detail::pointer(value), format_detail::size(value),
                   upper ? 1 : 0);
}

template <typename T>
static inline std::string to_hex(const T &value, bool upper = false) {
  std::string r;
  r.resize(fingera_to_hex_length(format_detail::size(value)));
  fingera_to_hex(format_detail::pointer(value), format_detail::size(value),
                 const_cast<char *>(r.c_str()), upper ? 1 : 0);
  return std::move(r);
}

template <typename T>
static inline bool from_hex(const std::string &str, T &value) {
  size_t size = fingera_from_hex(
      str.c_str(), str.size(),
      format_detail::pointer(value, fingera_from_hex_length(str.size())));
  return size == format_detail::size(value);
}

/*
template <typename T,
          P_IF(std::is_trivial<T>::value && !std::is_pointer<T>::value)>
static inline void hex_dump(const T &value, bool upper = true) {
  fingera_hex_dump(&value, sizeof(T), upper ? 1 : 0);
}

template <typename T, P_IF(std::is_trivial<T>::value)>
static inline void hex_dump(const T *value, bool upper = true) {
  fingera_hex_dump(value, sizeof(T), upper ? 1 : 0);
}

template <typename T,
          P_IF(std::is_trivial<T>::value && !std::is_pointer<T>::value)>
static inline void hex_dump(const std::vector<T> &value, bool upper = true) {
  fingera_hex_dump(value.data(), value.size() * sizeof(T), upper ? 1 : 0);
}

template <typename T, std::size_t N,
          P_IF(std::is_trivial<T>::value && !std::is_pointer<T>::value)>
static inline void hex_dump(const std::array<T, N> &value, bool upper = true) {
  fingera_hex_dump(value.data(), value.size() * sizeof(T), upper ? 1 : 0);
}
*/

}  // namespace fingera