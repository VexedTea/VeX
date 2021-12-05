#ifndef __VECTOR_OPERATORS_HPP__
#define __VECTOR_OPERATORS_HPP__

#include <iostream>
#include <cmath>
#include <experimental/filesystem>
#include "SFML/Graphics.hpp"
namespace fs = std::experimental::filesystem;

template <class T>
class Ringbuff{
private:
    std::vector<T> buff;
    unsigned int size;
    unsigned int head;
    unsigned int tail;
public:
    explicit Ringbuff(unsigned int size):
        buff(),
        size(size),
        head(0),
        tail(0)
    {}

    void push_back(const T & item){
        head++;
        if(head >= size){
            head -= size;
        }
        if(head == tail){
            tail++;
            if(tail >= size){
                tail -= size;
            }
        }
        if(head >= buff.size()){
            buff.push_back(item);
        }else{
            buff[head] = item;
        }
    }

    T front(){
        return buff[head];
    }

    T back(){
        return buff[tail];
    }
};

sf::Vector2f vector2iToVector2f(const sf::Vector2i & v);

float angleRadians(const sf::Vector2f & v);

sf::Vector2f pow(const sf::Vector2f & v, int power);

float distance(const sf::Vector2f & point1, const sf::Vector2f & point2);

float magnitude(const sf::Vector2f & v);

sf::Vector2f normalize(const sf::Vector2f & v);

unsigned int countFilesInFolder(const std::string & folderPath);

sf::Vector2f getPositionOnCircle(const sf::Vector2f & centerPos, float radius, float angleDegrees);

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

inline sf::Vector2f operator|(
    const sf::FloatRect& left,
    float right
) {
    return {left.width / right, left.height / right};
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

std::ostream& operator<<(std::ostream &os, const sf::Vector2f & vec);

std::ostream& operator<<(std::ostream &os, const sf::Vector2i & vec);

std::ostream& operator<<(std::ostream &os, const sf::Vector2u & vec);

#endif // __VECTOR_OPERATORS_HPP__
