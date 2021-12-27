#pragma once

#include "Cell.hpp"

#include "CellContent.hpp"
#include "Logger/LogPublisher.hpp"
#include "Logger/Logger.hpp"

enum class PlayerParameter
{
  HEALTH,
  ATTACK,
  DEFENCE
};

class Player : public CellContent, public LogPublisher
{
public:
  Player();
  ~Player();
  
  /// @brief Изменение здоровья игрока после получения урона врага damage.
  unsigned short dealDamage(unsigned short damage);
  /// @brief Увеличение здоровья health игрока после подбора предметов.
  unsigned short healthUp(unsigned short healthUp);
  /// @brief Увеличение защиты defense игрока после подбора предметов.
  unsigned short defenseUp(unsigned short defenseUp);
  /// @brief Увеличение атаки attack игрока после подбора предметов.
  unsigned short attackUp(unsigned short attackUp);

  unsigned short health = 100;
  unsigned short attack = 20;
  unsigned short defense = 0;

  void serialize(std::ofstream& ofs) override;
  void deserialize(std::ifstream& ifs) override;

private:
/// @brief Изменение характеристик игрока после подбора предметов.
  unsigned short changeParameters(unsigned short parameter, unsigned short change,
  PlayerParameter playerParameter);
};