/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** MusicManagement
*/

using namespace graphicECS::SFML::Components;

namespace graphicECS::SFML::Systems
{
    void MusicManagement::run(World &world)
    {
        std::vector<std::shared_ptr<ecs::Entity>> joined = world.joinEntities<MusicName>();

        auto stopMusic = [&world](std::shared_ptr<ecs::Entity> entityPtr) {
            MusicName sound = entityPtr.get()->getComponent<MusicName>();

            if (sound.getStatus() == MusicName::STOPED) {
                world.getResource<MusicResource>()._soundsList.at(sound.getName())->stop();
            }
            if (sound.getStatus() == MusicName::PAUSED) {
                world.getResource<MusicResource>()._soundsList.at(sound.getName())->pause();
            }
            if (sound.getStatus() == MusicName::PLAYING) {
                world.getResource<MusicResource>()._soundsList.at(sound.getName())->play();
            }
        };

        std::for_each(joined.begin(), joined.end(), stopMusic);
    }
} // namespace graphicECS::SFML::Systems
