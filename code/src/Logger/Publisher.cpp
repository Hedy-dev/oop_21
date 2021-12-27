#include "../pch.hpp"

#include "Publisher.hpp"

void Publisher::publish(const std::string& message)
{
  if (subscribers.size() > 0) {
    for (auto const& i : subscribers) {
      i->onPublish(message);
    }
  } 
}
