#include "../pch.hpp"

#include "LocalLogger.hpp"

Log::Type LocalLogger::getLogType()
{
  return logType;
}

void LocalLogger::setLogType(Log::Type logType)
{
  this->logType = logType;
}