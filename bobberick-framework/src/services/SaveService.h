#ifndef BOBBERICK_TOOLS_SAVESERVICE_H
#define BOBBERICK_TOOLS_SAVESERVICE_H

#include "Service.h"
#include "../../externals/json/json.hpp"
#include <map>
#include <string>

class SaveService : public Service
{
public:
    SaveService();
    void init() override;
    void clean() override;

    template <typename T>
    void keep(const std::string &key, T value)
    {
        j->operator[](key) = value;
    }

    template <typename T>
    T get(std::string key) const
    {
        return j->operator[](key).get<T>();
    }

    bool load();
    void flush() const;
    bool has(std::string key) {
        return j->find(key) != j->end();
    }

private:
    std::unique_ptr<nlohmann::json> j;
    const std::string fileName;
};


#endif //BOBBERICK_TOOLS_SAVESERVICE_H
