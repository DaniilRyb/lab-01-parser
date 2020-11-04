// Copyright 2020 <Daniil Rybakov>
#ifndef INCLUDE_PARSER_HPP_
#define INCLUDE_PARSER_HPP_
#include "student.hpp"
#include <iostream>
#include <iomanip>
#include "string"
#include <vector>
using nlohmann::json;

class Parser {
 public:
  Parser();
  explicit Parser(const std::string &JsonObject);
  void Print(const student_t& student);
  void PrintStudents();
  std::vector<student_t> students;
};
#endif // INCLUDE_PARSER_HPP_