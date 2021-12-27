#pragma once

#include "Ghost.hpp"
#include "Killer.hpp"
#include "Demon.hpp"
#include "AttackItem.hpp"
#include "HealthItem.hpp"
#include "DefenseItem.hpp"
#include "Field.hpp"
#include "Cell.hpp"
#include "CellContent.hpp"
#include "Logger/Publisher.hpp"
#include "Logger/Logger.hpp"
#include "VictoryCondition/VictoryCondition.hpp"
#include "LoadException.hpp"

class Field;
class Cell;
class CellContent;

class Game : public Publisher
{
public:
  Game(unsigned short width, unsigned short heigth, 
    VictoryCondition<ExitCellReachRequirement, EnemiesKilledRequirement, CollectedItemRequirement>* victoryCondition);
  Game(const Game& other) = delete;
  Game(Game&& other) = delete;
  Game& operator=(const Game& other) = delete;
  Game& operator=(Game&& other) = delete;
  ~Game();

  short playerInteractionWithItem = 0;
  short playerInteractionWithEnemy = 0;

  std::shared_ptr<Field> field;
  std::shared_ptr<VictoryCondition <ExitCellReachRequirement,
    EnemiesKilledRequirement, CollectedItemRequirement>> victoryCondition;

  /// @brief Взаимодействие с предметом.
  void itemProperty(unsigned short width, unsigned short heigth);
  /// @brief Взаимодействие с врагом.
  bool fight(unsigned short width, unsigned short heigth);
  /// @brief Движение игрока.
  bool movePlayer(Direction direction);
  /// @brief Проверка клетки перехода.
  bool checkPlayerDirection(short width, short heigth);
  /// @brief Проверка корректности положения желаемой клетки на поле.
  bool correctInteractPlayerWithCell(unsigned short width, unsigned short heigth);
  /// @brief Координаты игрока на поле.
  Point playerCoordinates;

  bool checkEnemyDirection(Point enemyPosition, Point desiredPoint);
  void moveEnemy(Point enemyPosition);

  void movePlayerCell(short currentX, short currentY, short desiredX, short desiredY);

  void moveEnemyCell(short currentX, short currentY, short desiredX, short desiredY);

  bool interactEnemyWithCell(unsigned short width, unsigned short heigth, Point enemyPosition);

  std::vector<Point> enemyPosotions;

  void serialize(const std::string& fileName);
  void deserialize(const std::string& fileName);
  
private:
  void startTurn();

  const std::string saveFilesVersion = "GameSaveFile_ver._1.0";
};
