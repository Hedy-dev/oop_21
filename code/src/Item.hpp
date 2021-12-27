#pragma once

#include "IItem.hpp"

#include "CellContent.hpp"
#include "Logger/LogPublisher.hpp"
#include "Logger/Logger.hpp"
class Item : public IItem, public LogPublisher
{
public:
  Item();
  virtual ~Item();
  /// @brief Вывод характеристик предмета.
  virtual void itemSpecialProperty() override;

  unsigned short attackBonus = 0;
  unsigned short defenseBonus = 0;
  unsigned short healthBonus = 0;

  void serialize(std::ofstream& ofs) override;
  void deserialize(std::ifstream& ifs) override;
};
