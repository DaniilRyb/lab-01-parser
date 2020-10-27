//
// Created by daniilrybakov on 24.10.2020.
//

#ifndef LAB01_PARSER_STUDENT_HPP
#define LAB01_PARSER_STUDENT_HPP

#include "../../../.hunter/_Base/9a3594a/2c824f9/48401e9/Install/include/nlohmann/json.hpp"
#include <any>
#include <exception>
#include <string>

using json = nlohmann::json;

class student_t {

 private:

  std::string name;
  std::any group;
  double avg = 0;
  std::any debt;

 public:
  student_t();
  student_t(const json & j);
  std::string GetName();
  std::any GetGroup();
  double GetAvg();
  std::any GetDebt();

};



#endif //LAB01_PARSER_STUDENT_HPP
