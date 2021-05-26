#include "Color.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(test_exen, test_color_example_and_all_exen_provided_functions)
{
  EXPECT_EQ(Car::Color::name(Car::Color::RED), "RED");
  EXPECT_EQ(Car::Color::name(Car::Color::GREEN), "GREEN");
  EXPECT_EQ(Car::Color::name(Car::Color::BLUE), "BLUE");
  EXPECT_EQ(Car::Color::BLUE, 55000);
  EXPECT_EQ(Car::Color::ORANGE, 55001);
  EXPECT_EQ(Car::Color::RED, Car::Color::min());
  EXPECT_EQ(Car::Color::ORANGE, Car::Color::max());
  EXPECT_EQ(Car::Color::RED, Car::Color::array()[0]);
  EXPECT_EQ(Car::Color::GREEN, Car::Color::array()[1]);
  EXPECT_EQ(Car::Color::BLUE, Car::Color::array()[2]);
  EXPECT_EQ(Car::Color::array().size(), Car::Color::count());
  EXPECT_EQ(Car::Color::count(), 4);
  EXPECT_EQ(Car::Color::RED, Car::Color::first());
  EXPECT_EQ(Car::Color::ORANGE, Car::Color::last());
  EXPECT_EQ("Car::Color", Car::Color::type_name());
  std::stringstream ss;
  ss << Car::Color::RED;
  EXPECT_EQ(ss.str(), std::string("RED"));
  constexpr bool color_t_is_uint16_t =
      std::is_same<std::underlying_type_t<Car::Color::Color>,
                   std::uint16_t>::value;
  EXPECT_TRUE(color_t_is_uint16_t);
}
