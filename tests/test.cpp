//
// Copyright 2020 Daniil Rybakov <pochtaworld7@gmail.com>
//
#include <gtest/gtest.h>
#include <iostream>
#include "parser.hpp"
#include "student.hpp"
std::vector<student_t> students;
TEST(parser, TheFirstCheckIsValidStudent) {
  student_t st1(json::parse(R"(
 {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    }
)"));
  ASSERT_EQ(st1.GetName(), "Ivanov Petr");
  ASSERT_EQ(std::any_cast<json>(st1.GetGroup()).get<std::string>(), "1");
  ASSERT_DOUBLE_EQ(st1.GetAvg(), 4.25);
  ASSERT_TRUE(std::any_cast<json>(st1.GetDebt()).is_null());
}
TEST(parser, TheSecondCheckIsValidStudent) {
  student_t st2{json::parse(R"(
 {
      "name": "Sidorov Ivan",
      "group": "31",
      "avg": 4.25,
      "debt": "C++"
    }
)")};
  ASSERT_EQ(st2.GetName(), "Sidorov Ivan");
  ASSERT_EQ(std::any_cast<json>(st2.GetGroup()).get<std::string>(), "31");
  ASSERT_DOUBLE_EQ(st2.GetAvg(), 4.25);
  ASSERT_EQ(std::any_cast<json>(st2.GetDebt()).get<std::string>(), "C++");
}
  TEST(parser, The3CheckIsValidStudent) {
  student_t st3(json::parse(R"(
{
      "name": "Petrov Nikita",
      "group": "IU8-33",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
)"));

  ASSERT_EQ(st3.GetName(), "Petrov Nikita");
  ASSERT_EQ(std::any_cast<json>(st3.GetGroup()).get<std::string>(), "IU8-33");
  ASSERT_DOUBLE_EQ(st3.GetAvg(), 3.33);
  ASSERT_TRUE(std::any_cast<json>(st3.GetDebt()).is_array());
}
TEST(parser, Throw_Exceptions_Test1) {
  ASSERT_THROW(Parser(""), std::invalid_argument);
  ASSERT_THROW(Parser("NameFileIsNotExist"), std::runtime_error);
  ASSERT_THROW(Parser((R"({})")), std::invalid_argument);
  ASSERT_THROW(Parser(R"({"items": 5})"), std::invalid_argument);
}
 TEST(parser, countOfStudents) {
    ASSERT_THROW(Parser((R"({
"items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Petrov Nikita",
      "group": "IU8-33",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 4
  }})")), std::out_of_range); }
