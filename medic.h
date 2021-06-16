//
// Created by galwe on 15/06/2021.
//

#ifndef AUXILIARIES_H_MEDIC_H
#define AUXILIARIES_H_MEDIC_H

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

        void reload() override {
            this->ammo += 5;
        }


        char getLetter() override
        {
            if(this->team==CROSSFITTERS)
            {
                return 'm';
            }
            else
            {
                return 'M';
            }
        }
        int getMaxMove() override
        {
            return 5;
        }
    };

}
#endif //AUXILIARIES_H_MEDIC_H
