#pragma once

#include "Cell.hpp"

#include "CellContent.hpp"

class IItem : public CellContent
{
public:
  IItem() { }
  virtual ~IItem() { }
  /// @brief Вывод характеристик предмета
 
  virtual void itemSpecialProperty() = 0;
};
