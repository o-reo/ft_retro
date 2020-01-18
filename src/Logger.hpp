#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Logger {
private:
  std::ofstream file;
  static Logger *instance;
  static size_t linecount;

  const std::string timestamp();
  Logger();
  Logger(Logger const &src);
  Logger &operator=(Logger const &src);

public:
  ~Logger();
  static Logger *get();
  std::ofstream &out();
  void log(std::string const &message);
};

#endif