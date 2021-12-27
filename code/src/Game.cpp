#include "pch.hpp"

#include "Game.hpp"
class Logger;
Game::Game(unsigned short width, unsigned short length, VictoryCondition<ExitCellReachRequirement, EnemiesKilledRequirement, CollectedItemRequirement>* game)
{
  field = std::make_shared<Field>(this, width, length);
  // field->setCellContent<Enemy>(1, 1, std::make_shared<Ghost>());
  // Point enemyCoordinates;
  // enemyCoordinates.x = 1;
  // enemyCoordinates.y = 1;
  // enemyPosotions.push_back(enemyCoordinates);
  // field->setCellContent<Enemy>(2, 2, std::make_shared<Demon>());
  // field->setCellContent<Enemy>(3, 2, std::make_shared<Killer>());
  // field->setCellContent<Item>(1, 0, std::make_shared<AttackItem>());
  field->setCellContent(field->entry.x, field->entry.y, std::make_shared<Player>());
  playerCoordinates.x = field->entry.x;
  playerCoordinates.y = field->entry.y;
  victoryCondition = std::shared_ptr<VictoryCondition<ExitCellReachRequirement, EnemiesKilledRequirement, CollectedItemRequirement>>(game);
  Logger::getInstance().subscribe(this);
}

bool Game::fight(unsigned short width, unsigned short heigth)
{
  Cell *playerCell = &field->field_contents[playerCoordinates.x][playerCoordinates.y];
  Cell *enemyCell = &field->field_contents[width][heigth];

  std::shared_ptr<Player> player = playerCell->getCellContent<Player>();
  std::shared_ptr<Enemy> enemy = enemyCell->getCellContent<Enemy>();

  if (!(player->dealDamage(enemy->attack())))
  {
    field->field_contents[playerCoordinates.x][playerCoordinates.y].setCellContent(std::make_shared<Traversable>());
    std::cout << "Restart game" << std::endl;
    exit(0);
  }

  if (!(enemy->dealDamage(player->attack)))
  {
    field->field_contents[width][heigth].setCellContent(std::make_shared<Traversable>());
    for (short i = 0; i < enemyPosotions.size(); i++) {
      if ((enemyPosotions[i].x == width) && (enemyPosotions[i].y == heigth))
      {
        enemyPosotions.erase(enemyPosotions.begin() + i);
      }
    }
    startTurn();
    return true;
  }

  return false;
}

Game::~Game() {}

void Game::itemProperty(unsigned short width, unsigned short heigth)
{
  Cell *playerCell = &field->field_contents[playerCoordinates.x][playerCoordinates.y];
  Cell *itemCell = &field->field_contents[width][heigth];

  std::shared_ptr<Player> player = playerCell->getCellContent<Player>();
  std::shared_ptr<Item> item = itemCell->getCellContent<Item>();

  player->healthUp(item->healthBonus);
  player->defenseUp(item->defenseBonus);
  player->attackUp(item->attackBonus);
}

bool Game::correctInteractPlayerWithCell(unsigned short width, unsigned short heigth)
{
  if (field->field_contents[width][heigth].getCellContentType() == Entity::TRAVERSABLE)
  {
    return true;
  }

  if (field->field_contents[width][heigth].getCellContentType() == Entity::NON_TRAVERSABLE)
  {
    std::cout << "NON TRAVERSABLE" << std::endl;
    return false;
  }

  if (field->field_contents[width][heigth].getCellContentType() == Entity::ENEMY)
  {
    std::cout << "You have been damaged" << std::endl;
    if (fight(width, heigth))
    {
      playerInteractionWithEnemy += 1;
      return true;
    }

    return false;
  }

  if (field->field_contents[width][heigth].getCellContentType() == Entity::ITEM)
  {
    itemProperty(width, heigth);
    field->field_contents[width][heigth].getCellContent<Item>()->itemSpecialProperty();
    playerInteractionWithItem += 1;
    return true;
  }

  return false;
}

bool Game::checkPlayerDirection(short width, short heigth)
{
  if ((width > field->_widthMaxIndex) || (width < 0) || (heigth > field->_heigthMaxIndex) || (heigth < 0))
  {
    return false;
  }

  if ((width == field->exit.x) && (heigth == field->exit.y))
  {
    auto test1 = victoryCondition->getRule2();
    auto test2 = victoryCondition->getRule3();
    if ((victoryCondition->getRule2() <= playerInteractionWithEnemy) && (victoryCondition->getRule3() <= playerInteractionWithItem)) {
      std::cout << "You Win!" << std::endl;
      exit(0);
    } else {
      std::cout << "Conditions are not met!" << std::endl;
      std::cout << "Enemy interaction: " << playerInteractionWithEnemy << std::endl;
      std::cout << "Item interaction: " << playerInteractionWithItem << std::endl;
      exit(0);
    }
  }

  if (!(correctInteractPlayerWithCell(width, heigth)))
  {
    return false;
  }

  movePlayerCell(playerCoordinates.x, playerCoordinates.y, width, heigth);
  
  return true;
}

bool Game::movePlayer(Direction direction)
{
  if (direction == Direction::DOWN)
  {
    if (checkPlayerDirection(playerCoordinates.x, playerCoordinates.y + 1))
    {
      playerCoordinates.y += 1;
    }
  }
  else if (direction == Direction::UP)
  {
    if (checkPlayerDirection(playerCoordinates.x, static_cast<short>(playerCoordinates.y - 1)))
    {
      playerCoordinates.y -= 1;
    }
  }
  else if (direction == Direction::LEFT)
  {
    if (checkPlayerDirection(static_cast<short>(playerCoordinates.x - 1), playerCoordinates.y))
    {
      playerCoordinates.x -= 1;
    }
  }
  else if (direction == Direction::RIGHT)
  {
    if (checkPlayerDirection(playerCoordinates.x + 1, playerCoordinates.y))
    {
      playerCoordinates.x += 1;
    }
  }
  
  startTurn();
  field->printField();
  return true;
}

bool Game::interactEnemyWithCell(unsigned short width, unsigned short heigth, Point enemyPosition)
{
  if (field->field_contents[width][heigth].getCellContentType() == Entity::TRAVERSABLE)
  {
    return true;
  } 
  else if (field->field_contents[width][heigth].getCellContentType() == Entity::PLAYER)
  {
    fight(enemyPosition.x, enemyPosition.y);
    return false;
  }
  else
  {
    std::cout << "Non traversable for enemy" << std::endl;
    return false;
  }
}

bool Game::checkEnemyDirection(Point enemyPosition, Point desiredPosition)
{
  if ((desiredPosition.x > field->_widthMaxIndex) || (desiredPosition.x < 0) || (desiredPosition.y > field->_heigthMaxIndex) || (desiredPosition.y < 0))
  {
    return false;
  }

  if ((interactEnemyWithCell(desiredPosition.x, desiredPosition.y, enemyPosition)) == false)
  {
    return false;
  }

  moveEnemyCell(enemyPosition.x, enemyPosition.y, desiredPosition.x, desiredPosition.y);
  return true;
}

void Game::moveEnemy(Point enemyPosition)
{
  auto direction = field->field_contents[enemyPosition.x][enemyPosition.y].getCellContent<Enemy>()->makeDecision(enemyPosition, playerCoordinates);

  Point desiredPosition = enemyPosition;
  if (direction == Direction::DOWN)
  {
    desiredPosition.y += 1;
  }
  else if (direction == Direction::UP)
  {
    // if (desiredPosition.y - 1 < 0) {
    //   std::cout << "Cannot move to this coordinates" << std::endl;
    //   return;
    // } // Тогда нужно будет сделать Point unsigned short.
    desiredPosition.y -= 1;
  }
  else if (direction == Direction::LEFT)
  {
    desiredPosition.x -= 1;
  }
  else if (direction == Direction::RIGHT)
  {
    desiredPosition.x += 1;
  }

  if (direction == Direction::DOWN)
  {
    if (checkEnemyDirection(enemyPosition, desiredPosition) == false)
    {
      desiredPosition = enemyPosition;
    }
  }
  else if (direction == Direction::UP)
  {
    if (checkEnemyDirection(enemyPosition, desiredPosition)) {

    }
  }
  else if (direction == Direction::LEFT)
  {
    if (checkEnemyDirection(enemyPosition, desiredPosition)) {

    }
  }
  else if (direction == Direction::RIGHT)
  {
    if (checkEnemyDirection(enemyPosition, desiredPosition)) {
      
    }
  }
  
  for (short i = 0; i < enemyPosotions.size(); i++) {
    if ((enemyPosotions[i].x == enemyPosition.x) && (enemyPosotions[i].y == enemyPosition.y)) {
      enemyPosotions[i] = desiredPosition;
    }
  }
  // desiredPosition = новый
  // enemyPosition = старый
}

void Game::startTurn()
{
  for (short i = 0; i < enemyPosotions.size(); i++) {
    moveEnemy(enemyPosotions[i]);
  }
}

void Game::movePlayerCell(short currentX, short currentY, short desiredX, short desiredY)
{
  auto cellContent = field->field_contents[currentX][currentY].getCellContent<Player>();
  field->field_contents[desiredX][desiredY].setCellContent(cellContent);
  field->field_contents[currentX][currentY].setCellContent(std::make_shared<Traversable>());
}

void Game::moveEnemyCell(short currentX, short currentY, short desiredX, short desiredY)
{
  auto cellContent = field->field_contents[currentX][currentY].getCellContent<Enemy>();
  field->field_contents[desiredX][desiredY].setCellContent(cellContent);
  field->field_contents[currentX][currentY].setCellContent(std::make_shared<Traversable>());
}

void Game::serialize(const std::string& fileName)
{
  field->printField();

  // std::filesystem::remove(fileName);
  std::ofstream ofs(fileName, std::ios::binary);

  ofs << saveFilesVersion << std::endl;

  ofs << playerInteractionWithItem << std::endl;
  ofs << playerInteractionWithEnemy << std::endl;

  ofs << playerCoordinates.x << std::endl;
  ofs << playerCoordinates.y << std::endl;
  
  ofs << enemyPosotions.size() << std::endl;
  for (unsigned i = 0; i < enemyPosotions.size(); ++i) {
    ofs << enemyPosotions[i].x << std::endl;
    ofs << enemyPosotions[i].y << std::endl;
  }

  field->serialize(ofs);

  ofs.close();
}

void Game::deserialize(const std::string& fileName)
{
  std::ifstream ifs(fileName, std::ios::binary);

  std::string currentSaveFileVerion;
  ifs >> currentSaveFileVerion;
  if (currentSaveFileVerion != saveFilesVersion) {
    throw LoadException("Save file verison is not correct");
  }

  ifs >> this->playerInteractionWithItem;
  ifs >> this->playerInteractionWithEnemy;

  ifs >> playerCoordinates.x;
  ifs >> playerCoordinates.y;

  enemyPosotions.clear();
  unsigned enemyPositionsSize;
  ifs >> enemyPositionsSize;
  Point buffer;
  for (unsigned i = 0; i < enemyPositionsSize; ++i) {
    ifs >> buffer.x;
    ifs >> buffer.y;
    enemyPosotions.push_back(buffer);
  }

  field->deserialize(ifs);

  ifs.close();

  std::cout << "DESERIALIZED FIELD" << std::endl;
  field->printField();
}

// TODO: 1. Функции для классов "ниже" должны принмать ссылку на уже открытый поток (ofs/ifs).
// 2. Для каждого класса "ниже" реализовать функции сериализации/десериализации.