// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>
#include "parser.hpp"
#include "student.hpp"
#include <iostream>
using  nlohmann::json;



TEST(parser, Test2) {

  student_t st1(json::parse(R"(
 {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": 4.25,
      "debt": "C++"
    }
)"));
  ASSERT_EQ(st1.GetName(), "Ivanov Petr");
  ASSERT_EQ(std::any_cast<json>(st1.GetGroup()).get<std::string>(), "1");
  ASSERT_EQ(std::any_cast<json>(st1.GetDebt()).get<std::string>(), "C++");
  ASSERT_DOUBLE_EQ(st1.GetAvg(), 4.25);


}

