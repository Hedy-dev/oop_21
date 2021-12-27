#include "../pch.hpp"
#include "CollectedItemRequirement.hpp"
CollectedItemRequirement::CollectedItemRequirement(short itemCount)
{
  _itemCount = itemCount;
}
short CollectedItemRequirement::descriptionCollectedItemRequirement()
{
  return _itemCount;
};