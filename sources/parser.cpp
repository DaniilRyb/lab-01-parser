//
// Copyright 2020 Daniil Rybakov <pochtaworld7@gmail.com>
//
//
#include "parser.hpp"
#include <fstream>

Parser::Parser() {}
Parser::Parser(const std::string &JsonObject) {
  json j;
  if (JsonObject[0] != '{') {
    if (JsonObject.empty()) {
      throw std::invalid_argument("Json path is incorrect!");
    }
    std::ifstream file{JsonObject};
    if (!file) {
      throw std::runtime_error("unable to open json: " + JsonObject);
    }
    file >> j;
  } else {
    j = json::parse(JsonObject);
  }
  if (j.empty()) {
    throw std::invalid_argument("Object array is empty");
  }
  if (!j.at("items").is_array()) {
    throw std::invalid_argument("Json file is not array!");
  }
  if (j.at("items").size() != j.at("_meta").at("count")) {
    throw std::out_of_range("count is not equal!");
  }
  for (auto const &student : j.at("items")) {
    student_t s(student);
    students.push_back(s);
  }
}
void Parser::Print(const student_t &student) {
std::cout  << "| name        | group  | avg  | debt      |" << std::endl;
std::cout << "|---------------|--------|------|---------------|" << std::endl;
  if (std::any_cast<json>(student.GetName()).is_string()) {
    std::cout  << "|" << " " <<
        std::any_cast<json>(student.GetName()).get<std::string>() << "  ";
  }
  if (std::any_cast<json>(student.GetGroup()).is_number()) {
    std::cout  << "|" << " " <<
        std::any_cast<json>(student.GetGroup()).get<int>()<< "  ";
  }else{
    std::cout  << "|" << " " <<
        std::any_cast<json>(student.GetGroup()).get<std::string>()
            << std::setw(6);
  }
  std::cout  << "|" << " " << student.GetAvg() << std::setw(2);
  if (std::any_cast<json>(student.GetDebt()).is_null()) {
    std::cout  << "| " << "null" << std::setw(10) << std::endl;
  } else if (std::any_cast<json>(student.GetDebt()).is_number()) {
    std::cout  <<  std::any_cast<json>(student.GetDebt()).get<int>()
        << " items" << std::setw(9) << "|" << std::endl;
  }else{
    std::cout  << "| " <<
        std::any_cast<json>(student.GetDebt()).get<std::string>()
        << std::setw(9) << std::endl;
  }
  std::cout  << "|---------------|--------|------|---------------|"
            << std::endl;
}
void Parser::PrintStudents() {
  for (const auto &student : students) {
    Print(student);
  }
}




