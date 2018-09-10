#ifndef BOBBERICK_TOOLS_ECS_H
#define BOBBERICK_TOOLS_ECS_H

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include "Component.h"

using ComponentID = std::size_t;

inline ComponentID getComponentID()
{
    static ComponentID lastID = 0;

    return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
    static ComponentID typeID = getComponentID();

    return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

#endif //BOBBERICK_TOOLS_ECS_H
