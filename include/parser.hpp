

// Created by daniilrybakov on 24.10.2020.
//

#ifndef LAB01_PARSER_PARSER_HPP
#define LAB01_PARSER_PARSER_HPP
#include "student.hpp"
#include <iostream>
#include <iomanip>
using nlohmann::json;


class Parser {
 public:
  Parser();
  void parser(const std::string &JsonObject);
  void Print(const student_t& student);
  void PrintStudents();
  //void set_json(const std::string &JsonObject);
  std::vector<student_t> students;
};


#endif //LAB01_PARSER_PARSER_HPP
