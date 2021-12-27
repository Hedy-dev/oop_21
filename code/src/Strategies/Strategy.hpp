#pragma once

enum StrategyEnum : unsigned short {
  FLEE,
  PASSIVE,
  ATTACK
};

class Strategy 
{
public:
  ///@brief Функция принятия решения стратегией. Обращения к данной функции вызавет запуск одной из функций, определяющей поведение врага.
  virtual Direction makeDecision(Point enemy, Point player) = 0;

  StrategyEnum getStrategyEnum();
  void setStrategyEnum(StrategyEnum _strategyEnum);

private:
  StrategyEnum _strategyEnum;
};
