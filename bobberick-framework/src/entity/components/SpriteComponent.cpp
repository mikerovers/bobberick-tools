#include "SpriteComponent.h"
#include "../Entity.h"
#include "../../services/ServiceManager.h"
#include "../../TextureManager.h"
#include "../../services/RenderService.h"

void SpriteComponent::init()
{
    transform = &entity->getComponent<TransformComponent>();

    sourceRect.x = sourceRect.y = 0;
	destinationRect.w = sourceRect.w = transform->width;
	destinationRect.h = sourceRect.h = transform->height;
	destinationRect.x = transform->position.getX();
	destinationRect.y = transform->position.getY();
}

void SpriteComponent::update()
{
	if (currentFrame >= 0) {
		animTimer--;
		if (animTimer == 0 || staticAnimation) {
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

	destinationRect.x = transform->position.getX();
	destinationRect.y = transform->position.getY();
}

void SpriteComponent::render()
{
    ServiceManager::Instance()->getService<TextureManager>().draw(texture, &sourceRect, &destinationRect, ServiceManager::Instance()->getService<RenderService>().getRenderer());
}

SpriteComponent::SpriteComponent(const char *path, const char *textureID): staticAnimation(false)
{
    if (ServiceManager::Instance()->getService<TextureManager>().load(path, textureID, ServiceManager::Instance()->getService<RenderService>().renderer)) {
        texture = textureID;
    } else {
        std::cout << SDL_GetError();
    }

	currentFrame = -1;

}

SpriteComponent::SpriteComponent(const char *path, const char *textureID, const int animCols, const int animFrames, const int animRate): staticAnimation(false)
{
	if (ServiceManager::Instance()->getService<TextureManager>().load(path, textureID, ServiceManager::Instance()->getService<RenderService>().renderer)) {
		texture = textureID;
	}
	else {
		std::cout << SDL_GetError();
	}

	SpriteComponent::animCols = animCols;
	SpriteComponent::animFrames = animFrames;
	SpriteComponent::animRate = animRate;
	animTimer = animRate;
	currentFrame = 0;
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

