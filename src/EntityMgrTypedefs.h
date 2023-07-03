#pragma once
#include <vector>
#include <memory>
#include "Entity.h"

using EntityArray = std::vector<std::unique_ptr<Entity>>;
using EntityArrayIterator = EntityArray::iterator;
using ConstEntityArrayIterator = EntityArray::const_iterator;