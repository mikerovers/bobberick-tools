#ifndef BOBBERICK_TOOLS_SERVICEMANAGER_H
#define BOBBERICK_TOOLS_SERVICEMANAGER_H


#include <vector>
#include <bitset>
#include <map>
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

class ServiceManager
{
public:
    template <typename T> bool hasService() const
    {
        return serviceBitSet[getServiceTypeID<T>()];
    }

    template <typename T, typename ... TArgs> void addService(TArgs&&... mArgs)
    {
        std::unique_ptr<T> nPtr = std::make_unique<T>(std::forward<TArgs>(mArgs)...);
        ServiceID serviceID = getServiceTypeID<T>();
        if (servicesMap.find(serviceID) == servicesMap.end()) {
            servicesMap[serviceID] = std::move(nPtr);
            serviceBitSet[getServiceTypeID<T>()] = true;
        }
    }

    template <typename T> T& getService() const
    {
        const ServiceID serviceID = getServiceTypeID<T>();
        auto ptr = servicesMap.find(serviceID)->second.get();

        return *static_cast<T*>(ptr);
    }

    void clean();

    static ServiceManager* Instance();

private:
    static ServiceManager* instance;
    std::map<ServiceID, std::unique_ptr<Service>> servicesMap;
    ServiceBitSet serviceBitSet;
};


#endif //BOBBERICK_TOOLS_SERVICEMANAGER_H
