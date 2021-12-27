#include "pch.hpp"
#include "Commands/ActionManager.hpp"
#include "Game.hpp"
#include "Logger/Logger.hpp"
#include "VictoryCondition/VictoryCondition.hpp"

int gameMenu()
{
  // ExitCellReachRequirement rule1(true);
  // EnemiesKilledRequirement rule2(0);
  // CollectedItemRequirement rule3(0);
  
  // VictoryCondition<ExitCellReachRequirement, EnemiesKilledRequirement, CollectedItemRequirement> game1(rule1,rule2,rule3);
  // Game game(4, 5, &game1);
  // game.field->printField();

  ActionManager actionManager;
  // actionManager.mainLoop();

  return 0;
}

int main()
{
  // srand(time(nullptr));
  gameMenu();

  return 0;
}

/// TODO: (optional): Отдельную папку для классов врагов.
/// TODO: (optional): Отдельную папку для классов вещей.

/// TODO: Реализовать cellInteract
/// TODO: Реализовать наследование Player и Enemy от нового класса Character.
/// TODO: В коде много повторяющегося dealDamage
/// TODO: Определить шаблон поведения врагов
/// TODO: Вынесение общих характеристик врагов?
/// TODO: Реализовать метод перемещение врага, логику хода. Написать пример, в котором класс Игра будет перемещать врагов. Создать базовый класс стратегия, отнаследовать от него flee и attack. Добавить в класс врагов метод установки стратегии. После хода игрока вызывать метод makemove. Враг с классом attack пытается приблизиться к игроку, враг должен знать текущее местоположение игрока и свое.
/// TODO: Распаковка параметров, метод check