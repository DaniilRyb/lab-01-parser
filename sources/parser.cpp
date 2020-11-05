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
void Parser::Print() {
  std::string s1 = "| name          | group  | avg  | debt          |";
  std::string s2 = "|---------------|--------|------|---------------|";
  std::cout << s1 << std::endl;
  std::cout << s2 << std::endl;
  for (const auto &student : students) {
    size_t length_of_field_name = 15;
    int length_of_field_group = 8, length_of_field_debt = 15;
    //size_t  length_of_field_avg = 6;
    if (std::any_cast<json>(student.GetName()).is_string()) { //parsing of name
      if (std::any_cast<json>(student.GetName()).get<std::string>().length() >=
          length_of_field_name) {
        length_of_field_name =
            std::any_cast<json>(student.GetName()).get<std::string>().length();
      } else {
        std::cout << "| "
                  << std::any_cast<json>(student.GetName()).get<std::string>()
                  << std::setw(length_of_field_name);
      }
    }
    if (std::any_cast<json>(student.GetGroup()).is_number()) {
      if (std::any_cast<json>(student.GetGroup()).get<int>() >=
          length_of_field_group) {
        length_of_field_group =
            std::any_cast<json>(student.GetGroup()).get<int>();
      } else if (std::any_cast<json>(student.GetAvg()).is_string()) {
        std::cout << "| "
                  << std::any_cast<json>(student.GetGroup()).get<std::string>()
                  << std::setw(length_of_field_group);
      } else {
        std::cout << "| " << std::any_cast<json>(student.GetGroup()).get<int>()
                  << std::setw(length_of_field_group);
      }
    }
    std::cout << "| "
              << student.GetAvg()
              << std::setw(length_of_field_group);
    if (std::any_cast<json>(student.GetDebt()).is_null()) { // parsing of dept
      std::cout << "| null" << std::setw(length_of_field_debt) << std::endl;
    }
     if (std::any_cast<json>(student.GetDebt()).is_string()){
      std::cout << "| "
                << std::any_cast<json>(student.GetDebt()).get<std::string>()
                << std::setw(length_of_field_debt) << std::endl;
       } else {
      std::string it = std::to_string(std::any_cast<json>(student.GetDebt())
                                          .get<std::vector<std::string>>()
                                          .size()) + " items";
      std::cout << "| " << it << std::setw(length_of_field_debt) << std::endl;
    }
     }
  std::cout << "|---------------|--------|------|---------------|";
}