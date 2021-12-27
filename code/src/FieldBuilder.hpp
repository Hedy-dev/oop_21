#pragma once

#include "Field.hpp"
#include "NonTraversable.hpp"
#include "Ghost.hpp"
#include "Killer.hpp"
#include "Demon.hpp"
#include "AttackItem.hpp"
#include "HealthItem.hpp"
#include "DefenseItem.hpp"
#include "Traversable.hpp"

class Field;

class FieldBuilder
{
public:
  // Если использовать для this умный указатель - при (гипотетическом) удалении 
  // FieldBuilder будет освобождён оригинальный объект.
  FieldBuilder(Field* parent);
  ~FieldBuilder();
  /// @brief Создание клеток поля.
  void createFieldCells();
  /// @brief Запускает функции, подготавливающие поле к игре (createEnteranceAndExit() и fillTheField()).
  void initializeField();

private:
  unsigned short nonTraversableCellCount = 3;
  unsigned short countEnemyCell = 5;
  unsigned short countItemCell = 5;

  template <class T1, class T2>
  void fillType(unsigned short countSpecialCell);

  /// @brief Создаёт клетки выхода и входа на поле. Вход находится на координатах [0][0], 
  /// выход на координатах [width][heigth]. Устанавливает игрока в поле входа.
  void createEnteranceAndExit();
  /// @brief Заполняет поле случайными элементами. Для этого используются случайные числа.
  void fillTheField();

  Field* parent; //поле создается вне филдбилдера. филд - родитель, поэтому филдбилдер не отвечает за очищение памяти филда
};
