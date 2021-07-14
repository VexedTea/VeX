#ifndef __VECTOR_OPERATORS_HPP__
#define __VECTOR_OPERATORS_HPP__

#include <iostream>
#include <cmath>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

float angleRadians(const sf::Vector2f & v){
    float angle = atan2(v.y, v.x)/* *180/3.14159265358979323846 */;
    // if(angle < 0){
    //     angle += 360;
    // }
    return angle;
}

sf::Vector2f pow(const sf::Vector2f & v, int power){
    return sf::Vector2f(pow(v.x, power), pow(v.y, power));
}

float distance(const sf::Vector2f & point1, const sf::Vector2f & point2){
    return sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
}

float magnitude(const sf::Vector2f & v){
    return distance(v, {0.f,0.f});
}

sf::Vector2f normalize(const sf::Vector2f & v){
    return v / magnitude(v);
}

unsigned int countFilesInFolder(const std::string & folderPath){
    unsigned int count = 0;
    for(const auto & entry : fs::directory_iterator(folderPath)){
        if(fs::is_regular_file(entry)){
            count++;
        }
    }
    return count;
}

template<typename T>
inline sf::Vector2f operator/(
    const sf::Vector2<T>& left,
    const sf::Vector2f& right
) {
    return {left.x / right.x, left.y / right.y};
}

template<typename T>
inline sf::Vector2f operator/(
    const sf::Vector2f& left,
    const sf::Vector2<T>& right
) {
    return {left.x / right.x, left.y / right.y};
}

inline sf::Vector2f operator/(
    const sf::Vector2f& left,
    const sf::Vector2f& right
) {
    return {left.x / right.x, left.y / right.y};
}

inline sf::Vector2f operator/(
    const sf::Vector2f& left,
    float right
) {
    return {left.x / right, left.y / right};
}

inline sf::Vector2f operator/(
    const sf::Vector2u& left,
    const sf::Vector2u& right
) {
    const auto leftX{static_cast<float>(left.x)};
    const auto leftY{static_cast<float>(left.y)};
    return {leftX / right.x, leftY / right.y};
}

inline sf::Vector2f operator+(
    const sf::Vector2f& left,
    float right
) {
    return {left.x + right, left.y + right};
}

inline sf::Vector2f operator-(
    const sf::Vector2f& left,
    const sf::Vector2u& right
) {
    return {left.x - right.x, left.y - right.y};
}

template<typename T>
inline sf::Vector2f operator*(
    const sf::Vector2<T>& left,
    const sf::Vector2f& right
) {
    return {left.x * right.x, left.y * right.y};
}

template<typename T>
inline sf::Vector2f operator*(
    const sf::Vector2f& left,
    const sf::Vector2<T>& right
) {
    return {left.x * right.x, left.y * right.y};
}

inline sf::Vector2f operator*(
    const sf::Vector2f& left,
    const sf::Vector2f& right
) {
    return {left.x * right.x, left.y * right.y};
}

inline sf::Vector2f operator*(
    const sf::Vector2f& left,
    float right
) {
    return {left.x * right, left.y * right};
}

inline sf::Vector2f operator*(
    const sf::Vector2u& left,
    float right
) {
    return {float(left.x) * right, float(left.y) * right};
}

inline sf::Vector2f operator*(
    const sf::Vector2u& left,
    const sf::Vector2u& right
) {
    const auto leftX{static_cast<float>(left.x)};
    const auto leftY{static_cast<float>(left.y)};
    return {leftX * right.x, leftY * right.y};
}

template<typename T>
inline sf::Vector2<T> operator*(
    const sf::Vector2<T>& left,
    float right
) {
    return {left.x * right, left.y * right};
}

template<typename T>
inline sf::Vector2<T> operator*(
    const sf::Vector2<T>& left,
    int right
) {
    return {left.x * right, left.y * right};
}

template<typename T>
inline sf::Vector2f operator/(
    const sf::Vector2<T>& left,
    float right
) {
    return {left.x / right, left.y / right};
}

std::ostream& operator<<(std::ostream &os, const sf::Vector2f & vec){
    os << "(" << vec.x <<", "<< vec.y << ")";
    return os;
}

std::ostream& operator<<(std::ostream &os, const sf::Vector2i & vec){
    os << "(" << vec.x <<", "<< vec.y << ")";
    return os;
}

std::ostream& operator<<(std::ostream &os, const sf::Vector2u & vec){
    os << "(" << vec.x <<", "<< vec.y << ")";
    return os;
}

#endif // __VECTOR_OPERATORS_HPP__
