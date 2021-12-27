#pragma once

#include "ActionProcesser.hpp"
#include "Command.hpp"

struct Keys
{
  char ESC;
  char UP;
  char DOWN;
  char LEFT;
  char RIGHT;
  char RECORD; 
  char SAVE;
  char LOAD;
  char NEW_GAME;
};

class ActionProcesser;
class ActionManager
{
private:
  std::shared_ptr<ActionProcesser> actionProcesser;
  std::shared_ptr<Game> game = nullptr;
  
  bool isRecording = false;
  void addToQueue(std::shared_ptr<Command> command);
  void getKeysMap();
  void getKeyShortcut(const std::string& hint, char& keyForRecord);

  std::list<std::shared_ptr<Command>> commandQueue;

  Keys keys;
public:
  ActionManager();
  void mainLoop();

  ~ActionManager();
};


