//
// Copyright 2020 Daniil Rybakov <pochtaworld7@gmail.com>
//
//
#include "parser.hpp"
#include <fstream>
std::vector<student_t> s_t;
const size_t ten = 10;
const size_t two = 2;
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
    s_t = students;
  }
}
std::ostream& operator<<(std::ostream& out, std::vector<student_t> st) {
  st = s_t;
  std::string s = "|";
  std::string headerTable ="";
  size_t a1 = 0, a2 = 0, a3 = 0, a4 = 0;
  std::vector<size_t> new_fields = {15, 8, 6, 15};
  std::vector<std::string> header = {"|name", "|group", "|avg", "|debt"};
  for (const auto &student : st) {
    if (std::any_cast<json>(student.GetName()).get<std::string>().length() >=
        new_fields[0]) {
        new_fields[0] =
            std::any_cast<json>(student.GetName()).get<std::string>().length();
      }
      if (std::any_cast<json>(student.GetGroup()).is_string()) {
         new_fields[1] = std::any_cast<json>(student.GetAvg()).
             get<std::string>().length();
    }
      new_fields[2] =
          std::any_cast<json>(student.GetAvg()).get<std::string>().length();
    if (std::any_cast<json>(student.GetDebt()).is_string() &&
        std::any_cast<json>(student.GetDebt()).get<std::string>().length()>=
          new_fields[3]){
      new_fields[3] =
          std::any_cast<json>(student.GetDebt()).get<std::string>().length();
    } else {
      std::string it = std::to_string(std::any_cast<json>(student.GetDebt())
                                          .get<std::vector<std::string>>()
                                          .size()) + " items";
    }
    for (size_t i = 0; i < new_fields[0]; ++i) {
      s+= "-";
    }
    s+="|";
    a1 = s.length() - ten;
    headerTable += header[0];
    for (size_t i = 0; i < a1; ++i) {
      headerTable += " ";
    }
    for (size_t i = 0; i < new_fields[1]; ++i) {
      s+= "-";
    }
    s+="|";
    a2 = s.length() - two;
    headerTable += header[1];
    for (size_t i = 0; i < a2; ++i) {
      headerTable += " ";
    }
    for (size_t i = 0; i < new_fields[2]; ++i) {
      s+= "-";
    }
    s+="|";
     a3 = s.length() - two;
    headerTable += header[2];
    for (size_t i = 0; i < a3; ++i) {
      headerTable += " ";
    }
    for (size_t i = 0; i < new_fields[3]; ++i) {
      s+= "-";
    }
    s+="|";
    a4 = s.length() - ten;
    headerTable += header[3];
    for (size_t i = 0; i < a4; ++i) {
      headerTable += " ";
    }

    headerTable+="|";
    out << headerTable << std::endl;
    out << s << std::endl;

    std::cout << "|" << student.GetName() << std::setw(new_fields[0]);
    if (std::any_cast<json>(student.GetGroup()).is_string()) {
      out << "|" <<
          std::any_cast<json>(student.GetGroup()).get<std::string>()
              << std::setw(new_fields[1]);
    } else {
      out << "|" <<
                std::any_cast<json>(student.GetGroup()).get<size_t>()
                << std::setw(new_fields[1]);
    }
    if (std::any_cast<json>(student.GetAvg()).get<std::string>().length()) {
      out << "|" <<
                std::any_cast<json>(student.GetAvg()).get<size_t>()
                << std::setw(new_fields[2]);
    } else {
      out << "|" <<
                std::any_cast<json>(student.GetAvg()).get<size_t>()
                << std::setw(new_fields[2]);
    }
    if (std::any_cast<json>(student.GetDebt()).is_null()) {
      out << "| null" << std::setw(new_fields[3]) << std::endl;
    }
     if (std::any_cast<json>(student.GetDebt()).is_string()){
      out << "| "
                << std::any_cast<json>(student.GetDebt()).get<std::string>()
                << std::setw(new_fields[3]) << std::endl;
       } else {
      std::string it = std::to_string(std::any_cast<json>(student.GetDebt())
                                          .get<std::vector<std::string>>()
                                          .size()) + " items";
      out << "| " << it << std::setw(new_fields[3]) << std::endl;
    }
     }
  out << s << std::endl;
  return out;
}
