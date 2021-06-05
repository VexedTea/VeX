#ifndef __ASSET_MANAGER_HPP__
#define __ASSET_MANAGER_HPP__

#include <vector>

#include "definitions.hpp"

namespace VeX{

    class Asset_Manager{
    private:
        std::map<std::string, sf::Texture> textures;
    public:
        // Texture functions
        const sf::Texture& loadTexture(const std::string & name) {
            return loadTexture(name, Definition::textures[name]);
        }

        const sf::Texture& loadTexture(const std::string & name, const std::string & fileName) {
            const auto& [texture, isKeyNew] = textures.emplace(name, sf::Texture());

            if (isKeyNew) {
                texture->second.loadFromFile(fileName);
            }
            return texture->second;
        }

        const sf::Texture& reloadTexture(const std::string & name) {
            return reloadTexture(name, Definition::textures[name]);
        }

        const sf::Texture& reloadTexture(const std::string & name, const std::string & fileName) {
            sf::Texture texture;
            texture.loadFromFile(fileName);
            return textures[name] = std::move(texture); //Could throw error on wrong name?
        }

        const sf::Texture& getTexture(const std::string & name) const {
            const auto& item = textures.find(name);

            if (item == textures.end()) {
                std::cerr << "[VeX WARNING] Unable to get asset of type 'Texture' with name '" << name << "'.\n";
            }
            return item->second; //Second is the value, first should be the key
        }
    };

}

#endif // __ASSET_MANAGER_HPP__
