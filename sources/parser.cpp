//
// Created by daniilrybakov on 24.10.2020.
//

#include "parser.hpp"
#include <fstream>

Parser::Parser() {}

void Parser::parser(const std::string &JsonObject) {

  if(JsonObject.empty()) {
    throw std::invalid_argument("Error! JsonObject is empty!");
  }

  std::ifstream file{JsonObject};
  if (!file) {
    throw std::runtime_error{"unable to open json: " + JsonObject};
  }

  json data;
  file >> data;

  if (!data.at("items").is_array()) {
    throw std::invalid_argument("Items are not array!");
  }


  if (data.at("items").size() != data.at("_meta").at("count").get<size_t>()) {
    throw std::invalid_argument("Error! _meta != number of students");
  }

  for (auto const &student : data.at("items")) {
    students.push_back(student);
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





void Parser::Print(const student_t &student) {

std::cout  << "| name        | group  | avg  | debt      |" << std::endl;
std::cout << "|---------------|--------|------|---------------|" << std::endl;


  if(std::any_cast<json>(student.GetName()).is_string()) {
    std::cout  <<"|"<< " " << std::any_cast<json>(student.GetName()).get<std::string>()<< "  "; // std::any_cast<json>(student.GetName())
  }



  if(std::any_cast<json>(student.GetGroup()).is_number()) {
    std::cout  <<"|" << " " << std::any_cast<json>(student.GetGroup()).get<int>()<< "  ";
  }else{
    std::cout  <<"|" << " " << std::any_cast<json>(student.GetGroup()).get<std::string>()<<std::setw(6);
  }
  std::cout  << "|" << " " << student.GetAvg() << std::setw(2);

  if(std::any_cast<json>(student.GetDebt()).is_null()) {
    std::cout  << "| " << "null" << std::setw(10) << std::endl;

  }else if (std::any_cast<json>(student.GetDebt()).is_number()) {
    std::cout  <<  std::any_cast<json>(student.GetDebt()).get<int>() << " items" << std::setw(9) << "|" << std::endl;

  }else{
    std::cout  << "| " << std::any_cast<json>(student.GetDebt()).get<std::string>() << std::setw(9) << std::endl;

  }

  std::cout  << "|---------------|--------|------|---------------|" << std::endl;

}


void Parser::PrintStudents() {

  for (const auto &student : students) {
    Print(student);
  }

}




