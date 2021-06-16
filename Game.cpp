#include "Game.h"
#include <cmath>
namespace mtm {
    Game::Game(int height, int width) : height(height), width(width) {
        this->board = new std::vector<std::vector<std::shared_ptr<Character>>>;
        this->board->resize(height);
        for(int i=0;i<height;i++)
        {
            this->board->at(i).resize(width);
        }
    }

/*Game::~Game()
{

for(std::vector<Character> vec:*this->board)
    {
       delete vec;
    }
}*/
    Game::Game(const Game &other)
    {
        this->height = other.height;
        this->width = other.width;
        this->board = new std::vector<std::vector<std::shared_ptr<Character>>>;
        this->board->resize(height);
        for(int i=0;i<height;i++)
        {
            this->board->at(i).resize(width);
        }
        for(int i=0;i<this->height;i++)
        {
            for(int j=0;j<this->width;j++)
            {
                if(other.board->at(i).at(j)!= nullptr) {
                   *this->board->at(i).at(j) = *other.board->at(i).at(j)->clone();//////
                }
            }
        }
    }

    Game &Game::operator=(const Game &other) {
        if (this == &other) {
            return *this;
        }
        delete this;
        this->height = other.height;
        this->width = other.width;
        this->board = new std::vector<std::vector<std::shared_ptr<Character>>>;
        this->board->resize(height);
        for(int i=0;i<height;i++)
        {
            this->board->at(i).resize(width);
        }
        for(int i=0;i<this->height;i++)
        {
            for(int j=0;j<this->width;j++)
            {
                if(other.board->at(i).at(j)!= nullptr) {
                    *this->board->at(i).at(j) = *other.board->at(i).at(j)->clone();
                }
            }
        }
        return *this;
    }

    void Game::addCharacter(const GridPoint &coordinates, std::shared_ptr<Character> character)
    {
        isIllegalCell(coordinates);
        if (this->board->at(coordinates.row).at(coordinates.col)!= nullptr)
        {
            throw CellOccupied();
        }
        this->board->at(coordinates.row).at(coordinates.col) = character;
    }

    std::shared_ptr<Character> Game::getCharacter(const GridPoint &coordinates) const
    {
        return this->board->at(coordinates.row).at(coordinates.col);
    }

    void Game::move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates)
    {
        isIllegalCell(src_coordinates);
        isIllegalCell(dst_coordinates);
        if (this->board->at(src_coordinates.row).at(src_coordinates.col) == nullptr)
        {
            throw CellEmpty();
        }

        int range =GridPoint::distance(src_coordinates,dst_coordinates);
        if (range > this->getCharacter(src_coordinates)->getMaxMove())
        {
            throw MoveTooFar();
        }
        if (this->board->at(dst_coordinates.row).at(dst_coordinates.col) != nullptr)
        {
            throw CellOccupied();
        }
        this->board->at(dst_coordinates.row).at(dst_coordinates.col) = this->getCharacter(src_coordinates);
        this->board->at(src_coordinates.row).at(src_coordinates.col) = nullptr;
    }

    void Game::attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates)
    {
        isIllegalCell(src_coordinates);
        isIllegalCell(dst_coordinates);
        if (this->board->at(src_coordinates.row).at(src_coordinates.col) == nullptr)
        {
            throw CellEmpty();
        }
        int range =GridPoint::distance(src_coordinates,dst_coordinates);
        int char_range=this->getCharacter(src_coordinates)->getRange();
        if (range > char_range)
        {
            throw OutOfRange();
        }
        if(this->getCharacter(src_coordinates)->getLetter()=='n'||this->getCharacter(src_coordinates)->getLetter()=='N')
        {
            if(range<char_range/2+(char_range%2==1))
            {
                throw OutOfRange();
            }

        }

        std::shared_ptr<Character> character = getCharacter(src_coordinates);
        if (character->getAmmo() == 0) {
            throw OutOfAmmo();
        }

        int power = (character->getPower() / 2) +1- (character->getPower() % 2 == 0);
        switch (character->getLetter()) {
            case 's':
            case 'S':
                {
                    if(dst_coordinates.row != src_coordinates.row && dst_coordinates.col != src_coordinates.col)
                    {
                        throw IllegalTarget();
                    }
                Game::attackInSquare(GridPoint(dst_coordinates), character->getTeam(), character->getPower());
                range = (range / 3 -(range % 3 == 0));
                for (int i = dst_coordinates.row- range; i < dst_coordinates.row + range; i++) {
                    for (int j = dst_coordinates.col - range; j < dst_coordinates.col + range; j++) {
                        if(j==dst_coordinates.col&&i==dst_coordinates.row)
                        {
                            continue;
                        }
                        Game::attackInSquare(GridPoint(i, j),
                                             character->getTeam(), power);
                    }
                }
                Game::attackInSquare(GridPoint(dst_coordinates.row + range +1, dst_coordinates.col),
                                     character->getTeam(), power);
                Game::attackInSquare(GridPoint(dst_coordinates.row - range -1, dst_coordinates.col),
                                     character->getTeam(), power);
                Game::attackInSquare(GridPoint(dst_coordinates.row, dst_coordinates.col + range +1),
                                     character->getTeam(), power);
                Game::attackInSquare(GridPoint(dst_coordinates.row, dst_coordinates.col - range -1),
                                     character->getTeam(), power);
                break;
            }
            case 'm':
            case 'M': {
                if (getCharacter(dst_coordinates) == nullptr||dst_coordinates==src_coordinates)
                {
                    throw IllegalTarget();
                }
                if (character->getTeam() == getCharacter(dst_coordinates)->getTeam())
                {
                    this->getCharacter(dst_coordinates)->lowerHealth(-power);
                }
                else
                    {
                    Game::attackInSquare(dst_coordinates, character->getTeam(), power);
                }
                break;
            }
            case 'n':
            case 'N': {
                if (getCharacter(dst_coordinates) == nullptr)
                {
                    throw IllegalTarget();
                }
                if (character->getTeam() == getCharacter(dst_coordinates)->getTeam())
                {
                    throw IllegalTarget();
                }
                Game::attackInSquare(dst_coordinates, character->getTeam(),
                                     getCharacter(src_coordinates)->hitMultiplier()*
                                     getCharacter(src_coordinates)->getPower());

                break;
            }
        }
        character->lowerAmmo();

    }

    void Game::attackInSquare(GridPoint dst_coordinates, Team team, int power) {
        if (dst_coordinates.col >= 0 && this->width > dst_coordinates.col
            && dst_coordinates.row >= 0 && this->height > dst_coordinates.row&&getCharacter(dst_coordinates)!= nullptr)
        {
            if (team != getCharacter(dst_coordinates)->getTeam()) {
                if (this->getCharacter(dst_coordinates)->lowerHealth(power)) {
                    this->board->at(dst_coordinates.row).at(dst_coordinates.col) = nullptr;
                }
            }
        }
    }

    void Game::reload(const GridPoint &coordinates) {
        isIllegalCell(coordinates);
        if (this->board->at(coordinates.row).at(coordinates.col) == nullptr) {
            throw CellEmpty();
        }
        (*this->getCharacter(coordinates)).reload();
    }

    bool Game::isOver(Team *winningTeam) const {
        bool cross_found = false, power_found = false;
        for (std::vector<std::shared_ptr<Character>> vec:*this->board) {
            for (std::shared_ptr<Character> character_ptr:vec) {
                if (character_ptr != nullptr) {
                    cross_found = cross_found || (*character_ptr).getTeam() == CROSSFITTERS;
                    power_found = power_found || (*character_ptr).getTeam() == POWERLIFTERS;
                }
            }
        }
        if (winningTeam != nullptr) {
            if (!power_found) {
                *winningTeam = CROSSFITTERS;
            }
            if (!cross_found) {
                *winningTeam = POWERLIFTERS;
            }
        }
        return (!power_found) || (!cross_found);
    }
    std::ostream& operator<<(std::ostream& os, const Game& game)
    {
        std::string str;
        str.resize(game.height * game.width);
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