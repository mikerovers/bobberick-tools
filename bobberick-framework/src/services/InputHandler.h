#ifndef __SDL__InputHandler__
#define __SDL__InputHandler__
#include "../util/Vector2D.h"
#include <stdio.h>
#include <vector>
#include <SDL.h>
#include <iostream>
#include <SDL_system.h>
#include "../services/Service.h"
#include <bitset>

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputHandler : public Service
{
public:
	InputHandler();

	~InputHandler()
	{
	};

	void update();
	void clean() override;

	void init() override;

	/// Handling Mouse Event
	void onMouseButtonDown(SDL_Event& event);
	void onMouseMove(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);
	void onJoyButtonDown(SDL_Event& event);
	void onJoyButtonUp(SDL_Event& event);
	void onJoyAxisMotion(SDL_Event& event);
	bool getMouseButtonState(int buttonNumber);
	void onWindowEvent(const SDL_Event& event);

	Vector2D* getMousePosition() const;

	std::vector<std::pair<Vector2D*, Vector2D*>> getJoystickValues();

	///Handling Keyboard Event
	void onKeyDown(/*bool keyMapping = false, */SDL_Event* event = nullptr);
	void onKeyUp();
	bool isKeyDown(SDL_Scancode key) const;
	bool isWindowEvent(int windowEvent) const;
	
	void initialiseJoysticks();

	bool joysticksInitialised()
	{
		return m_bJoysticksInitialised;
	}

	bool getButtonState(int joy, int buttonNumber);

	void isMappingKey(bool isMappingKey);
	bool isMappingKey() const;

	int xvalue(int joy, int stick);
	int yvalue(int joy, int stick);

	SDL_Scancode newKey;

private:
	std::vector<bool> m_mouseButtonStates;
	std::vector<std::vector<bool>> m_buttonStates;
	Vector2D* m_mousePosition;
	Uint8* m_keystates = 0;

	std::vector<SDL_Joystick*> m_joysticks;
	std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
	bool m_bJoysticksInitialised{};
	const int m_joystickDeadZone = 10000;

	// std::vector<bool> windowStates;
	
	bool windowClosed;

	bool keyMapping = false;
};

#endif /* defined(__SDL__InputHandler__) */
