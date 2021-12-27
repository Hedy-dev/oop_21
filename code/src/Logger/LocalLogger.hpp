#pragma once

#include "Publisher.hpp"

// Класс, "сидящий" в каждом классе, что умеет писать в лог. Именно вызывая 
// его классы отправляют сообщения в логгер.
class LocalLogger
{
public:
  LocalLogger(Publisher* parent) : parent(parent) { };
  ~LocalLogger() { };

  LocalLogger* operator<<(const std::string& message);

  Log::Type getLogType();
  void setLogType(Log::Type logType);

protected:
  Log::Type logType = Log::Type::GENERAL;
  Publisher* parent;
};