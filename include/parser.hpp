

// Created by daniilrybakov on 24.10.2020.
//

#ifndef LAB01_PARSER_PARSER_HPP
#define LAB01_PARSER_PARSER_HPP
#include "../../../.hunter/_Base/9a3594a/2c824f9/48401e9/Install/include/nlohmann/json.hpp"
#include "student.hpp"
#include <iostream>
#include <iomanip>
using nlohmann::json;


class Parser {
 public:

  Parser(const std::string &JsonObject);
  void Print(student_t& student, std::ostream& os);
  void PrintStudents(std::vector<student_t>& s, std::ostream os);
  std::vector<student_t> students;


};


#endif //LAB01_PARSER_PARSER_HPP
