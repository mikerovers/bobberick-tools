#ifndef BOBBERICK_TOOLS_SERVICEMANAGER_H
#define BOBBERICK_TOOLS_SERVICEMANAGER_H


#include <vector>
#include <bitset>
#include <array>
#include "Service.h"

using ServiceID = std::size_t ;

inline ServiceID getServiceID()
{
    static ServiceID lastID = 0;

    return lastID++;
}

template <typename T> inline ServiceID getServiceTypeID() noexcept
{
    static ServiceID typeID = getServiceID();

    return typeID;
}

constexpr std::size_t maxServices = 32;

using ServiceBitSet = std::bitset<maxServices>;
using ServiceArray = std::array<Service*, maxServices>;

class ServiceManager
{
public:
    template <typename T> bool hasService() const
    {
        return serviceBitSet[getServiceTypeID<T>()];
    }

    template <typename T, typename ... TArgs> T& addService(TArgs&&... mArgs)
    {
        T* s(new T(std::forward<TArgs>(mArgs)...));
        std::unique_ptr<Service> uPtr{ s };
        services.emplace_back(std::move(uPtr));

        serviceArray[getServiceTypeID<T>()] = s;
        serviceBitSet[getServiceTypeID<T>()] = true;

        s->init();

        return *s;
    }

    template <typename T> T& getService() const
    {
        auto ptr(serviceArray[getServiceTypeID<T>()]);

        return *static_cast<T*>(ptr);
    }

    static ServiceManager* Instance();

private:
    static ServiceManager* instance;

    std::vector<std::unique_ptr<Service>> services;

    ServiceArray serviceArray;
    ServiceBitSet serviceBitSet;
};


#endif //BOBBERICK_TOOLS_SERVICEMANAGER_H
