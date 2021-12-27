#include "../pch.hpp"

#include "Attack.hpp"

Attack::Attack()
{
  setStrategyEnum(StrategyEnum::ATTACK);
}

Direction Attack::makeDecision(Point enemy, Point player)
{
  return Direction::UP;
}