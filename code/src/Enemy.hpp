#pragma once

#include "IEnemy.hpp"
#include "Strategies/Strategy.hpp"
#include "Strategies/Flee.hpp"
#include "Strategies/Attack.hpp"
#include "Strategies/Passive.hpp"
#include "Logger/LogPublisher.hpp"
#include "Logger/Logger.hpp"

class Enemy : public IEnemy, public LogPublisher
{
public:
  Enemy(std::shared_ptr<Strategy> strategy = std::make_shared<Flee>()); //поменять

  virtual ~Enemy() { }
  /// @brief Возврат урона врага damage.
  virtual unsigned short attack() override;
  /// @brief Рассчет нового значения health.
  virtual unsigned short dealDamage(unsigned short playerDamage) override;

  unsigned short damage;
  unsigned short health;

  std::shared_ptr<Strategy> getStrategy();
  void setStrategy(std::shared_ptr<Strategy> strategy);

  std::shared_ptr<Strategy> _strategy;

  Direction makeDecision(Point enemy, Point player);

  void serialize(std::ofstream& ofs) override;
  void deserialize(std::ifstream& ifs) override;
};
