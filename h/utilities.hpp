#ifndef __VECTOR_OPERATORS_HPP__
#define __VECTOR_OPERATORS_HPP__

#include <iostream>
// #include <array>
// #include <algorithm>

// using HsvColor = std::array<float, 3>;

// HsvColor rgbToHsvColorFraction(const sf::Color & rgb){
    
// }

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
