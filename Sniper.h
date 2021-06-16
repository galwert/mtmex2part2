//
// Created by galwe on 15/06/2021.
//

#ifndef AUXILIARIES_H_SNIPER_H
#define AUXILIARIES_H_SNIPER_H

namespace mtm
{
    class Sniper : public Character
    {
    public:
        Sniper(Team team, int health, int ammo, int range, int power) :
                Character(team, health, ammo, range, power)
        {

        }

        ~Sniper() = default;

        void reload() override {
            this->ammo += 2;
        }


        char getLetter() override
        {
            if(this->team==CROSSFITTERS)
            {
                return 'n';
            }
            else
            {
                return 'M';
            }
        }
        int getMaxMove() override
        {
            return 4;
        }
    };

}
#endif //AUXILIARIES_H_SNIPER_H
