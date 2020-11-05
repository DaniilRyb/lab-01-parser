// Copyright 2020 <pochtaworld7@gmail.com>

#ifndef INCLUDE_STUDENT_HPP_
#define INCLUDE_STUDENT_HPP_

#include <any>
#include <exception>
#include <string>
#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class student_t {
 private:
  std::string name;
  std::any group;
  std::any avg;
  std::any debt;

 public:
  student_t();
  explicit student_t(const json& j);
  std::string GetName() const;
  std::any GetGroup() const;
  std::any GetAvg() const;
  std::any GetDebt() const;
};
#endif  // INCLUDE_STUDENT_HPP_
