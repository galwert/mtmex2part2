#include "Game.h"

using namespace mtm;
Game::Game(int height, int width) :height(height),width(width)
{
    this->board=new std::vector<std::vector<std::shared_ptr<Character>>>;
    this->board->resize(width);
    for(std::vector< std::shared_ptr<Character>> vec:*this->board)
    {
        vec.resize(height);////////////
    }
}
/*Game::~Game()
{

for(std::vector<Character> vec:*this->board)
    {
       delete vec;
    }
}*/
Game::Game(const Game& other)
{
    this->height=other.height;
    this->width=other.width;
    this->board=other.board;
}
Game& Game::operator=(const Game& other)
{
    this->height=other.height;
    this->width=other.width;
    this->board=other.board;
    return *this;
}
void Game::addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character)
{
    this->board->at(coordinates.col).at(coordinates.row)=character;
}

std::shared_ptr<Character> Game::getCharacter(const GridPoint &coordinates)
{
    return this->board->at(coordinates.col).at(coordinates.row);
}
void Game::move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
{
    this->board->at(dst_coordinates.col).at(dst_coordinates.row)=this->getCharacter(src_coordinates);
    this->board->at(src_coordinates.col).at(src_coordinates.row)= nullptr;/////////////
}
void  Game::attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates)
{
    std::shared_ptr<Character> character=getCharacter(src_coordinates);
    switch (character->getLetter()) {
    case 's':case 'S':
        if(this->getCharacter(dst_coordinates)->lowerHealth(character->getPower()))
        {
            getCharacter(dst_coordinates)= nullptr;
        }
        for(int i=0)///////////
        break;
    }
}
void Game::reload(const GridPoint & coordinates)
{
    (*this->getCharacter(coordinates)).reload();
}

bool Game::isOver(Team* winningTeam) const
{
    bool cross_found= false,power_found= false;
    for(std::vector< std::shared_ptr<Character>> vec:*this->board)
    {
       for(std::shared_ptr<Character> character_ptr:vec)
       {
           if(character_ptr!= NULL)
           {
               cross_found=cross_found||(*character_ptr).getTeam()==CROSSFITTERS;
               power_found=power_found||(*character_ptr).getTeam()==POWERLIFTERS;
           }
       }
    }
    if(winningTeam!=NULL)
    {
        if(!power_found)
        {
            *winningTeam=POWERLIFTERS;
        }
        if(!cross_found)
        {
            *winningTeam=CROSSFITTERS;
        }
    }
    return (!power_found)||(!cross_found);
}
