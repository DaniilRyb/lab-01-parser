//
// Copyright 2020 Daniil Rybakov <pochtaworld7@gmail.com>
//
#include "student.hpp"

student_t::student_t() {}
student_t::student_t(const json &js) {
  if (js.empty()){
    throw std::invalid_argument("Object student is empty");
  }
  name = js.at("name").get<std::string>();
  group = std::any{js.at("group")};

  if (js.at("avg").is_string()) {
    avg = std::stod(js.at("avg").get<std::string>());
  } else if (js.at("avg").is_number()) {
    avg = js.at("avg").get<double>();
  }else{
    throw std::invalid_argument("Avg cannot be another type!");
  }
  debt = std::any{js.at("debt")};
}
std::any student_t::GetGroup() const { return group; }
std::string student_t::GetName() const { return name; }
double student_t::GetAvg() const { return avg; }
std::any student_t::GetDebt() const { return debt; }
