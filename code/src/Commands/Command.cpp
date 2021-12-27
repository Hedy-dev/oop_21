#include "../pch.hpp"
#include "Command.hpp"

Command::Command(CommandType commandType)
{ 
  _commandType = commandType;
}

CommandType Command::getCommandType()
{
  return _commandType;
}

Command::~Command() {}