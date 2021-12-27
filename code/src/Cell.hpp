#pragma once 

#include "CellContent.hpp"
#include "Enemy.hpp"
#include "Item.hpp"
#include "Player.hpp"
#include "NonTraversable.hpp"
#include "Traversable.hpp"

class CellContent;
class Enemy;
class Item;
class Player;
class NonTraversable;
class Traversable;

class Cell
{
public:
  Cell();
  ~Cell();

  template <class T> // Шаблонный метод класса. 
  void setCellContent(std::shared_ptr<T> cellContent)
  {
    _cellContent = std::dynamic_pointer_cast<CellContent>(cellContent);
    if (std::is_same<T, Enemy>::value == true) {
      _cellContent->setContentType(Entity::ENEMY);
    } else if (std::is_same<T, Item>::value == true) {
      _cellContent->setContentType(Entity::ITEM);
    } else if (std::is_same<T, Player>::value == true) {
      _cellContent->setContentType(Entity::PLAYER);
    } else if (std::is_same<T, NonTraversable>::value == true) {
      _cellContent->setContentType(Entity::NON_TRAVERSABLE);
    } else if (std::is_same<T, Traversable>::value == true) {
      _cellContent->setContentType(Entity::TRAVERSABLE);
    }
  }
  
  template <class T> std::shared_ptr<T> getCellContent() 
  {
    return std::dynamic_pointer_cast<T>(_cellContent);
  }

  Entity getCellContentType();

private:
  std::shared_ptr<CellContent> _cellContent = std::make_shared<CellContent>();
};
