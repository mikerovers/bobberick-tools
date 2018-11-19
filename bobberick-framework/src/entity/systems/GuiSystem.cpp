#include "GuiSystem.h"
#include "../components/ButtonComponent.h"
#include "../../services/ServiceManager.h"
#include "../../services/InputHandler.h"
#include "../../services/TextureManager.h"
#include "../components/SpriteComponent.h"
#include "../components/ButtonSpriteComponent.h"

GuiSystem::GuiSystem(EntityManager &entityManager) : System(entityManager)
{

}

void GuiSystem::update()
{
    for (auto& entity: entityManager.getAllEntitiesWithComponent<ButtonComponent>()) {
        auto& bC = entity->getComponent<ButtonComponent>();
        auto& inputHandler = ServiceManager::Instance()->getService<InputHandler>();
        auto& tx = ServiceManager::Instance()->getService<TextureManager>();
        Vector2D* mousePosition = inputHandler.getMousePosition();
        auto& spr = entity->getComponent<ButtonSpriteComponent>();
        auto& transformComponent = entity->getComponent<TransformComponent>();

        if (mousePosition->x < transformComponent.position.x + transformComponent.width
            && mousePosition->x > transformComponent.position.x
            && mousePosition->y < transformComponent.position.y + transformComponent.height
            && mousePosition->y > transformComponent.position.y)
        {
            spr.setCurrentFrame(1);

            if (inputHandler.getMouseButtonState(LEFT)) {
                spr.setCurrentFrame(2);
                if (bC.getReleased()) {
                    bC.runCallback();
                    bC.setReleased(false);
                }
            } else if (!inputHandler.getMouseButtonState(LEFT)) {
                bC.setReleased(true);
            }
        } else {
            spr.setCurrentFrame(0);
        }

        spr.update();
        spr.render();
    }
}
