#ifndef HEADER_H
#define HEADER_H

#endif // HEADER_H

#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <random>

using namespace std;

///Sizes of all the ships
const int CARRIER = 5;
const int BATTLESHIP = 4;
const int CRUISER = 3;
const int SUBMARINE = 3;
const int DESTROYER = 2;

const int FLEET_SIZE = 5;

///Values representing whose turn it is to play
const int PLAYER_ONE = 0;
const int PLAYER_TWO = 1;
const int AI = 3;


///Point struct stores the row and column index of a point
struct Point
{
    int row;
    int column;
};
///Ship struct stores the name and size of the ship as well as the number of
///times it has been hit. Also stores whether or not it has been destroyed
///and the number of spaces it occupies
struct Ship
{
    string name;
    int size;
    int hitcount;
    vector <Point> spaces;
    bool destroyed;
};
///Stores the board and fleet of ships for a player
struct PlayerBoard
{
    char board[10][10];
    Ship fleet[FLEET_SIZE];
};

///Displays the boards
void displayBoards(char[][10],  //Your ships
                   char[][10]); //Enemy ships

///Checks if the space has a 's' in the index of the array
bool spaceOccupied(PlayerBoard board,   //Set of ships
                    int row,            //Row to test
                    int col,            //Column to test
                    char o,             //Orientation, which determines futher
                                            //rows to test
                    Ship ship,          //Size of ship
                    char field[][10]);  //Array of battlefield

///Sets the names, sizes, and hitcounts for all ships
void initFleet(PlayerBoard& board);     //Set of ships

///Sets the ships on the board
vector<Point> setShip(PlayerBoard board,  //Array of the battlefield
                  Ship ship,     //Type of ship
                  char[][10],    //Board
                  int&,          //Row index
                  int&,          //Column index
                  char&);        //Orientation

///Generates random numbers and sets the ships on the board
vector <Point> setShipAI(PlayerBoard board,     //Array of the battlefield
                         Ship ship,             //Type of ship
                         char field[][10],      //Field of ships
                         char& o,                //Orientation of the ship
                         int& row,               //Row index of the ship
                         int& column);           //Column index of the ship

///Checks if the location of the placed ship is valid
void getValidShipInfo(int& row,         //Row index of the ship
                      int& column,      //Column index of the ship
                      char& o,          //Orientation of the ship
                      PlayerBoard board,//Set of ships
                      Ship ship,        //Type of ship
                      char[][10]);      //Array of battlefield

///Initializes the fleet and sets ships on board
void initBoard(PlayerBoard&,    //Set of ships
               char[][10],      //Array of your ships
               char[][10],      //Array of enemy ships
               int player,      //Player
               bool ai = false);//Tells whether or not an ai is playing

///Checks if the player scored a hit or a miss
void hitOrMiss(int player,      //Player 1 or 2
               PlayerBoard&,    //Set of ships for the player
               char[][10],      //player's set of ships
               char[][10],      //player's array of shots
               char[][10]);     //Opponent's board

///Checks if the game has been won by a player
bool gameWon(PlayerBoard);      //Set of ships

///Generates random numbers to attack the other player. If it hits a ship, it
///targets surrounding coordinates, continuing until it gets a miss
void aiAttack(PlayerBoard& oppships,        //Opponents ships
              char enemyshotfield[][10],    //Array of hits and misses
              char enemyshipfield[][10]);   //Opponent's ships

