#pragma once

#include "Cell.hpp"

#include "CellContent.hpp"

class IEnemy : public CellContent
{
public:
  IEnemy() { }
  virtual ~IEnemy() { }

  virtual unsigned short attack() = 0;
  virtual unsigned short dealDamage(unsigned short playerDamage) = 0;
};
