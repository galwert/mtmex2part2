

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
        /**
 * Game: build a new game board
 *
 * @param height - the height of the board. must be positive
 * @param width - the height of the board. must be positive
 *
 * @throw IllegalArgument- if the height or widht are not positive
 * @return
         * a new game board.
 */
        Game(int height, int width);
/**
* ~Game: destruct the current game
*/
        ~Game()=default;
        /**
        * Game: copy constructor
        *
        * @param
         * other - a different game to be copied
        *
        * @return
                * a new game board with the same state as the first
        */
        Game(const Game &other);
        /**
        * Game: opertaor=
        *
        * @param
         * other - a different game to be copied
        *
        * @return
                * a new game board with the same state as the first
        */
        Game &operator=(const Game &other);

        /**
* addCharacter: add a new character to the game board
*
* @param coordinates - the place we would like to the character to.
* @param character - a shared_ptr pointing to the data of the character we would like to add
*
* @throw IllegalArgument- if the height or width are not positive
* @return
        * a new game board.
*/

        void addCharacter(const GridPoint &coordinates, std::shared_ptr<Character> character);

        /**
* makeCharacter: create a new shared pointer that points to a character
*
* @param type - the type of the character
        * team - the team of the character
        * health - the health of the character. must be a positive number
        * ammo - the ammo of the character/ must be 0 or positive
        * range - the range of the character. must be 0 or positive
        * power- the power of the character. must be 0 or positive
*
* @throw IllegalArgument- if one of the parameters are smaller than zero or the health is 0.
* @return
        * a new game board.
*/
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

        /**
* move: move a character from the src-coordinates to dst_coordinates
*
* @param src_coordinates - the place of the character we would like to move
        * dst_coordinates - the place we would like to move the character to
*
* @throw CellEmpty- if there is no character in the src_coordinates.
         * MoveTooFar- if the coordinates are too far to move the character
         * CellOccupied- if there is a character in the dst_coordinates
         *
* @return
        * a new game board.
   */

        void move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);


        /**
* attack: attack with the character in src_coordinates the square dst_coordinates
*
* @param src_coordinates - the place of the character we would like attack with
* dst_coordinates - the place we would like to attack with the character
*
* @throw IllegalCell- if one of the coordinates points to a cell outside of the game board
 * CellEmpty- if there is no character in the src_coordinates.
 * OutOfRange- if the coordinates are too far away. the distance is larger than the character range
 * OutOfAmmo- if the character in the src_coordinates is out of ammo
 *
* @return
* a new game board.
*/
        void attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);

        /**
* attackAsSniper: attack with a character of type sniper in src_coordinates the square dst_coordinates
*
* @param src_coordinates - the place of the character we would like attack with
* dst_coordinates - the place we would like to attack with the character
*
* @throw IllegalTarget- a sniper cannot attack himself, his teammate or an empty square
*
* @return
* a new game board.
*/

        void attackAsSniper(GridPoint dst_coordinates,GridPoint src_coordinates);

        /**
* attackAsMedic: attack with a character of type medic in src_coordinates the square dst_coordinates
*
* @param src_coordinates - the place of the character we would like attack with
* dst_coordinates - the place we would like to attack with the character
*
* @throw OutOfAmmo- the medic tries to attack an enemy character and has no ammo
         * IllegalTarget- a medic cannot attack himself or an empty square
*
* @return
* a new game board.
*/
        bool attackAsMedic(GridPoint dst_coordinates,GridPoint src_coordinates);

        /**
* reload: the character reloads according to the character rules
*
* @param coordinates - the place of the character we would like reload with
*
* @throw IllegalCell- if the coordinates points to a cell outside of the game board
         * CellEmpty- there is no character in the cell
*
* @return
* a new game board.
*/
        void reload(const GridPoint &coordinates);

        /**
* attackAsSoldier: attack with a character of type soldier in src_coordinates the square dst_coordinates
*
* @param src_coordinates - the place of the character we would like attack with
* dst_coordinates - the place we would like to attack with the character
*
* @throw IllegalTarget- a soldier can only attack a cell in the same row or column
*
* @return
* a new game board.
*/

        void attackAsSoldier(GridPoint dst_coordinates,GridPoint src_coordinates,std::shared_ptr<Character> character);

        /**operator<<: print the game board
         * @param os: the output stream we would like to print to
         *game: the game we would like to print it's status
         *
         * @return the newly updated output stream
         */
        friend std::ostream& operator<<(std::ostream& os, const Game& game);

        /**
         *
         * @param winningTeam a pointer to Team where we will save the winning team. can be null
         *
         * @return true if there character of only one team
         * false if the board is empty or both team have characters on the board
         */
        bool isOver(Team *winningTeam = nullptr) const;
        /**
         * getCharacter: getting a shared_ptr to the character on the board
         * @param dst_coordinates- the coordinates we would like to get the character from
         */
        std::shared_ptr<Character> getCharacter(const GridPoint &dst_coordinates) const;
        /**
         *
         * attackInSquare- lower the helath or kill the character in the dst_coordinates
         * @param dst_coordinates - the place of the character we would like attack
         *          team- the team of the attacking character
         *          power- the amount of health to drop
         *
         */
        void attackInSquare(GridPoint dst_coordinates,Team team,int power);

        /**
         * isIllegalCell: checks if the coordinates point to a legal cell in the game board
         * @param coordinates: the coordinates we would like to check
         *
         * @throw IllegalCell: the cell we checked is illegal
         */
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
