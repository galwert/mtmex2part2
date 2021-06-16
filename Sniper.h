//
// Created by galwe on 15/06/2021.
//

#ifndef AUXILIARIES_H_SNIPER_H
#define AUXILIARIES_H_SNIPER_H

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
                return 'N';
            }
        }
        int getMaxMove() override
        {
            return 4;
        }
        int hitMultiplier() override
        {
            if(this->hit==SECOND)
            {
                this->hit=ZERO;
                return 2;
            }
            if(this->hit==FIRST)
            {
                this->hit=SECOND;
            }
            if(this->hit==ZERO)
            {
                this->hit=FIRST;
            }
            return 1;
        }
        Character* clone() const override
        {
            return new Sniper(this->team, this->health,this->ammo,this->range,this->power,this->hit);
        }
    };

}
#endif //AUXILIARIES_H_SNIPER_H
