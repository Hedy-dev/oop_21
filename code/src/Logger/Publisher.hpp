#pragma once

#include "Subscriber.hpp"

class Subscriber;
class Publisher;

class Publisher
{
public:
  void publish(const std::string& message);
  
protected:
  std::list<Subscriber*> subscribers;

  friend class Subscriber;
};