#ifndef BOBBERICK_TOOLS_CAMERAMANAGER_H
#define BOBBERICK_TOOLS_CAMERAMANAGER_H

#include "Service.h"
#include "../util//Vector2D.h"
class CameraManager : public Service
{
public:
	void init() override;
	void clean() override;
	void update(Vector2D velocity);
	void setTarget(Vector2D* target) { m_pTarget = target; }
	void setPosition(const Vector2D& position) {
		m_position = position;
	}
	const Vector2D getPosition() const;
private:
	// the camera's target
	Vector2D* m_pTarget;
	// the camera's position
	Vector2D m_position;
};


#endif //BOBBERICK_TOOLS_CAMERAMANAGER_H
