#pragma once

#include "Game.hpp"
#include "FieldBuilder.hpp"
#include "Cell.hpp"
#include "VictoryCondition/VictoryCondition.hpp"

class FieldBuilder;
class Game;

class Field
{
public:
  Field(Game* parent, unsigned short width, unsigned short length);
  Field(const Field& other);
  Field(Field&& other);
  Field& operator=(const Field& other);
  Field& operator=(Field&& other);
  ~Field();

  /// @brief Возвращает параметр клетки width.
  unsigned short getWidth();
  /// @brief Возвращает параметр клетки heigth.
  unsigned short getHeigth();

  /// @brief Возвращают клетку с указанными параметрами.
  Cell getCell(unsigned short width, unsigned short heigth);

  /// @brief Устанавливает параметры клетки.
  /// @param[in] width Кордината клетки по оси абсцисс.
  /// @param[in] heigth Кордината клетки по оси ординат.
  /// @param[in] entity Определяет, что находится в клетке.
  /// @param[in] special Определяет, является ли клетка входом, выходом или ни тем, ни другим.
  /// @return true если клетка существует, false если нет.
  
  template<class T> 
  bool setCellContent(unsigned short width, unsigned short heigth, std::shared_ptr<T> cellContent)
  {
    field_contents[width][heigth].setCellContent(cellContent);
    return true;
  }

  /// @brief Вывод поля на экран.
  void printField();

  void serialize(std::ofstream& ofs);
  void serializeCell(Cell& cell, std::ofstream& ofs);
  void deserialize(std::ifstream& ifs);
  std::shared_ptr<CellContent> deserializeCell(std::ifstream& ifs);

private:
  Point entry;
  Point exit;
  /// @brief Ширина поля.
  unsigned short _width = 0;
  /// @brief Длина поля.
  unsigned short _heigth = 0;

  unsigned short _widthMaxIndex = 0;
  unsigned short _heigthMaxIndex = 0;

  /// @brief Указатель на указатель для хранения клеток поля.
  Cell** field_contents = nullptr;

  void buildField();
 
  /// @brief Проверка параметров клетки.
  bool newCellParametersIsValid(Entity entity, Special special);
  /// @brief Удаление клеток поля.
  void deleteFieldCells();
  /// @brief Копирование параметров клетки.
  void copyStackValues(Field* destination, const Field& source);

  std::unique_ptr<FieldBuilder> fieldBuilder;

  Game* parent;
  
  friend class FieldBuilder;
  friend class Game;
};
