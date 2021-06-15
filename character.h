
#ifndef HW2PART2_CHARACTER_H
#define HW2PART2_CHARACTER_H
namespace mtm
{
    class Character
            {
    protected:
        int health;
        int ammo;
        int range;
        int power;
        Team team;

        Character(Team team, int health, int ammo, int range, int power) :
            team(team), health(health), ammo(ammo), range(range), power(power)
        {

        }
        ~Character() = default;

    public:
        virtual void reload() = 0;

        bool lowerHealth(int power)
        {
            if (this->health <= power)
                return true;
            this->health -= power;
            return false;
        }
        Team getTeam()
        {
            return this->team;
        }
        virtual char getLetter()=0;
        int getPower()
        {
            return power;
        }
    };

}
#endif //HW2PART2_CHARACTER_H
