

#ifndef SOLDIER_H_GAME_H
#define SOLDIER_H_GAME_H

#include <iostream>
#include <memory>
#include <vector>
#include "Exceptions.h"
#include "Auxiliaries.h"
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
        std::vector<std::vector< std::shared_ptr<Character>>> *board;
    public:
        Game(int height, int width);

        ~Game()=default;

        Game(const Game &other);

        Game &operator=(const Game &other);

        void addCharacter(const GridPoint &coordinates, std::shared_ptr<Character> character);

        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team,
                                                               units_t health, units_t ammo, units_t range, units_t power)
        {
            if(health<=0||ammo<0||range<=0||power<0)
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

        void attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);

        void reload(const GridPoint &coordinates);

        friend std::ostream& operator<<(std::ostream& os, const Game& game);

        bool isOver(Team *winningTeam = nullptr) const;

        std::shared_ptr<Character> getCharacter(const GridPoint &dst_coordinates) const;
        int getWidth() const
        {
            return this->width;
        }
        int getHeigth() const
        {
            return this->height;
        }
        void attackInSquare(GridPoint dst_coordinates,Team team,int power);

        void isIllegalCell(GridPoint coordinates) const
        {
            if(this->width<=coordinates.col||coordinates.col<0||this->height<=coordinates.row||coordinates.row<0)
            {
                throw IllegalCell();
            }
        }

    };

    std::ostream& operator<<(std::ostream& os, const Game& game)
    {
       std::string str;
       for (int i = 0; i < game.height; i++)
        {
            for (int j = 0; j < game.width; j++)
            {
                if(game.board->at(i).at(j)== nullptr)
                {
                    str[i*game.width+j]=' ';
                }
                else
                {
                    str[i*game.width+j]=game.getCharacter(GridPoint(i,j))->getLetter();
                }
            }
        }
        return printGameBoard(os, str.c_str(), str.c_str()+(game.height * game.width), (unsigned int)game.width);
    }

}
#endif //SOLDIER_H_GAME_H
