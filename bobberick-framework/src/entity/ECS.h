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

constexpr std::size_t maxComponents = 64;
constexpr std::size_t maxGroups = 64;
using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;
using GroupSet = std::vector<int>;
using Group = std::string;

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

#endif //BOBBERICK_TOOLS_ECS_H
