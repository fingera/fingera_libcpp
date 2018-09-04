#include <fingera/format.h>

#include <gtest/gtest.h>
#include <cstdint>

class alignas(1) test_class {
 public:
  uint8_t d1;
  uint8_t d2;
  test_class() : d1(0), d2(0) {}
  test_class(uint8_t x, uint8_t y) : d1(x), d2(y) {}
};

template <typename T>
static void test_from(const T &value, const std::string &hex) {
  T from_value;
  EXPECT_TRUE(fingera::from_hex(hex, from_value));
  EXPECT_EQ(fingera::to_hex(from_value), hex);
}
template <typename T>
static void test_from_p(const std::string &hex) {
  T from_value;
  EXPECT_TRUE(fingera::from_hex(hex, from_value));
  EXPECT_EQ(fingera::to_hex(from_value), hex);
}

TEST(test_format, hex) {
  uint8_t value1 = 0;
  uint16_t value2 = 0;
  uint32_t value3 = 0;
  uint64_t value4 = 0;

  struct alignas(1) {
    uint8_t d1;
    uint8_t d2;
  } struct_value = {0, 1};

  test_class class_value(0x11, 0x22);

  std::vector<uint8_t> vector_value = {0, 1, 2, 3};
  std::array<uint8_t, 5> arr_value = {0, 1, 2, 3, 4};

  uint8_t carr_value[] = {1, 2, 3, 4};

  EXPECT_EQ(fingera::to_hex(value1), "00");
  test_from(value1, "00");
  EXPECT_EQ(fingera::to_hex(value2), "0000");
  test_from(value2, "0000");
  EXPECT_EQ(fingera::to_hex(value3), "00000000");
  test_from(value3, "00000000");
  EXPECT_EQ(fingera::to_hex(value4), "0000000000000000");
  test_from(value4, "0000000000000000");
  EXPECT_EQ(fingera::to_hex(struct_value), "0001");
  test_from(struct_value, "0001");
  EXPECT_EQ(fingera::to_hex(class_value), "1122");
  test_from(class_value, "1122");
  EXPECT_EQ(fingera::to_hex(vector_value), "00010203");
  test_from(vector_value, "00010203");
  EXPECT_EQ(fingera::to_hex(arr_value), "0001020304");
  test_from(arr_value, "0001020304");
  EXPECT_EQ(fingera::to_hex(carr_value), "01020304");
  test_from(carr_value, "01020304");
  EXPECT_EQ(fingera::to_hex(&value1), "00");
  test_from_p<uint8_t>("00");
  EXPECT_EQ(fingera::to_hex(&value2), "0000");
  test_from_p<uint16_t>("0000");
  EXPECT_EQ(fingera::to_hex(&value3), "00000000");
  test_from_p<uint32_t>("00000000");
  EXPECT_EQ(fingera::to_hex(&value4), "0000000000000000");
  test_from_p<uint64_t>("0000000000000000");
  EXPECT_EQ(fingera::to_hex(&struct_value), "0001");
  test_from_p<decltype(struct_value)>("0001");
  EXPECT_EQ(fingera::to_hex(&arr_value), "0001020304");
  test_from_p<decltype(arr_value)>("0001020304");
  // EXPECT_EQ(fingera::to_hex(&class_value), "1122"); error
  // EXPECT_EQ(fingera::to_hex(&vector_value), "00010203"); error
}