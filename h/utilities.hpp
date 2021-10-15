#ifndef __VECTOR_OPERATORS_HPP__
#define __VECTOR_OPERATORS_HPP__

#include <iostream>
#include <cmath>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

template <class T>
class ringbuff{
private:
    std::vector<T> buff;
    unsigned int size;
    unsigned int head;
    unsigned int tail;
public:
    explicit ringbuff(unsigned int size):
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

sf::Vector2f vector2iToVector2f(const sf::Vector2i & v){
    return {static_cast<float>(v.x), static_cast<float>(v.y)};
}

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

sf::Vector2f getPositionOnCircle(const sf::Vector2f & centerPos, float radius, float angleDegrees){
    return sf::Vector2f(centerPos.x + (radius*cos(angleDegrees*(3.14159265358979323846/180.f))), centerPos.y + (radius*sin(angleDegrees*(3.14159265358979323846/180.f))));
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
