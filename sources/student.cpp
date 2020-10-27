#include "../include/student.hpp"

student_t::student_t() {}

student_t::student_t(const json &j) {
  if (j.empty()){
    throw std::invalid_argument("Object student is empty");
  }
  name = j.at("name").get<std::string>();
  group = std::any{j.at("group")};
  if (j.at("avg").is_string()) {
    avg = std::stod(j.at("avg").get<std::string>());
  } else if (j.at("avg").is_number()) {
    avg = j.at("avg").get<double>();
  }else{
    throw std::invalid_argument("Avg cannot be another type!");
  }
  debt = std::any{j.at("debt")};
}

std::any student_t::GetGroup() {
  return group;
}

std::string student_t::GetName() {
  return name;
}

double student_t::GetAvg()  {
  return avg;
}

std::any student_t::GetDebt()  {
  return debt;
}
