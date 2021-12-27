#include "../pch.hpp"
#include "ActionProcesser.hpp"

ActionProcesser::ActionProcesser(std::shared_ptr<Game> game) : game(game) { }

ActionProcesser::~ActionProcesser() { }

void ActionProcesser::processCommand(std::shared_ptr<Command> command) 
{
  if (command->getCommandType() == CommandType::ABORT)
  {
    exit(0);
  } else if (command->getCommandType() == CommandType::MOVEMENT) {
    MovementCommand& movementCommand = dynamic_cast<MovementCommand&>(*command);
    game->movePlayer(movementCommand.getDirection());
  } else if (command->getCommandType() == CommandType::SAVE) {
    std::cout << "Enter game save file name" << std::endl;
    std::string saveFileName;
    std::cin >> saveFileName;
    game->serialize(saveFileName);
  } else if (command->getCommandType() == CommandType::LOAD) {
    std::cout << "Enter game save file name" << std::endl;
    std::string saveFileName;
    std::cin >> saveFileName;
    auto tmpGame = createGame();

    try {
      tmpGame->deserialize(saveFileName);
    } catch (const LoadException& e) {
      std::cout << e.getErrString() << std::endl;
    }

    game = tmpGame;
  } else if (command->getCommandType() == CommandType::NEW_GAME) {
    game = createGame();
  }
}

std::shared_ptr<Game> ActionProcesser::createGame()
{
  std::shared_ptr<Game> result;

  ExitCellReachRequirement rule1(true);
  EnemiesKilledRequirement rule2(0);
  CollectedItemRequirement rule3(0);

  VictoryCondition<ExitCellReachRequirement, EnemiesKilledRequirement, 
    CollectedItemRequirement> victoryConditions(rule1, rule2, rule3);

  result = std::make_shared<Game>(4, 5, &victoryConditions);

  return result;
}
