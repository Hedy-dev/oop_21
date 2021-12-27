#pragma once

#include "../Game.hpp"
#include "Command.hpp"
#include "../LoadException.hpp"

class ActionProcesser
{
public:
  ActionProcesser(std::shared_ptr<Game> game);
  ~ActionProcesser();
  
  std::shared_ptr<Game> game;
    
  std::list<std::shared_ptr<Command>> commands;
  void processCommand(std::shared_ptr<Command> command);

private:
  std::shared_ptr<Game> createGame();
};
