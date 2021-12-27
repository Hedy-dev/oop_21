#include "../pch.hpp"

#include "Passive.hpp"

Passive::Passive()
{
  setStrategyEnum(StrategyEnum::PASSIVE);
}

Direction Passive::makeDecision(Point enemy, Point player)
{
  return Direction::NONE;
}
