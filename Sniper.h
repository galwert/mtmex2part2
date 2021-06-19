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
        Sniper(Team team, int health, int ammo, int range, int power) :
                Character(team, health, ammo, range, power)
        {
            hit=ZERO;
        }
        Sniper(Team team, int health, int ammo, int range, int power,HitNumber hit) :
                Character(team, health, ammo, range, power),hit(hit)
        {
        }

        ~Sniper() = default;

        void reload() override;


        char getLetter() override;
        int getMaxMove() override;
        int hitMultiplier() override;
        std::shared_ptr<Character> clone() const override;
    };

}
#endif //AUXILIARIES_H_SNIPER_H
