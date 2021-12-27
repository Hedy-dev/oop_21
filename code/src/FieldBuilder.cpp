#include "pch.hpp"

#include "FieldBuilder.hpp"

FieldBuilder::FieldBuilder(Field* parent) : parent(parent) { }

FieldBuilder::~FieldBuilder() { }

void FieldBuilder::createFieldCells()
{
  parent->field_contents = new Cell*[parent->_width]; 
  for (unsigned i = 0; i < parent->_width; ++i) {
    parent->field_contents[i] = new Cell[parent->_heigth];
  }
}

void FieldBuilder::createEnteranceAndExit()
{
  parent->entry.x = 0;
  parent->entry.y = 0;
  parent->exit.x = parent->_widthMaxIndex;
  parent->exit.y = parent->_heigthMaxIndex;
}
void FieldBuilder::initializeField()
{
  createFieldCells();
  createEnteranceAndExit();
  fillTheField();
}

void FieldBuilder::fillTheField()
{
  fillType<NonTraversable, NonTraversable>(nonTraversableCellCount);
  fillType<Enemy, Ghost>(countEnemyCell / 4);
  fillType<Enemy, Killer>(countEnemyCell / 4);
  fillType<Enemy, Demon>(countEnemyCell / 4);
  fillType<Item, AttackItem>(countItemCell / 2);
  fillType<Item, HealthItem>(countItemCell / 2);
  fillType<Item, DefenseItem>(countItemCell / 2);
}

/// @TODO: Исправить это убожество
template <class T1, class T2>
void FieldBuilder::fillType(unsigned short countSpecialCell)
{
  Point enemyCoordinates;
  unsigned short widthRand;
  unsigned short heightRand;
  for (unsigned short i = 0; i < countSpecialCell; i++) {
    widthRand = rand() % parent->_widthMaxIndex;
    heightRand = rand() % parent->_heigthMaxIndex;
    //auto test1 = parent->getCell(widthRand, heightRand).getCellContentType();
    if (parent->getCell(widthRand, heightRand).getCellContentType() == Entity::TRAVERSABLE)
    {
      parent->setCellContent<T1>(widthRand, heightRand, std::make_shared<T2>());
      if (std::is_same<T1, Enemy>::value == true) {
      enemyCoordinates.x = widthRand;
      enemyCoordinates.y = heightRand;
      parent->parent->enemyPosotions.push_back(enemyCoordinates);
      }
    }
  
  }
  
}
