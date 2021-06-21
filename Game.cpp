#include "Game.h"

const int HALF=2;
const int THIRD=3;
const int ROUND_UP=1;
const int DIVIDED=0;
const int EMPTY=0;
const char SPACE=' ';
namespace mtm {

    Game::Game(int height, int width) : height(height), width(width)
    {
        if(height<=0||width<=0)
        {
            throw IllegalArgument();
        }
        this->board=std::vector<std::vector<std::shared_ptr<Character>>>
                (height,std::vector<std::shared_ptr<Character>>(width,nullptr));
        // the game board. it is a vector of vectors. each cell has a shared_ptr. each pointer points to a character
    }

    Game::Game(const Game &other)
    {
        this->height = other.height;
        this->width = other.width;
        this->board = std::vector<std::vector<std::shared_ptr<Character>>>
                (height,std::vector<std::shared_ptr<Character>>(width,nullptr));
        for(int i=0;i<this->height;i++)
        {
            for(int j=0;j<this->width;j++)
            {
                if(other.board.at(i).at(j)!= nullptr) {
                    this->board.at(i).at(j) = other.board.at(i).at(j)->clone();
                }
            }
        }
    }

    Game &Game::operator=(const Game &other)
       {
        if (this == &other)//self assignment check.
        {
            return *this;
        }
        this->height = other.height;
        this->width = other.width;
        this->board = std::vector<std::vector<std::shared_ptr<Character>>>
                (height,std::vector<std::shared_ptr<Character>>(width,nullptr));
        //same game board as the builder
        for(int i=0;i<this->height;i++)
        {
            for(int j=0;j<this->width;j++)
            {
                if(other.board.at(i).at(j)!= nullptr)
                {
                    this->board.at(i).at(j) = other.board.at(i).at(j)->clone();
                    //duplicating the character in the current cell using the clone function
                }
            }
        }
        return *this;
    }

    void Game::addCharacter(const GridPoint &coordinates, std::shared_ptr<Character> character)
    {
        isIllegalCell(coordinates);
        if (this->board.at(coordinates.row).at(coordinates.col)!= nullptr)
            //if there is another character in the current cell
        {
            throw CellOccupied();
        }
        this->board.at(coordinates.row).at(coordinates.col) =character;
    }
    std::shared_ptr<Character> Game::getCharacter(const GridPoint &coordinates) const
    {
        return this->board.at(coordinates.row).at(coordinates.col);
    }

    void Game::move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates)
    {
        isIllegalCell(src_coordinates);
        isIllegalCell(dst_coordinates);
        if (this->board.at(src_coordinates.row).at(src_coordinates.col) == nullptr)
        {
            throw CellEmpty();//no character at the source location
        }

        int range =GridPoint::distance(src_coordinates,dst_coordinates);
        if (range > this->getCharacter(src_coordinates)->getMaxMove())
        {
            throw MoveTooFar();
        }
        if (this->board.at(dst_coordinates.row).at(dst_coordinates.col) != nullptr)//another character is at the cell
        {
            throw CellOccupied();
        }
        this->board.at(dst_coordinates.row).at(dst_coordinates.col) = this->getCharacter(src_coordinates);
        this->board.at(src_coordinates.row).at(src_coordinates.col) = nullptr;
    }//the move is legal so we move the character

    void Game::attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates)
    {
        isIllegalCell(src_coordinates);
        isIllegalCell(dst_coordinates);
        if (this->board.at(src_coordinates.row).at(src_coordinates.col) == nullptr)
        {
            throw CellEmpty();
        }
        int range = GridPoint::distance(src_coordinates, dst_coordinates);
        int char_range = this->getCharacter(src_coordinates)->getRange();
        if (range > char_range)
        {
            throw OutOfRange();//the source and destination is too far away
        }
        if (this->getCharacter(src_coordinates)->getLetter() == 'n' ||
            this->getCharacter(src_coordinates)->getLetter() == 'N')//the character is a sniper
        {
            if (range < (char_range / HALF) + ROUND_UP - (char_range % HALF == DIVIDED))//calculate the range round up
            {
                throw OutOfRange();
            }
        }
        std::shared_ptr<Character> character = getCharacter(src_coordinates);
        if (character->getAmmo() == EMPTY)//the character is out of ammo
        {
            throw OutOfAmmo();
        }
        switch (character->getLetter())
        {
            case 's':
            case 'S':
                {
                    attackAsSoldier(dst_coordinates, src_coordinates,character);//the attacking character is a soldier
                break;
            }
            case 'm':
            case 'M':
                {
                if(attackAsMedic(dst_coordinates, src_coordinates))//the attacking character is a medic
                {
                    return;//the medic has healed a player from the team. we don't want to drop ammo
                }
                break;
            }
            case 'n':
            case 'N':
                {
                attackAsSniper(dst_coordinates, src_coordinates);//the attacking character is a sniper
                break;
            }
        }
        character->lowerAmmo();
    }
    void Game::attackAsSoldier(GridPoint dst_coordinates,GridPoint src_coordinates,std::shared_ptr<Character> character)
    {
        int char_range = this->getCharacter(src_coordinates)->getRange();
        if(src_coordinates.col!=dst_coordinates.col&&src_coordinates.row!=dst_coordinates.row)
            //a soldier can attack only in straight lines
        {
            throw IllegalTarget();
        }
        int power = (character->getPower() / HALF) + ROUND_UP - (character->getPower() % HALF == DIVIDED);
        //the damage divided by 2 round up
        attackInSquare(dst_coordinates,character->getTeam(),character->getPower());//attacking in the destination block
        char_range = (char_range / THIRD) + ROUND_UP - (char_range % THIRD == DIVIDED);
        //the range divided by 3 round up
        for (int i = 0; i < this->height; i++)
        {
            for (int j = 0; j < this->width; j++)//we go over all of the board
            {
                if (j == dst_coordinates.col && i == dst_coordinates.row)
                    //we already attack at the destination. we don't want to strike again
                {
                    continue;
                }
                if (char_range >= GridPoint::distance(dst_coordinates, GridPoint(i, j)))
                {
                    attackInSquare(GridPoint(i, j),character->getTeam(),power);
                    //we strike in a certain block
                    //we will also check  the team and the distance fro the character in the block
                }
            }
        }
    }
    bool Game::attackAsMedic(GridPoint dst_coordinates,GridPoint src_coordinates)
    {
        if (getCharacter(dst_coordinates) == nullptr || dst_coordinates == src_coordinates)
            //if the destination cell is empty
        {
            throw IllegalTarget();
        }
        if (getCharacter(src_coordinates)->getTeam() == getCharacter(dst_coordinates)->getTeam())
        {//if they are from the same team
            this->getCharacter(dst_coordinates)->lowerHealth(-this->getCharacter
                    (src_coordinates)->getPower());//heal the player
            return true;
        }
        else
        {
            if (this->getCharacter(dst_coordinates)->lowerHealth(this->getCharacter
                    (src_coordinates)->getPower()))//they are enemies
            {
                this->board.at(dst_coordinates.row).at(dst_coordinates.col) = nullptr;//character is killed
            }
        }
        return false;
    }
    void Game::attackAsSniper(GridPoint dst_coordinates,GridPoint src_coordinates)
    {
        if (getCharacter(dst_coordinates) == nullptr || dst_coordinates == src_coordinates)
        {
            throw IllegalTarget();
        }
        if (getCharacter(src_coordinates)->getTeam() == getCharacter(dst_coordinates)->getTeam())
        {//the sniper can't attack a player from the same team
            throw IllegalTarget();
        }
        if (this->getCharacter(dst_coordinates)->lowerHealth(getCharacter(src_coordinates)->
                hitMultiplier() * getCharacter(src_coordinates)->getPower()))
            //checking if it is a third strike of the sniper
        {
            this->board.at(dst_coordinates.row).at(dst_coordinates.col) = nullptr;
        }
    }
    void Game::attackInSquare(GridPoint dst_coordinates, Team team, int power)
    {
        if (getCharacter(dst_coordinates)!= nullptr)//there is a character in the coordinates
        {
            if (team != getCharacter(dst_coordinates)->getTeam())//they are not from the same team
            {
                if (this->getCharacter(dst_coordinates)->lowerHealth(power))
                {
                    this->board.at(dst_coordinates.row).at(dst_coordinates.col) = nullptr;//if the character is killed
                }
            }
        }
    }
    void Game::reload(const GridPoint &coordinates)
    {
        isIllegalCell(coordinates);
        if (this->board.at(coordinates.row).at(coordinates.col) == nullptr)
        {
            throw CellEmpty();
        }
        (this->getCharacter(coordinates))->reload();
    }

    bool Game::isOver(Team *winningTeam) const
    {
        bool cross_found = false, power_found = false;
        for (const std::vector<std::shared_ptr<Character>>& vec:this->board)
        {
            for (const std::shared_ptr<Character>& character_ptr:vec)
            {
                if (character_ptr != nullptr)
                {
                    cross_found = cross_found || (*character_ptr).getTeam() == CROSSFITTERS;
                    power_found = power_found || (*character_ptr).getTeam() == POWERLIFTERS;
                }
            }
        }
        if (winningTeam != nullptr)
        {
            if (!power_found)
            {
                *winningTeam = CROSSFITTERS;
            }
            if (!cross_found)
            {
                *winningTeam = POWERLIFTERS;
            }
        }

        return !power_found==cross_found;
    }
    std::ostream& operator<<(std::ostream& os, const Game& game)
    {
        std::string str;
        str.resize(game.height * game.width);
        for (int i = 0; i < game.height; i++)
        {
            for (int j = 0; j < game.width; j++)
            {
                if(game.board.at(i).at(j)== nullptr)
                {
                    str[i*game.width+j]=SPACE;
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