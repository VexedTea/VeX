#ifndef __GRAVITATIONAL_SYSTEM_HPP__
#define __GRAVITATIONAL_SYSTEM_HPP__

#include "utilities.hpp"
#include "circle_object.hpp"
#include "definitions.hpp"

namespace VeX{

    class Gravitational_System{
    private:
        std::vector<std::unique_ptr<Circle_Object>> bodies;
    public:
        Gravitational_System();

        void update(float delta);

        void draw(float delta);

        void addBody(std::unique_ptr<Circle_Object> newBody);
    };

} // namespace VeX

#endif // __GRAVITATIONAL_SYSTEM_HPP__
