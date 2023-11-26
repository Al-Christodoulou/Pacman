#pragma once
#include <vector>
#include <memory>
#include "Entity.h"

using SharedEntityPtr = std::shared_ptr<Entity>;
using EntityArray = std::vector<SharedEntityPtr>;
using EntityArrayIterator = EntityArray::iterator;
using ConstEntityArrayIterator = EntityArray::const_iterator;