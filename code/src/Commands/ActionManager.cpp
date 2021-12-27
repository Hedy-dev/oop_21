#include "../pch.hpp"
#include "../Game.hpp"

#include "ActionManager.hpp"

ActionManager::ActionManager() 
{
  actionProcesser = std::make_shared<ActionProcesser>(game);

  getKeysMap();
  mainLoop();       
}

void ActionManager::getKeysMap()
{
  getKeyShortcut("Enter ESC command", keys.ESC);
  getKeyShortcut("Enter UP command", keys.UP);
  getKeyShortcut("Enter DOWN command", keys.DOWN);
  getKeyShortcut("Enter LEFT command", keys.LEFT);
  getKeyShortcut("Enter RIGHT command", keys.RIGHT);
  getKeyShortcut("Enter RECORD command", keys.RECORD);
  getKeyShortcut("Enter SAVE command", keys.SAVE);
  getKeyShortcut("Enter LOAD command", keys.LOAD);
  getKeyShortcut("Enter NEW GAME command", keys.NEW_GAME);

  // std::cout << static_cast<short>(keys.ESC) << std::endl;
  // std::cout << static_cast<short>(keys.UP) << std::endl;
  // std::cout << static_cast<short>(keys.DOWN) << std::endl;
  // std::cout << static_cast<short>(keys.LEFT) << std::endl;
  // std::cout << static_cast<short>(keys.RIGHT) << std::endl;
  // std::cout << static_cast<short>(keys.RECORD) << std::endl;
  // std::cout << static_cast<short>(keys.SAVE) << std::endl;
  // std::cout << static_cast<short>(keys.LOAD) << std::endl;
  // std::cout << static_cast<short>(keys.NEW_GAME) << std::endl;

  // keys.ESC = 27;
  // keys.UP = -26;
  // keys.DOWN = -21;
  // keys.LEFT = -28;
  // keys.RIGHT = -94;
  // keys.RECORD = -86;
  // keys.SAVE = -89;
  // keys.LOAD = -23;
  // keys.NEW_GAME = -24;
}

void ActionManager::getKeyShortcut(const std::string& hint, char& keyForRecord)
{
  std::cout << hint << std::endl;
  keyForRecord = getch();
}

void ActionManager::addToQueue(std::shared_ptr<Command> command)
{
  commandQueue.push_back(command);
}

void ActionManager::mainLoop() 
{
  std::shared_ptr<Command> resultCommand;
  char selectedKey;

  while (true)
  {
    std::cout << "Enter your command" << std::endl;
    selectedKey = getch();
    if (selectedKey == keys.ESC){ 
      resultCommand = std::make_shared<Command>(CommandType::ABORT);
    } else if (selectedKey == keys.UP) {
      resultCommand = std::make_shared<MovementCommand>(Direction::UP);
    } else if (selectedKey == keys.DOWN) {
      resultCommand = std::make_shared<MovementCommand>(Direction::DOWN);
    } else if (selectedKey == keys.LEFT) {
      resultCommand = std::make_shared<MovementCommand>(Direction::LEFT);
    } else if (selectedKey == keys.RIGHT) {
      resultCommand = std::make_shared<MovementCommand>(Direction::RIGHT);
    } else if (selectedKey == keys.SAVE) {
      resultCommand = std::make_shared<Save>();
    } else if (selectedKey == keys.LOAD) {
      resultCommand = std::make_shared<Load>();
    } else if (selectedKey == keys.NEW_GAME) {
      resultCommand = std::make_shared<NewGame>();
    } else if (selectedKey == keys.RECORD) {
      isRecording = !isRecording;
      if (isRecording == true) {
        std::cout << "Recording started." << std::endl;
        continue;
      } else {
        std::cout << "Recording done." << std::endl;
      }
    } else {
      continue;
    }
  
    addToQueue(resultCommand);

    if (isRecording == false) { 
      for (auto& command : commandQueue) {
        actionProcesser->processCommand(command);
      }

      commandQueue.clear();
    }
  }
}

ActionManager::~ActionManager() { }
