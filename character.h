
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
                /**
                 *character: build a new character
                 * @param team - the team of the new character
                 * @param health -the health of the new character
                 * @param ammo -the ammo of the new character
                 * @param range- the range of the new character
                 * @param power-the power of the new character
                 */
        Character(Team team, int health, int ammo, int range, int power) :
            team(team), health(health), ammo(ammo), range(range), power(power)
        {

        }
        ~Character() = default;
        virtual void reload() = 0;
        /**
         * lowerHealth: lower the health of the this character
         * @param hit_points- the amount of health to drop
         * @return true f the character was killed
         * false if it is alive
         */
        bool lowerHealth(int hit_points);
        //getTeam: get the character team
        Team getTeam();
        virtual char getLetter()=0;
        //getPower: get the character power
        int getPower() const;
        virtual void lowerAmmo();
        //getAmmo: get the character ammo
        int getAmmo() const;
        //getRange: get the character range
        int getRange() const;
        virtual int getMaxMove()=0;
        virtual int hitMultiplier();
        virtual std::shared_ptr<Character> clone() const=0;
    };

}
#endif //HW2PART2_CHARACTER_H
