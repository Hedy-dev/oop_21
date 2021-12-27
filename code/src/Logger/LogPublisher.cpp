#include "../pch.hpp"

#include "LogPublisher.hpp"

LocalLogger* LocalLogger::operator<<(const std::string& message) 
{
  std::stringstream typeAmendedMessage;
  if (logType == Log::Type::GENERAL) {
    typeAmendedMessage << "GENERAL: " << message;
  } else if (logType == Log::Type::BATTLE) {
    typeAmendedMessage << "BATTLE: " << message;
  } else if (logType == Log::Type::MOVEMENT) {
    typeAmendedMessage << "MOVEMENT: " << message;
  } else {
    typeAmendedMessage << "UNKNOWN: " << message;
  }

  parent->publish(typeAmendedMessage.str());
  return this;
}
