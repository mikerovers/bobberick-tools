#include "SpriteComponent.h"
#include "../Entity.h"
#include "../../services/ServiceManager.h"
#include "../../services/TextureManager.h"
#include "../../services/RenderService.h"
#include <map>

void SpriteComponent::init()
{
	if (entity->hasComponent<TransformComponent>())
	{
		transform = &entity->getComponent<TransformComponent>();
	}
    sourceRect.x = sourceRect.y = 0;
	destinationRect.w = sourceRect.w = transform->width;
	destinationRect.h = sourceRect.h = transform->height;
	destinationRect.x = transform->position.x;
	destinationRect.y = transform->position.y;
}

void SpriteComponent::update()
{
	if (moving) { // TODO double code
		if (currentFrame >= 0) {
			animTimer--;
			if (animTimer == 0) {
				animTimer = animRate;
				currentFrame++;
				if (currentFrame >= animFrames) {
					currentFrame = 0;
				}

				int currentRow = currentFrame / animCols;
				int currentCol = currentFrame % animCols;

				sourceRect.x = transform->width * currentCol;
				sourceRect.y = transform->height * currentRow;
			}
		}
	}	
	else {
		currentFrame = 0;
	}

	destinationRect.x = transform->position.x;
	destinationRect.y = transform->position.y;
}

void SpriteComponent::render()
{
    ServiceManager::Instance()->getService<TextureManager>().draw(currentTexture, &sourceRect, &destinationRect, ServiceManager::Instance()->getService<RenderService>().getRenderer(), flip);
}

SpriteComponent::SpriteComponent(const std::string textureID, const bool guiLayer): staticAnimation(false)
{
	currentTexture = textureID;
	currentFrame = -1;
	SpriteComponent::guiLayer = guiLayer;
}

SpriteComponent::SpriteComponent(const char *textureID, const int animCols, const int animFrames, const int animRate): staticAnimation(false)
{
	currentTexture = textureID;
	SpriteComponent::animCols = animCols;
	SpriteComponent::animFrames = animFrames;
	SpriteComponent::animRate = animRate;
	animTimer = animRate;
	currentFrame = 0;
}

void SpriteComponent::setTexture(const char * textureID) 
{
	if (currentTexture != textureID) {
		currentTexture = textureID;
	}
}

void SpriteComponent::setCurrentFrame(const int frame)
{
	currentFrame = frame;
}

void SpriteComponent::setStaticAnimation(const bool stan)
{
	staticAnimation = stan;
}

SpriteComponent::SpriteComponent(): staticAnimation(false)
{

}

void SpriteComponent::processScale(const int scale)
{
	destinationRect.w = destinationRect.w * scale;
	destinationRect.h = destinationRect.h * scale;
}

SDL_Rect &SpriteComponent::getSourceRect()
{
	return sourceRect;
}

SDL_Rect &SpriteComponent::getDestinationRect()
{
	return destinationRect;
}

std::string &SpriteComponent::getTexture()
{
	return currentTexture;
}

