/*
** EPITECH PROJECT, 2022
** Project
** File description:
** UpdateBackgroundMusic
*/

#include "UpdateBackgroundMusic.hpp"
#include "GraphicECS/SFML/Components/MusicComponent.hpp"
#include "GraphicECS/SFML/Resources/MusicResource.hpp"
#include "R-TypeLogic/Global/Components/EnemyComponent.hpp"
#include "R-TypeLogic/Global/SharedResources/GameLevel.hpp"

using namespace graphicECS::SFML::Systems;
using namespace graphicECS::SFML::Components;

static void updateMusic(const MusicResource::music_e music, std::shared_ptr<ecs::Entity> entityPtr)
{
    std::lock_guard(*entityPtr.get());
    entityPtr->removeComponent<MusicComponent>();
    entityPtr->addComponent<MusicComponent>(music, sf::SoundSource::Status::Playing)
}

void UpdateBackgroundMusic::run(World &world)
{
    if (!world.containsResource<GameLevel>())
        return;
    GameLevel &gameLvl = world.getResource<GameLevel>();

    gameLvl.lock();
    GameLevel::level_e currLvl = gameLvl.getCurrentLevel();
    bool hasMusicChanged = gameLvl.hasMusicChanged();
    gameLvl.unlock();

    if (!hasMusicChanged)
        return;
    std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<MusicComponent>();
    std::vector<std::shared_ptr<ecs::Entity>> enemies = world.joinEntities<Enemy>();
    bool bossFight = false;

    for (auto &it : enemies) {
        {
            std::lock_guard(*it.get());
            if (it->getComponent<Enemy>().enemyType == Enemy::BOSS) {
                bossFight = true;
                break;
            }
        }
    }

    for (auto &it : joined) {
        switch (currLvl) {
            case GameLevel::LEVEL_TWO: updateMusic(MusicResource::music_e::LEVEL_TWO_THEME, it); break;
            case GameLevel::LEVEL_THREE: updateMusic(MusicResource::music_e::LEVEL_THREE_THEME, it); break;
            case GameLevel::LEVEL_FORTH: updateMusic(MusicResource::music_e::LEVEL_FOUR_THEME, it); break;
            case GameLevel::LEVEL_INFINITE:
                if (bossFight) {
                    updateMusic(MusicResource::music_e::BOSS_FIGHTTHEME, it);
                } else {
                    updateMusic(MusicResource::music_e::INFINITE_THEME, it);
                } break;
            default: break;
        }
    };
    gameLvl.lock();
    gameLvl.musicHasChanged();
    gameLvl.unlock();
}
