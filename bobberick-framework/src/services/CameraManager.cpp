#include "CameraManager.h"

void CameraManager::init()
{

}

void CameraManager::clean()
{

}
const Vector2D CameraManager::getPosition() const
{
	{

		Vector2D pos(m_position.x - (640 / 2), m_position.y - 480 / 2);
		if (pos.x < 0)
		{
			pos.x = 0;
		}
		if (pos.y < 0)
		{
			pos.y = 0;
		}
		return pos;

	}
}