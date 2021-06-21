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
        /**
                 *Medic: build a new Medic
                 * @param team - the team of the new character
                 * @param health -the health of the new character
                 * @param ammo -the ammo of the new character
                 * @param range- the range of the new character
                 * @param power-the power of the new character
                 */
        Medic(Team team, int health, int ammo, int range, int power) :
                Character(team, health, ammo, range, power)
        {

        }
        ~Medic() = default;

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
         * clone: makes a new shared_ptr with the same character information
         * @return a new shared_ptr pointing the character with the some information as this
         */
        std::shared_ptr<Character> clone() const override;
    };

}
#endif //AUXILIARIES_H_MEDIC_H
