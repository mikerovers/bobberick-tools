#ifndef BOBBERICK_TOOLS_SERVICE_H
#define BOBBERICK_TOOLS_SERVICE_H


class Service
{
public:
    virtual ~Service() = default;
    virtual void init() = 0;
    virtual void clean() = 0;
};


#endif //BOBBERICK_TOOLS_SERVICE_H
