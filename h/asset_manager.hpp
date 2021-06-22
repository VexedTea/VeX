#ifndef __ASSET_MANAGER_HPP__
#define __ASSET_MANAGER_HPP__

#include <vector>
#include <array>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

#include "definitions.hpp"
#include "color_gradient.hpp"
#include "utilities.hpp"

namespace VeX{

    class Asset_Manager{
    private:
        std::map<std::string, sf::Texture> textures;
    public:
        // Texture functions
        const sf::Texture & loadTexture(const std::string & name) {
            return loadTexture(name, Definition::textures[name]);
        }

        const sf::Texture & loadTexture(const std::string & name, const std::string & fileName) {
            const auto& [texture, isKeyNew] = textures.emplace(name, sf::Texture());

            if (isKeyNew) {
                texture->second.loadFromFile(fileName);
            }
            return texture->second;
        }

        const sf::Texture & reloadTexture(const std::string & name) {
            return reloadTexture(name, Definition::textures[name]);
        }

        const sf::Texture & reloadTexture(const std::string & name, const std::string & fileName) {
            sf::Texture texture;
            texture.loadFromFile(fileName);
            return textures[name] = std::move(texture); //Could throw error on wrong name?
        }

        const sf::Texture & getTexture(const std::string & name) const {
            const auto& item = textures.find(name);

            if (item == textures.end()) {
                std::cerr << "[VeX WARNING] Unable to get asset of type 'Texture' with name '" << name << "'.\n";
            }
            return item->second; //Second is the value, first should be the key
        }

        const sf::Texture & loadTextureFromImage(const std::string & name, const sf::Image & image){
            const auto& [texture, isKeyNew] = textures.emplace(name, sf::Texture());

            if (isKeyNew) {
                texture->second.loadFromImage(image);
            }
            return texture->second;
        }

        std::vector<std::string> loadTexturesFromFolder(const std::string & folderPath){
            std::vector<std::string> textureNames;
            //std::size_t fileCount = countFilesInFolder(folderPath);
            for(const auto & entry : fs::directory_iterator(folderPath)){
                if(entry.path().extension() == ".png" || entry.path().extension() == ".jpg"){
                    //std::cout << entry.path().string() << std::endl;
                    loadTexture(entry.path().string(), entry.path().string());
                    textureNames.push_back(entry.path().string());
                }
            }
            return textureNames;
        }

        //Texture factory
        const sf::Texture & makeRectangleTexture(const std::string & name, const sf::Vector2i & dimensions, const sf::Color & color){
            sf::Image image;
            image.create(dimensions.x, dimensions.y, color);
            return loadTextureFromImage(name, image);
        }

        const sf::Texture & makeRectangleTexture(const std::string & name, const sf::Vector2i & dimensions, 
                                                const Color_Gradient & colors, const std::string & gradientDirection="LR"){
            sf::Image image;
            uint8_t* pixels = new uint8_t[dimensions.x*dimensions.y*4]; //Pixels in RGBA with one uint8_t per R, G, B or A.
            //image.create(dimensions.x, dimensions.y, sf::Color::White);
            if(gradientDirection == "LR"){
                for(int i=0; i<dimensions.x; i++){
                    for(int j=0; j<dimensions.y; j++){
                        sf::Color color = colors.getColorAt(float(i)/float(dimensions.x));
                        //if(j==0)std::cout << float(i)/float(dimensions.x) << "\n";
                        //if(j==0)std::cout << color.toInteger() << "\n";
                        //if(j==0)std::cout << unsigned(color.r) << " " << unsigned(color.g) << " " << unsigned(color.b) << "\n";
                        pixels[(i+(j*dimensions.x))*4] = color.r;
                        pixels[(i+(j*dimensions.x))*4+1] = color.g;
                        pixels[(i+(j*dimensions.x))*4+2] = color.b;
                        pixels[(i+(j*dimensions.x))*4+3] = 255;
                        //std::cout << "i: " << i << " j: " << j << "\n";
                        //image.setPixel(i, j, color);
                    }
                }
            }else{
                std::cout << "[VeX WARNING] unknown gradientDirection on a makeRectangleTexture function call.\n";
                image.create(dimensions.x, dimensions.y, sf::Color::White);
                return loadTextureFromImage(name, image);
            }
            image.create(dimensions.x, dimensions.y, pixels);
            return loadTextureFromImage(name, image);
        }
    };

}

#endif // __ASSET_MANAGER_HPP__
