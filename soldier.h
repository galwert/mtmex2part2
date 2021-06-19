//
// Created by galwe on 09/06/2021.
//

#ifndef HW2PART2_SOLDIER_H
#define HW2PART2_SOLDIER_H

#include "Character.h"
namespace mtm
{
    class Soldier : public Character
            {
    public:
        Soldier(Team team, int health, int ammo, int range, int power) :
                Character(team, health, ammo, range, power)
        {

        }

        ~Soldier() = default;

        void reload() override;
        char getLetter() override;
        int getMaxMove() override;
        std::shared_ptr<Character> clone() const override;

    };

}

#endif //HW2PART2_SOLDIER_H
