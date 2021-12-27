#pragma once

enum class CommandType {
  MOVEMENT,
  ABORT,
  SAVE,
  LOAD,
  NEW_GAME
};

class Command
{
public:
  virtual CommandType getCommandType();
  Command(CommandType commandType);
  ~Command();

private:
  CommandType _commandType;
};

class MovementCommand : public Command
{
public:
  MovementCommand(Direction direction) : Command(CommandType::MOVEMENT), direction(direction) { }
  ~MovementCommand() { };

  Direction getDirection()
  {
    return direction;
  }

private:
  Direction direction;
};

class Save : public Command
{
public:
  Save() : Command(CommandType::SAVE) {}
  ~Save() {}
};

class Load : public Command
{
public:
  Load() : Command(CommandType::LOAD) {}
  ~Load() {}
};

class NewGame : public Command
{
public:
  NewGame() : Command(CommandType::NEW_GAME) {}
  ~NewGame() {}
};