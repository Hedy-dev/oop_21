#pragma once

class CellContent 
{
public:
  CellContent();
  ~CellContent();

  virtual Entity getContentType();
  /// @brief По умолчанию клетка является Traversable.
  virtual void setContentType(Entity cellContentType);

  virtual void serialize(std::ofstream& ofs);
  virtual void deserialize(std::ifstream& ifs);

protected:
  Entity _cellContentType = Entity::TRAVERSABLE;

  friend class Cell;
};