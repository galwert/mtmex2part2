
#ifndef HW2PART2_CHARACTER_H
#define HW2PART2_CHARACTER_H
#include "Auxiliaries.h"
#include <memory>
namespace mtm
{
    class Character
            {
    protected:
        Team team;
        int health;
        int ammo;
        int range;
        int power;
    public:
        Character(Team team, int health, int ammo, int range, int power) :
            team(team), health(health), ammo(ammo), range(range), power(power)
        {

        }
        ~Character() = default;
        virtual void reload() = 0;
        bool lowerHealth(int hit_points);
        Team getTeam();
        virtual char getLetter()=0;
        int getPower() const;
        virtual void lowerAmmo();
        int getAmmo() const;
        int getRange() const;
        virtual int getMaxMove()=0;
        virtual int hitMultiplier();
        virtual std::shared_ptr<Character> clone() const=0;
    };

}
#endif //HW2PART2_CHARACTER_H
