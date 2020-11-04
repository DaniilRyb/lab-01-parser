//

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
  double avg = 0;
  std::any debt;

 public:
  student_t();
  explicit student_t(const json& j);
  std::string GetName() const;
  std::any GetGroup() const;
  double GetAvg() const;
  std::any GetDebt() const;
};

#endif  // LAB01_PARSER_STUDENT_HPP
