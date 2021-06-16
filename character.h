
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
        bool lowerHealth(int hit_points)
        {
            if (this->health <= hit_points)
                return true;
            this->health -= hit_points;
            return false;
        }
        Team getTeam()
        {
            return this->team;
        }
        virtual char getLetter()=0;
        int getPower() const
        {
            return power;
        }
        void lowerAmmo()
        {
            this->ammo--;
        }
        int getAmmo() const
        {
            return this->ammo;
        }
        int getRange() const
        {
            return this->range;
        }
        virtual int getMaxMove()=0;
    };

}
#endif //HW2PART2_CHARACTER_H
