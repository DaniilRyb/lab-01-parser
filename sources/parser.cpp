//
// Created by daniilrybakov on 24.10.2020.
//

#include "../include/parser.hpp"
#include "student.cpp"
#include <fstream>


Parser::Parser(const std::string &JsonObject) {

  if(JsonObject.empty()) {
    throw std::invalid_argument("Error! JsonObject is empty!");
  }

  std::ifstream JsonFile{JsonObject};
  if (!JsonFile.is_open()) {
    throw std::out_of_range("unable to open json: " + JsonObject);
  }

  json data;
  JsonFile >> data;

  if (!data.at("items").is_array()) {
    throw std::invalid_argument("Items are not array!");
  }


  if (data.at("items").size() != data.at("_meta").at("count").get<size_t>()) {
    throw std::invalid_argument("Error! _meta != number of students");
  }

  for (auto const &student : data.at("items")) {
    students.push_back(student_t{student});
  }


}


/*
| name          | group  | avg  | debt          |
|---------------|--------|------|---------------|
| Ivanov Petr   | 1      | 4.25 | null          |
|---------------|--------|------|---------------|
| Sidorov Ivan  | 31     | 4.00 | C++           |
|---------------|--------|------|---------------|
| Pertov Nikita | IU8-31 | 3.33 | 3 items       |
|---------------|--------|------|---------------|
 */

void Parser::Print(student_t &student, std::ostream &os) {

  if(std::any_cast<json>(student.GetName()).is_string()) {
    os <<"|"<< " " << std::any_cast<json>(student.GetName()).get<std::string>()<< "  "; // std::any_cast<json>(student.GetName())
  }
  if(std::any_cast<json>(student.GetGroup()).is_number()) {
    os <<"|" << " " << std::any_cast<json>(student.GetGroup()).get<int>()<< "  ";
  }else{
    os <<"|" << " " << std::any_cast<json>(student.GetGroup()).get<std::string>()<<std::setw(6);
  }
  os << "|" << " " << student.GetAvg() << std::setw(2);

  if(std::any_cast<json>(student.GetDebt()).is_null()) {
    os << "| " << "null" << std::setw(10) << std::endl;

  }else if (std::any_cast<json>(student.GetDebt()).is_number()) {
    os <<  std::any_cast<json>(student.GetDebt()).get<int>() << " items" << std::setw(9) << "|" << std::endl;

  }else{
    //auto v = std::any_cast<json>(student.GetDebt()).get<std::vector<std::string>>();
    os << "| " << std::any_cast<json>(student.GetDebt()).get<std::string>() << std::setw(9) << std::endl;

  }


}

void Parser::PrintStudents(std::vector<student_t> &s, std::ostream os) {

  for (auto &student : s) {
    Print(student, os);
  }

}