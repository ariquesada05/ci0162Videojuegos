#ifndef STATS_COMPONENT_HPP
#define STATS_COMPONENT_HPP

struct StatsComponent
{
    int Health;
    int Points;
    int Damage;

    StatsComponent(
        int health = 0,
        int points = 0,
        int damage = 0)
    {
        Health = health;
        Points = points;
        Damage = damage;
    }
};

#endif