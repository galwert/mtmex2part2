//
// Created by galwe on 15/06/2021.
//

#ifndef AUXILIARIES_H_MEDIC_H
#define AUXILIARIES_H_MEDIC_H
#include "Character.h"
namespace mtm
{
    class Medic : public Character
    {
    public:
        Medic(Team team, int health, int ammo, int range, int power) :
                Character(team, health, ammo, range, power)
        {

        }
        ~Medic() = default;

        void reload() override;

        char getLetter() override;
        int getMaxMove() override;
        std::shared_ptr<Character> clone() const override;
    };

}
#endif //AUXILIARIES_H_MEDIC_H
