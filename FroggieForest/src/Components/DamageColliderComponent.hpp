#ifndef DAMAGE_COLLIDER_COMPONENT_HPP
#define DAMAGE_COLLIDER_COMPONENT_HPP

struct DamageColliderComponent
{
    int Width;
    int Height;

    DamageColliderComponent(
        int width = 0,
        int height = 0)
    {
        Width = width;
        Height = height;
    }
};

#endif