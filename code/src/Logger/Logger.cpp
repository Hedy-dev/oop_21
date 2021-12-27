#include "../pch.hpp"

#include "Logger.hpp"

Logger::Logger()
{
  oLogStream.open(logFileName);
}

Logger::~Logger() 
{
  oLogStream.close();
}

Logger& Logger::getInstance()
{
  static Logger* inst = new Logger;
  return *inst;
}

void Logger::onPublish(const std::string& message)
{
  if (consoleOutput == true) {
    std::clog << message << std::endl;
  }

  if (fileOutput == true && oLogStream.is_open()) {
    oLogStream << message << std::endl;
  }
}

void Logger::setConsoleOutput(bool newCondition)
{
  consoleOutput = newCondition;
}
void Logger::setFileOutput(bool newCondition)
{
  fileOutput = newCondition;
}
