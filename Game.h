

#ifndef SOLDIER_H_GAME_H
#define SOLDIER_H_GAME_H

#include <iostream>
#include <memory>
#include <vector>
#include "Exceptions.h"
#include "Auxiliaries.h"
#include "Soldier.h"
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
            switch (type)
            {
                case CharacterType::SOLDIER:
                    return std::shared_ptr<Character>
                            (new Soldier(team, health, ammo, range, power));

            }
        }

        void move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);

        void attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);

        void reload(const GridPoint &coordinates);

        friend std::ostream& operator<<(std::ostream& os, const Game& game);

        bool isOver(Team *winningTeam = nullptr) const;

        std::shared_ptr<Character> getCharacter(const GridPoint &dst_coordinates);
        int getWidth() const
        {
            return this->width;
        }
        int getHeigth() const
        {
            return this->height;
        }
    };
    std::ostream& operator<<(std::ostream& os, const Game& game)
    {
        std::string delimiter = std::string(2 * game.getWidth() + 1, '*');
        os << delimiter << std::endl;
        for(std::vector< std::shared_ptr<Character>> vec:*game.board)
        {
            for(std::shared_ptr<Character> character_ptr:vec)
            {
                if(character_ptr!= NULL)
                {
                    os<<(*character_ptr).getTeam();
                }
            }
        }
        os << delimiter;
        return os;
    }

}
#endif //SOLDIER_H_GAME_H
