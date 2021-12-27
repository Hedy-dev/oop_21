#pragma once

#include "Strategy.hpp"

class Attack : public Strategy
{
public:
  Attack();

  ///@brief Сближение врага с игроком.
  Direction makeDecision(Point enemy, Point player) override;
};
