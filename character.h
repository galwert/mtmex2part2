
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
        bool lowerHealth(int hit_points)
        {
            if (this->health <= hit_points)
                return true;
            this->health -= hit_points;
            return false;
        }
        Team getTeam()
        {
            return this->team;
        }
        virtual char getLetter()=0;
        int getPower() const
        {
            return power;
        }
        virtual void lowerAmmo()
        {
            this->ammo--;
        }
        int getAmmo() const
        {
            return this->ammo;
        }
        int getRange() const
        {
            return this->range;
        }
        virtual int getMaxMove()=0;
        virtual int hitMultiplier()
        {
            return 0;
        }
        virtual std::shared_ptr<Character> clone() const=0;
    };

}
#endif //HW2PART2_CHARACTER_H
