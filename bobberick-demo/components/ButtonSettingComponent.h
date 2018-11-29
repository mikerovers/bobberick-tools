#ifndef BOBBERICK_TOOLS_BUTTONSETTINGCOMPONENT_H
#define BOBBERICK_TOOLS_BUTTONSETTINGCOMPONENT_H

#include "../../bobberick-framework/src/entity/Component.h"

class ButtonSettingComponent : public Component
{
public:
	explicit ButtonSettingComponent(std::string setting) : setting(setting) {};
	std::string getSetting() const;
private:
	std::string setting;
};


#endif //BOBBERICK_TOOLS_BUTTONSETTINGCOMPONENT_H
