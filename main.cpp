#include <header.h>
/*****************************************************************************
 *                                                                           *
 * BATTLESHIP                                                                *
 *                                                                           *
 * Create a program that simulates a game of battleship.                     *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * INPUT:                                                                    *
 *  playernum: Number of players.                                            *
 *  clear: Tells either continues the game or allows the user to re-place    *
 *      their ships.                                                         *
 *  rowshot (and variations): Row index of the ship (or shot).               *
 *  colshot (and variations): Column index of the shot (or shot).            *
 *  o (and variations): Orientation of the ship.                             *
 * FUNCTIONS:  (see header.h)                                                *
 *---------------------------------------------------------------------------*
 * OUTPUT: Outputs the updated boards with ships, hits, and misses.          *
 ****************************************************************************/
int main()
{
    ///Making sure the computer will not choose the same random numbers
    ///every time
    //srand(time(NULL));
    //ARRAYS: these arrays will hold the locations of the ships, whether they
        //have been hit, and any hits or misses that the player makes
    char shipfield1[10][10];
    char enemyfield1[10][10];
    char shipfield2[10][10];
    char enemyfield2[10][10];

    char clear;
    bool gamerunning = true;
    bool twoplayer = false;
    int playernum;

    PlayerBoard Player1;
    cout << "One or two players? ";
    cin >> playernum;
    if(playernum == 2)
        twoplayer = true;



    //system("CLS");
    do
    {

        initBoard(Player1, shipfield1, enemyfield1, PLAYER_ONE, false);


        //Giving the option to reset and start over if the player made a mistake
        do
        {

            cout << "Press 'c' key to clear the screen and allow Player 2 "
                    "to place ships, or type 'a' to reset your board and\n"
                    "place your ships again \n";
            cin >> clear;
            if(clear == 'c' || clear == 'a')
                break;
        }while(true);

    }while(clear == 'a');
    //system("CLS");


    if(twoplayer)
    {
        PlayerBoard Player2;
        do
        {
            //Function makes all the magic happen.
            //Initializes the board, asks for input, and displays the results
                //of the input
            initBoard(Player2, shipfield2, enemyfield2, PLAYER_TWO);

            //Giving the option to reset and start over if the
                //player made a mistake
            do
            {
                cout << "Press 'c' key to clear the screen and start the game"
                        ", or type 'a' to reset your board and\n"
                        "place your ships again \n";
                cin >> clear;
                if(clear == 'c' || clear == 'a')
                    break;
            }while(true);

        }while(clear == 'a');
        //system("CLS");

        int player = PLAYER_ONE;
        while(gamerunning)
        {
            //system("CLS");
            if(player == PLAYER_ONE)
            {
                //hitOrMiss function asks the computer if the player has hit a
                    //ship. If yes, then the results are given
                hitOrMiss(player, Player2, shipfield1, enemyfield1, shipfield2);
            }
            else if (player == PLAYER_TWO)
            {
                //hitOrMiss function asks the computer if the player has hit a
                    //ship. If yes, then the results are given
                hitOrMiss(player, Player1, shipfield2, enemyfield2, shipfield1);
            }

            //Switching players
            if (player == PLAYER_ONE)
                player = PLAYER_TWO;
            else if (player == PLAYER_TWO)
                player = PLAYER_ONE;

            if(gameWon(Player1))
            {
                cout << "Player 2 has sunk all of the ships.\n";
                cout << "Player 2 wins!!\n";
                gamerunning = false;
            }
            if(gameWon(Player2))
            {
                cout << "Player 1 has sunk all of the ships.\n";
                cout << "Player 1 wins!!\n";
                gamerunning = false;
            }
            //cin.get();
        }
    }
    else {
        PlayerBoard CPU;
        initBoard(CPU, shipfield2, enemyfield2, AI, true);
        int player = PLAYER_ONE;
        while(gamerunning)
        {
            //system("CLS");
            if(player == PLAYER_ONE)
            {
                //hitOrMiss function asks the computer if the player has hit a
                    //ship. If yes, then the results are given
                hitOrMiss(player, CPU, shipfield1, enemyfield1, shipfield2);
            }
            else if(player == AI)
            {
                //aiAttack function checks if the computer has hit a ship.
                    //It will also target surrounding spaces if it gets a hit
                aiAttack(Player1, enemyfield2, shipfield1);
            }

            //Switching players
            if (player == PLAYER_ONE)
                player = AI;
            else if (player == AI)
                player = PLAYER_ONE;


            if(gameWon(Player1))
            {
                cout << "The computer has sunk all of the ships.\n";
                cout << "The computer wins.\n";
                gamerunning = false;
            }

            if(gameWon(CPU))
            {
                cout << "You have sunk all of the ships.\n";
                cout << "You win!!\n";
                gamerunning = false;
            }
            //Pausing the screen
            //cin.get();
        }
    }
}
