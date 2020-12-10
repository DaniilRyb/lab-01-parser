# Лабораторная работа № 1

### Задание
### Реализовать утилиту табличного вывода массива данных, хранящихся в файле формата JSON.
#### Некоторый пример кода
```cpp
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
} ```
```

```cpp
## Класс student_t
// Copyright 2020 <pochtaworld7@gmail.com>

#ifndef INCLUDE_STUDENT_HPP_
#define INCLUDE_STUDENT_HPP_

#include <any>
#include <exception>
#include <string>
#include <iostream>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class student_t {
 private:
  std::string name;
  std::any group;
  double avg;
  std::any debt;
 public:
  student_t();
  explicit student_t(const json& j);
  std::string GetName() const;
  std::any GetGroup() const;
  double GetAvg() const;
  std::any GetDebt() const;
};
#endif  // INCLUDE_STUDENT_HPP_
```
