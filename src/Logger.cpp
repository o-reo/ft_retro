#include "Logger.hpp"

Logger *Logger::instance = nullptr;
size_t Logger::linecount = 0;

Logger::Logger() {
  this->file.open("game.log");
  if (!this->file.is_open()) {
    std::cout << "Could not initialize the logger" << std::endl;
  }
}

Logger::~Logger() {}

const std::string Logger::timestamp(void) {
  std::ostringstream ost;
  std::time_t t = std::time(0);
  std::tm *now = std::localtime(&t);
  ost << "[" << (now->tm_year + 1900) << (now->tm_mon + 1) << now->tm_mday << "_" << now->tm_hour << now->tm_min
      << now->tm_sec << "] ";
  return ost.str();
}

void Logger::log(std::string const &message) {
  this->file << this->timestamp() << message;
  Logger::linecount++;
}

Logger *Logger::get() {
  if (!Logger::instance) {
    Logger::instance = new Logger();
  }
  return Logger::instance;
}

std::ofstream &Logger::out() {
  this->file << this->timestamp();
  return (this->file);
}