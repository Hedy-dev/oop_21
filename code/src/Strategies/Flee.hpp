#pragma once

#include "Strategy.hpp"

class Flee : public Strategy
{
public:
  Flee();

  ///@brief Удаление от игрока.
  Direction makeDecision(Point enemy, Point player) override;
};