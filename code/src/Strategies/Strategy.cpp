#include "../pch.hpp"

#include "Strategy.hpp"

StrategyEnum Strategy::getStrategyEnum()
{
  return _strategyEnum;
}

void Strategy::setStrategyEnum(StrategyEnum strategyEnum)
{
  _strategyEnum = strategyEnum;
}
