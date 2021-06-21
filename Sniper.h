//
// Created by galwe on 15/06/2021.
//

#ifndef AUXILIARIES_H_SNIPER_H
#define AUXILIARIES_H_SNIPER_H
#include "Character.h"
namespace mtm
{

    class Sniper : public Character
    {
        enum HitNumber {
            ZERO,FIRST,SECOND
        };
    private:
        HitNumber hit;
    public:
        /**
                *Sniper: build a new Sniper
                * @param team - the team of the new character
                * @param health -the health of the new character
                * @param ammo -the ammo of the new character
                * @param range- the range of the new character
                * @param power-the power of the new character
                */
        Sniper(Team team, int health, int ammo, int range, int power) :
                Character(team, health, ammo, range, power)
        {
            hit=ZERO;
        }
        /**
                *Sniper: build a new Sniper
                * @param team - the team of the new character
                * @param health -the health of the new character
                * @param ammo -the ammo of the new character
                * @param range- the range of the new character
                * @param power-the power of the new character
                * @param hit- the hit number of the new character
                */
        Sniper(Team team, int health, int ammo, int range, int power,HitNumber hit) :
                Character(team, health, ammo, range, power),hit(hit)
        {
        }

        ~Sniper() = default;

        /**
         * reload: reload with the current character
         */
        void reload() override;
        /**
         * getLetter: get a letter representing the current character
         */

        char getLetter() override;
        /**
        * getMaxMove:returns the max number of cells possible to move with the character
        * @return the number of moves possible
        */
        int getMaxMove() override;

        /**
         * hitMultiplier: counts the number of hits. if it is third hit return 2 if not return 1.
         * also increase the hit count
         * @return the hit multiplier
         */
        int hitMultiplier() override;
        /**
         * clone: makes a new shared_ptr with the same character information
         * @return a new shared_ptr pointing the character with the some information as this
         */
        std::shared_ptr<Character> clone() const override;
    };

}
#endif //AUXILIARIES_H_SNIPER_H
