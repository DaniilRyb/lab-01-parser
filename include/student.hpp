//
// Created by daniilrybakov on 24.10.2020.
//

#ifndef LAB01_PARSER_STUDENT_HPP
#define LAB01_PARSER_STUDENT_HPP

#include <any>
#include <exception>
#include <string>
#include <iostream>
#include <iomanip>
#include "../../../.hunter/_Base/9a3594a/2c824f9/48401e9/Install/include/nlohmann/json.hpp"

using json = nlohmann::json;

class student_t {
 private:
  std::string name;
  std::any group;
  double avg = 0;
  std::any debt;

 public:
  student_t();
  student_t(const json& j);
  const std::string GetName() const;
  const std::any GetGroup() const;
  double GetAvg() const;
  const std::any GetDebt() const;
};

#endif  // LAB01_PARSER_STUDENT_HPP
