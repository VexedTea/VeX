#include "../h/utilities.hpp"

float min(const sf::Vector2f & v){
    if(v.y < v.x){
        return v.y;
    }else{
        return v.x;
    }
}

sf::Vector2f vector2iToVector2f(const sf::Vector2i & v){
    return {static_cast<float>(v.x), static_cast<float>(v.y)};
}

sf::Vector2f vector2uToVector2f(const sf::Vector2u & v){
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

// inline bool operator<(
//     const sf::Vector2i & left,
//     const sf::Vector2i & right
// ){
//     return magnitude(left) < magnitude(right);
// }

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
