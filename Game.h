

#ifndef SOLDIER_H_GAME_H
#define SOLDIER_H_GAME_H

#include <iostream>
#include <vector>
#include "Exceptions.h"
#include "Soldier.h"
#include "Medic.h"
#include "Sniper.h"
namespace mtm
{
    class Game
    {
    private:
        int height;
        int width;
        std::vector<std::vector< std::shared_ptr<Character>>> board;
    public:
        Game(int height, int width);

        ~Game()=default;

        Game(const Game &other);

        Game &operator=(const Game &other);

        void addCharacter(const GridPoint &coordinates, std::shared_ptr<Character> character);

        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team,
                                                               units_t health, units_t ammo, units_t range, units_t power)
        {
            if(health<=0||ammo<0||range<0||power<0)
            {
                throw IllegalArgument();
            }
            switch (type)
            {
                case CharacterType::SOLDIER:
                    {
                    return std::shared_ptr<Character>
                            (new Soldier(team, health, ammo, range, power));
                }
                case CharacterType::MEDIC:
                    {
                    return std::shared_ptr<Character>
                            (new Medic(team, health, ammo, range, power));
                }
                case CharacterType::SNIPER:
                    {
                    return std::shared_ptr<Character>
                            (new Sniper(team, health, ammo, range, power));
                }

            }
            return nullptr;
        }

        void move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);
        void attackAsSniper(GridPoint dst_coordinates,GridPoint src_coordinates);
        void attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);
        void attackAsMedic(GridPoint dst_coordinates,GridPoint src_coordinates);
        void reload(const GridPoint &coordinates);
        void attackAsSoldier(GridPoint dst_coordinates,GridPoint src_coordinates,std::shared_ptr<Character> character);
        friend std::ostream& operator<<(std::ostream& os, const Game& game);

        bool isOver(Team *winningTeam = nullptr) const;

        std::shared_ptr<Character> getCharacter(const GridPoint &dst_coordinates) const;
        void attackInSquare(GridPoint dst_coordinates,Team team,int power);

        void isIllegalCell(GridPoint coordinates) const
        {
            if(this->width<=coordinates.col||coordinates.col<0||this->height<=coordinates.row||coordinates.row<0)
            {
                throw IllegalCell();
            }
        }

    };


}
#endif //SOLDIER_H_GAME_H
