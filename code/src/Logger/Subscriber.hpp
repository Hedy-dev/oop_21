#pragma once

#include "Publisher.hpp"

class Publisher;

class Subscriber
{
public:
  void subscribe(Publisher* publisher);
  void unsubscribe(Publisher* publisher);
  
protected:
  virtual void onPublish(const std::string& message) = 0;
  
  std::list<Publisher*> publishers;

  friend class Publisher;
};