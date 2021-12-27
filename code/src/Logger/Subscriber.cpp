#include "../pch.hpp"

#include "Subscriber.hpp"

void Subscriber::subscribe(Publisher* publisher)
{
  publishers.push_back(publisher);
  publisher->subscribers.push_back(this);
}

void Subscriber::unsubscribe(Publisher* publisher)
{
  unsigned currentPublisherIndex = 0;
  unsigned currentSubscriptionIndex = 0;

  publisher->subscribers.remove(this);
  publishers.remove(publisher);
}