#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <cstdint>

struct Collision {
    float X;
    float Y;
    float Width;
    float Height;    
};

static bool checkCollision(const Collision& a, const Collision& b) {
    return (
        a.X < b.X + b.Width &&
        a.X + a.Width > b.X &&
        a.Y < b.Y + b.Height &&
        a.Y + a.Height > b.Y
    );
}

#endif // COLLISION_HPP
