#include "Color2.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(test_exen, test_color2_example_and_all_exen_provided_functions)
{
  EXPECT_EQ(Car::Color2::name(Car::Color2::kRED), "RED");
  EXPECT_EQ(Car::Color2::name(Car::Color2::kGREEN), "GREEN");
  EXPECT_EQ(Car::Color2::name(Car::Color2::kBLUE), "BLUE");
  EXPECT_EQ(Car::Color2::kBLUE, 55000);
  EXPECT_EQ(Car::Color2::kORANGE, 55001);
  EXPECT_EQ(Car::Color2::kRED, Car::Color2::min());
  EXPECT_EQ(Car::Color2::kORANGE, Car::Color2::max());
  EXPECT_EQ(Car::Color2::kRED, Car::Color2::array()[0]);
  EXPECT_EQ(Car::Color2::kGREEN, Car::Color2::array()[1]);
  EXPECT_EQ(Car::Color2::kBLUE, Car::Color2::array()[2]);
  EXPECT_EQ(Car::Color2::array().size(), Car::Color2::count());
  EXPECT_EQ(Car::Color2::count(), 4);
  EXPECT_EQ(Car::Color2::kRED, Car::Color2::first());
  EXPECT_EQ(Car::Color2::kORANGE, Car::Color2::last());
  EXPECT_EQ("Car::Color2", Car::Color2::type_name());
  std::stringstream ss;
  ss << Car::Color2::kRED;
  EXPECT_EQ(ss.str(), std::string("RED"));
  constexpr bool color_t_is_uint16_t =
      std::is_same<std::underlying_type_t<Car::Color2::Color2>,
                   std::uint16_t>::value;
  EXPECT_TRUE(color_t_is_uint16_t);
}
