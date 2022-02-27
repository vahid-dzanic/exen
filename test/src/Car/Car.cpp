#include "Car.h"

#include <gtest/gtest.h>

TEST(test_exen, test_car_example_and_all_exen_provided_functions) {
  EXPECT_EQ(Car::name(Car::Mitsubishi), "Mitsubishi");
  EXPECT_EQ(Car::str(Car::Mazda), "Mazda");
  EXPECT_EQ(Car::str(Car::Honda), "Honda");
  EXPECT_EQ(Car::str(Car::Toyota), "Toyota");
}
