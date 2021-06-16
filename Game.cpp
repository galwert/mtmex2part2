#include "Game.h"
#include <cmath>
namespace mtm {
    Game::Game(int height, int width) : height(height), width(width) {
        this->board = new std::vector<std::vector<std::shared_ptr<Character>>>;
        this->board->resize(width);
        for (std::vector<std::shared_ptr<Character>> vec:*this->board) {
            vec.resize(height);
        }
    }

/*Game::~Game()
{

for(std::vector<Character> vec:*this->board)
    {
       delete vec;
    }
}*/
    Game::Game(const Game &other) {
        this->height = other.height;
        this->width = other.width;
        this->board = other.board;
    }

    Game &Game::operator=(const Game &other) {
        if (this == &other) {
            return *this;
        }
        delete this;
        this->height = other.height;
        this->width = other.width;
        this->board = other.board;
        return *this;
    }

    void Game::addCharacter(const GridPoint &coordinates, std::shared_ptr<Character> character) {
        isIllegalCell(coordinates);
        if (this->board->at(coordinates.col).at(coordinates.row) != nullptr) {
            throw CellOccupied();
        }
        this->board->at(coordinates.col).at(coordinates.row) = character;
    }

    std::shared_ptr<Character> Game::getCharacter(const GridPoint &coordinates) const {
        return this->board->at(coordinates.col).at(coordinates.row);
    }

    void Game::move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates) {
        isIllegalCell(src_coordinates);
        isIllegalCell(dst_coordinates);
        if (this->board->at(src_coordinates.col).at(src_coordinates.row) == nullptr) {
            throw CellEmpty();
        }
        int range = abs(src_coordinates.col - dst_coordinates.col) + abs(src_coordinates.row - dst_coordinates.row);
        if (range > this->getCharacter(src_coordinates)->getMaxMove()) {
            throw MoveTooFar();
        }
        if (this->board->at(dst_coordinates.col).at(dst_coordinates.row) == nullptr) {
            throw CellOccupied();
        }
        this->board->at(dst_coordinates.col).at(dst_coordinates.row) = this->getCharacter(src_coordinates);
        this->board->at(src_coordinates.col).at(src_coordinates.row) = nullptr;
    }

    void Game::attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates) {
        isIllegalCell(src_coordinates);
        isIllegalCell(dst_coordinates);
        if (this->board->at(src_coordinates.col).at(src_coordinates.row) == nullptr) {
            throw CellEmpty();
        }
        int range = abs(src_coordinates.col - dst_coordinates.col) + abs(src_coordinates.row - dst_coordinates.row);
        if (range > this->getCharacter(src_coordinates)->getRange()) {
            throw OutOfRange();
        }
        if (this->board->at(dst_coordinates.col).at(dst_coordinates.row) == nullptr) {
            throw CellOccupied();
        }
        std::shared_ptr<Character> character = getCharacter(src_coordinates);
        if (character->getAmmo() == 0) {
            throw OutOfAmmo();
        }
        int power = (character->getPower() / 2) + (character->getPower() % 2 == 0);
        switch (character->getLetter()) {
            case 's':
            case 'S': {
                Game::attackInSquare(GridPoint(dst_coordinates), character->getTeam(), power);
                int char_range = (int) fmax(abs(src_coordinates.col - dst_coordinates.col),
                                            abs(src_coordinates.row - dst_coordinates.row));
                char_range = (char_range / 3 + 1 - (char_range % 3 == 0)) / 2;
                for (int i = dst_coordinates.col - char_range; i < dst_coordinates.col + char_range; i++) {
                    for (int j = dst_coordinates.row - char_range; j < dst_coordinates.row + char_range; j++) {
                        Game::attackInSquare(GridPoint(i, j),
                                             character->getTeam(), power);
                    }
                }
                Game::attackInSquare(GridPoint(dst_coordinates.col + char_range * 2, dst_coordinates.row),
                                     character->getTeam(), power);
                Game::attackInSquare(GridPoint(dst_coordinates.col - char_range * 2, dst_coordinates.row),
                                     character->getTeam(), power);
                Game::attackInSquare(GridPoint(dst_coordinates.col, dst_coordinates.row + char_range * 2),
                                     character->getTeam(), power);
                Game::attackInSquare(GridPoint(dst_coordinates.col, dst_coordinates.row - char_range * 2),
                                     character->getTeam(), power);
                break;
            }
            case 'm':
            case 'M': {
                if (getCharacter(dst_coordinates) == nullptr) {
                    throw CellEmpty();
                }
                if (character->getTeam() == getCharacter(dst_coordinates)->getTeam()) {
                    this->getCharacter(dst_coordinates)->lowerHealth(-power);
                } else {
                    Game::attackInSquare(dst_coordinates, character->getTeam(), power);
                }
                break;
            }
            case 'n':
            case 'N': {
                if (getCharacter(dst_coordinates) == nullptr) {
                    throw CellEmpty();
                }
                Game::attackInSquare(dst_coordinates, character->getTeam(), power);
                break;
            }
        }
        character->lowerAmmo();

    }

    void Game::attackInSquare(GridPoint dst_coordinates, Team team, int power) {
        if (dst_coordinates.col >= 0 && this->width < dst_coordinates.col
            && dst_coordinates.row >= 0 && this->height < dst_coordinates.row) {
            if (team != getCharacter(dst_coordinates)->getTeam()) {
                if (this->getCharacter(dst_coordinates)->lowerHealth(power)) {
                    getCharacter(dst_coordinates) = nullptr;
                }
            }
        }
    }

    void Game::reload(const GridPoint &coordinates) {
        isIllegalCell(coordinates);
        if (this->board->at(coordinates.col).at(coordinates.row) == nullptr) {
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
                *winningTeam = POWERLIFTERS;
            }
            if (!cross_found) {
                *winningTeam = CROSSFITTERS;
            }
        }
        return (!power_found) || (!cross_found);
    }
}