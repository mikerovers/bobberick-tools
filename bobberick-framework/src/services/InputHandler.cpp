#include "InputHandler.h"
#include <SDL.h>

void InputHandler::init()
{
}

InputHandler::InputHandler() :
	m_mousePosition(new Vector2D(0, 0))
{
	windowClosed = false;
	//reset all states
	for (auto i = 0; i < 3; i++)
	{
		m_mouseButtonStates.push_back(false);
	}
}

Vector2D* InputHandler::getMousePosition() const
{
	return m_mousePosition;
}

void InputHandler::update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			// quit game
			break;
		case SDL_MOUSEMOTION:
			onMouseMove(event);
			break;
		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonDown(event);
			break;
		case SDL_MOUSEBUTTONUP:
			onMouseButtonUp(event);
			break;
		case SDL_KEYDOWN:
			onKeyDown(&event);
			break;
		case SDL_KEYUP:
			onKeyUp();
			break;
		case SDL_JOYBUTTONDOWN:
			onJoyButtonDown(event);
			break;
		case SDL_JOYBUTTONUP:
			onJoyButtonUp(event);
			break;
		case SDL_JOYAXISMOTION:
			onJoyAxisMotion(event);
			break;
		case SDL_WINDOWEVENT:
			onWindowEvent(event);
			break;
		default:
			break;
		}
	}
}

bool InputHandler::isKeyDown(SDL_Scancode key) const
{
	if (m_keystates != nullptr)
	{
		return static_cast<bool>(m_keystates[key]);
	}

	return false;
}

bool InputHandler::isWindowEvent(int windowEvent) const
{
	if (windowEvent == SDL_WINDOWEVENT_CLOSE)
	{
		return windowClosed;
	}
	return false;
}

void InputHandler::onKeyDown(SDL_Event* event)
{
	if (keyMapping)
	{
		newKey = event->key.keysym.scancode;
	}

	m_keystates = const_cast<Uint8*>(SDL_GetKeyboardState(nullptr));
}

void InputHandler::isMappingKey(bool isMappingKey)
{
	keyMapping = isMappingKey;
}

bool InputHandler::isMappingKey() const
{
	return keyMapping;
}

void InputHandler::onKeyUp()
{
	m_keystates = const_cast<Uint8*>(SDL_GetKeyboardState(nullptr));
}

void InputHandler::onMouseButtonDown(SDL_Event& event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		m_mouseButtonStates[LEFT] = true;
	}
	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		m_mouseButtonStates[MIDDLE] = true;
	}
	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		m_mouseButtonStates[RIGHT] = true;
	}
}

void InputHandler::onMouseMove(SDL_Event& event)
{
	m_mousePosition->x = event.motion.x;
	m_mousePosition->y = event.motion.y;
}

void InputHandler::onMouseButtonUp(SDL_Event& event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		m_mouseButtonStates[LEFT] = false;
	}
	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		m_mouseButtonStates[MIDDLE] = false;
	}
	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		m_mouseButtonStates[RIGHT] = false;
	}
}

bool InputHandler::getMouseButtonState(int buttonNumber)
{
	return m_mouseButtonStates[buttonNumber];
}

void InputHandler::onWindowEvent(const SDL_Event& event)
{
	if (event.window.event == SDL_WINDOWEVENT_CLOSE)
	{
		windowClosed = true;
	}
}

void InputHandler::initialiseJoysticks()
{
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
	{
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}
	if (SDL_NumJoysticks() > 0)
	{
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			SDL_Joystick* joy = SDL_JoystickOpen(i);
			if (joy)
			{
				m_joysticks.push_back(joy);
				m_joystickValues.push_back(std::make_pair(new
				                                          Vector2D(0, 0), new Vector2D(0, 0))); // add our pair

				std::vector<bool> tempButtons;
				for (int j = 0; j < SDL_JoystickNumButtons(joy); j++)
				{
					tempButtons.push_back(false);
				}
				m_buttonStates.push_back(tempButtons);
			}
			else
			{
				std::cout << SDL_GetError();
			}
		}
		SDL_JoystickEventState(SDL_ENABLE);
		m_bJoysticksInitialised = true;
		std::cout << "Initialised " << m_joysticks.size() << "joystick(s)";
	}
	else
	{
		m_bJoysticksInitialised = false;
	}
}

int InputHandler::xvalue(int joy, int stick)
{
	if (!m_joystickValues.empty())
	{
		if (stick == 1)
		{
			return static_cast<int>(m_joystickValues[joy].first->x);
		}
		if (stick == 2)
		{
			return static_cast<int>(m_joystickValues[joy].second->x);
		}
	}
	return 0;
}

int InputHandler::yvalue(int joy, int stick)
{
	if (!m_joystickValues.empty())
	{
		if (stick == 1)
		{
			return static_cast<int>(m_joystickValues[joy].first->y);
		}
		if (stick == 2)
		{
			return static_cast<int>(m_joystickValues[joy].second->y);
		}
	}
	return 0;
}

bool InputHandler::getButtonState(int joy, int buttonNumber)
{
	return m_buttonStates[joy][buttonNumber];
}

void InputHandler::onJoyButtonUp(SDL_Event& event)
{
	int whichOne = event.jaxis.which;
	m_buttonStates[whichOne][event.jbutton.button] = true;
}

void InputHandler::onJoyButtonDown(SDL_Event& event)
{
	int whichOne = event.jaxis.which;
	m_buttonStates[whichOne][event.jbutton.button] = false;
}

void InputHandler::onJoyAxisMotion(SDL_Event& event)
{
	int whichOne = event.jaxis.which;
	// left stick move left or right
	if (event.jaxis.axis == 0)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->x = 1;
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->x = -1;
		}
		else
		{
			m_joystickValues[whichOne].first->x = 0;
		}
	}
	// left stick move up or down
	if (event.jaxis.axis == 1)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->y = 1;
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].first->y = -1;
		}
		else
		{
			m_joystickValues[whichOne].first->y = 0;
		}
	}
	// right stick move left or right
	if (event.jaxis.axis == 3)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].second->x = 1;
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].second->x = -1;
		}
		else
		{
			m_joystickValues[whichOne].second->x = 0;
		}
	}
	// right stick move up or down
	if (event.jaxis.axis == 4)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_joystickValues[whichOne].second->y = 1;
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_joystickValues[whichOne].second->y = -1;
		}
		else
		{
			m_joystickValues[whichOne].second->y = 0;
		}
	}
}

void InputHandler::clean()
{
	if (m_bJoysticksInitialised)
	{
		for (unsigned int i = 0; i < SDL_NumJoysticks(); i++)
		{
			SDL_JoystickClose(m_joysticks[i]);
		}
	}
}

std::vector<std::pair<Vector2D *, Vector2D *>> InputHandler::getJoystickValues()
{
	return m_joystickValues;
}
