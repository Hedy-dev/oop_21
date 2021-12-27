#pragma once

#include "Strategy.hpp"

class Passive : public Strategy
{
public:
  Passive();

  ///@brief Враг остается на месте.
  Direction makeDecision(Point enemy, Point player) override;
};
