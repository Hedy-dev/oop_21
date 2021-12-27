#include "../pch.hpp"

#include "Flee.hpp"

Flee::Flee()
{
  setStrategyEnum(StrategyEnum::FLEE);
}

Direction Flee::makeDecision(Point enemy, Point player)
{
  return Direction::DOWN;
}
