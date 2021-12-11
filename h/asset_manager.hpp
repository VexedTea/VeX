#ifndef __ASSET_MANAGER_HPP__
#define __ASSET_MANAGER_HPP__

#include <vector>
#include <array>
#include <mutex>
#include <experimental/filesystem>
#include "SFML/Graphics.hpp"
namespace fs = std::experimental::filesystem;

#include "definitions.hpp"
// #include "utilities.hpp"
//#include "progress_bar.hpp"

namespace VeX{

    using Shader_Ptr = std::shared_ptr<sf::Shader>;

    class Asset_Manager{
    private:
        sf::Texture blankTexture;
        std::map<std::string, sf::Texture> textures;
        std::map<std::string, Shader_Ptr> shaders;
    public:
        Asset_Manager();

        // Texture functions
        const sf::Texture & getBlankTexture();

        const sf::Texture & loadTexture(const std::string & name);

        const sf::Texture & loadTexture(const std::string & name, const std::string & fileName);

        const sf::Texture & reloadTexture(const std::string & name);

        const sf::Texture & reloadTexture(const std::string & name, const std::string & fileName);

        const sf::Texture & getTexture(const std::string & name) const;

        const sf::Texture & loadTextureFromImage(const std::string & name, const sf::Image & image);

        void loadTexturesFromFolder(std::vector<std::string> & textureNames, const std::string & folderPath, float & progress, std::mutex & progressMutex);

        void setRepeated(const std::string & name, bool repeated);

        const Shader_Ptr & loadVertexShader(const std::string & name, const std::string & fileName);

        const Shader_Ptr & loadFragmentShader(const std::string & name, const std::string & fileName);

        const Shader_Ptr & loadShader(const std::string & name, const std::string & fileName);

        //Texture factory
        const sf::Texture & makeRectangleTexture(const std::string & name, const sf::Vector2i & dimensions, const sf::Color & color);

        const sf::Texture & makeRectangleTexture(const std::string & name, const sf::Vector2i & dimensions, 
                                                 const Color_Gradient & colors, const std::string & gradientDirection="LR");
    };

}

#endif // __ASSET_MANAGER_HPP__
