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
  std::string s="|"; // string "-"
  std::string headerTable; // headerTable
  std::vector<size_t> new_fields = {15,8,6,15}; // пока нули
  std::vector<std::string> header = {"|name","|group","|avg","|debt"};
  for (const auto &student : students) {
    if (std::any_cast<json>(student.GetName()).is_string()) { //parsing of name
      if (std::any_cast<json>(student.GetName()).get<std::string>().length() >=
          new_fields[0]) {
        new_fields[0] =
            std::any_cast<json>(student.GetName()).get<std::string>().length();
      }
    }
    if (std::any_cast<json>(student.GetGroup()).is_number()) {
      if (std::any_cast<json>(student.GetGroup()).get<size_t>() >=
          new_fields[1]) {
        new_fields[1] = std::any_cast<json>(student.GetGroup()).get<size_t>();
      }
      } else if (std::any_cast<json>(student.GetGroup()).is_string()) {
         new_fields[1] = std::any_cast<json>(student.GetAvg()).
             get<std::string>().length();
    }
    if(std::any_cast<json>(student.GetAvg()).is_number()) {
      new_fields[2] = std::any_cast<json>(student.GetAvg()).get<size_t>();
    } else {
      new_fields[2] =
          std::any_cast<json>(student.GetAvg()).get<std::string>().length();
    }
    for (size_t i = 0; i < new_fields[0]; ++i) {
      s+= "-";
    }
    s+="|";
    //std::string s1 = "|name          |group  |avg  |debt          |";
    size_t a1 = s.length() - 10;
    headerTable += header[0];
    for (size_t i = 0; i < a1; ++i) {
      headerTable += " ";
    }
    for (size_t i = 0; i < new_fields[1]; ++i) {
      s+= "-";
    }
    s+="|";
    size_t a2 = s.length() - 2;
    headerTable += header[1];
    for (size_t i = 0; i < a2; ++i) {
      headerTable += " ";
    }
    for (size_t i = 0; i < new_fields[2]; ++i) {
      s+= "-";
    }
    s+="|";
    size_t a3 = s.length() - 2;
    headerTable += header[2];
    for (size_t i = 0; i < a3; ++i) {
      headerTable += " ";
    }
    for (size_t i = 0; i < new_fields[3]; ++i) {
      s+= "-";
    }
    s+="|";
    size_t a4 = s.length() - 10;
    headerTable += header[3];
    for (size_t i = 0; i < a4; ++i) {
      headerTable += " ";
    }
    headerTable+="|";
    std::cout << headerTable << std::endl;
    std::cout << s << std::endl;
    std::cout << "|" << student.GetName() << std::setw(new_fields[0]);
    if (std::any_cast<json>(student.GetGroup()).is_string()) {
      std::cout << "|" <<
          std::any_cast<json>(student.GetGroup()).get<std::string>()
              << std::setw(new_fields[1]);
    } else {
      std::cout << "|" <<
                std::any_cast<json>(student.GetGroup()).get<size_t>()
                << std::setw(new_fields[1]);
    }
    if(std::any_cast<json>(student.GetAvg()).get<std::string>().length()) {
      std::cout << "|" <<
                std::any_cast<json>(student.GetAvg()).get<size_t>()
                << std::setw(new_fields[2]);
    } else {
      std::cout << "|" <<
                std::any_cast<json>(student.GetAvg()).get<size_t>()
                << std::setw(new_fields[2]);
    }
    if (std::any_cast<json>(student.GetDebt()).is_null()) { // parsing of dept
      std::cout << "| null" << std::setw(new_fields[3]) << std::endl;
    }
     if (std::any_cast<json>(student.GetDebt()).is_string()){
      std::cout << "| "
                << std::any_cast<json>(student.GetDebt()).get<std::string>()
                << std::setw(new_fields[3]) << std::endl;
       } else {
      std::string it = std::to_string(std::any_cast<json>(student.GetDebt())
                                          .get<std::vector<std::string>>()
                                          .size()) + " items";
      std::cout << "| " << it << std::setw(new_fields[3]) << std::endl;
    }
     }
  std::cout << s << std::endl;
}