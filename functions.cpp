#include <header.h>

//Displays the boards
void displayBoards(char board1[][10],   //Player's board
                    char board2[][10])  //Enemy's board
{
    cout << "                  Your Board";
    cout << "                                          Enemy Board\n";
    cout << "    1   2   3   4   5   6   7   8   9  10             ";
    cout << "    1   2   3   4   5   6   7   8   9  10\n";
    cout << "  -----------------------------------------";
    cout << "             -----------------------------------------\n";
    ///Loop outputting the contents of the boards
    for (int i = 0; i < 10; i++)
    {
        ///Outputting the row indicator
        cout << static_cast<char>(toupper('a' + i));
        ///Outputting the contents of the player's board
        for (int j = 0; j < 10; j++)
        {
             cout <<  " | " << board1[i][j];

        }
        cout << " |           ";
        ///Outputting the row indicator
        cout << static_cast<char>(toupper('a' + i));
        ///Outputting the contens of the enemy board
        for (int j = 0; j < 10; j++)
        {
             cout << " | " << board2[i][j];

        }
        cout << " |\n";
        cout << "  -----------------------------------------";
        cout << "             -----------------------------------------\n";

    }
}
//Takes in the user input for the location of the ship then sets it on the board
vector<Point> setShip(PlayerBoard board,  //Array of the battlefield
                  Ship ship,     //Type of ship
                  char field[][10])
{
    char o;     //Orientation of the ship
    int row;    //Row location of the ship
    int column; //Column location of the ship

    getValidShipInfo(row, column, o, board, ship, field);
    if(o == 'h')
    {
        //Off-by-one error when working with columns
        //Loop to go through the size of the ship and add the points it
            //contains to the struct
        for (int i = column; i < ship.size + (column); i++)
        {
            Point p = {row, i};
            ship.spaces.push_back(p);
            //Making the space where the ship occupies hold an 's'
            field[row][i] = 's';
        }
    }
    if(o == 'v')
    {
        //Loop to go through the size of the ship and add the points it
            //contains to the struct
        for (int i = row; i < ship.size + row; i++)
        {
            Point p = {i, column};
            ship.spaces.push_back(p);
            //Making the space where the ship occupies hold an 's'
            field[i][column] = 's';
        }
    }
    return ship.spaces;

}
//setShip but modified for no user input
vector <Point> setShipAI(PlayerBoard board,     //Array of the battlefield
                         Ship ship,             //Type of ship
                         char field[][10],      //Field of ships
                         char& o,                //Orientation of the ship
                         int& row,               //Row index of the ship
                         int& column)            //Column index of the ship
{


    bool occupied;  //Checks if the space is occupied
    bool isout;     //Checks if the space is out of the board
    int rrow;       //Random row index
    int rcol;       //Random column index
    int ro;         //Random orientation
    char ro2;       //ro converted to a character
    do
    {
        isout = false;

        //Choosing random numbers
        rrow = rand() % 10;
        rcol = rand() % 10;
        ro = rand() % 2;

        //Assigning ro2 to the correct variable
        if (ro == 0)
            ro2 = 'h';
        else if(ro == 1)
            ro2 = 'v';

//        cout << "In setShipAI" << endl;
//        cout << "Orientation = " << ro2 << endl;
//        cout << "Row = " << rrow << endl;
//        cout << "Column = " << rcol << endl;

        occupied = spaceOccupied(board, rrow, rcol, ro2, ship, field);

//        cout << "Occupied = " << occupied << endl;
        if(ro2 == 'h' && ship.size > 10 - rcol)
        {
            isout = true;
        }
        if(ro2 == 'v' && ship.size > 10 - rrow)
        {
            isout = true;
        }
//        cout << "isout = " << endl;
    }while(occupied || isout);


    if(ro2 == 'h')
    {
        //Loop to go through the size of the ship and add the points it
            //contains to the struct
        for (int i = rcol; i < ship.size + rcol; i++)
        {
            Point p = {rrow, i};
            ship.spaces.push_back(p);
            //Making the space where the ship occupies hold an 's'
            field[rrow][i] = 's';
        }
    }
    if(ro2 == 'v')
    {

        //Loop to go through the size of the ship and add the points it
            //contains to the struct
        for (int i = rrow; i < ship.size + rrow; i++)
        {
            Point p = {i, rcol};
            ship.spaces.push_back(p);
            //Making the space where the ship occupies hold an 's'
            field[i][rcol] = 's';
        }
    }
    return ship.spaces;
}
//Makes sure that the ship is in bounds and doesn't overlap with another ship
void getValidShipInfo(int& row,         //Row index of the ship
                      int& column,      //Column index of the ship
                      char& o,          //Orientation of the ship
                      PlayerBoard board,//Array of the battlefield
                      Ship ship,        //Type of ship
                      char field[][10]) //Field of ships
{
    bool isout;      //Checks if the ship is in the board
    bool occupied;  //Checks if a space is already occupied
    do{
        isout = false;
        char roww;
        cout << "Enter the starting coordinates of your " << ship.name << ": ";
        cin >> roww >> column;

        ///Setting the values of row and column to the index values in order
            ///to return them
        roww = static_cast<int>(toupper(roww));
        row = (roww)-65;
        column--;
        //cout << row << endl;
        cout << "\nEnter the orientation of your " << ship.name
             << " (horizontal(h) or vertical(v)): \n";
        cin >> o;


        ///Checking if the position of the ship results in it overlapping with
            ///another ship
        occupied = spaceOccupied(board, row, column, o, ship, field);
        //cout << "We got past spaceOccupied";

        if(occupied)
            cout << "Error: Space already occupied.\n";


        ///Checks if the position of the ship results in it being outside
            ///the board

        if(row > 9 || column > 9)
        {
            isout = true;
            cout << "Error: Ship placement is outside the board.\n";
        }
        if(o == 'h' && ship.size > 10 - (column))
        {
            isout = true;
            cout << "Error: Ship placement is outside the board.\n";
        }
        if(o == 'v' && ship.size > 10 - row)
        {
            isout = true;
            cout << "Error: Ship placement is outside the board.\n";
        }


    ///Loop will continue if the positions of the boat result in it overlapping
        ///with another ship or going outside the board
    }while(occupied || isout);
}
//Checks if the space is already occupied by a ship
bool spaceOccupied(PlayerBoard board,   //Array of the battlefield
                    int row,            //Row to test
                    int col,            //Column to test
                    char o,             //Orientation, which determines futher
                                            //rows to test
                    Ship ship,           //Size of ship
                    char field[][10])
{
    //cout << "We got to spaceOccupied" << endl;
    ///Function will return true if any space given does not contain a space
    if(o == 'h')
    {
        for(unsigned j = col; j < ship.size + col; j++)
        {
            //cout << "Inside second for loop. Horizontal" << endl;
            if(field[row][j] == 's')
            {
                //cout << "Returning true" << endl;
                return true;
            }
        }
    }
    ///Function will return true if any space given does not contain a space
    else if(o == 'v')
    {
        for(unsigned j = row; j < ship.size + row; j++)
        {
            //cout << "Inside second for loop" << endl;
            if(field[j][col] == 's')
            {
                return true;
            }
        }
    }
    ///Function will only return false if every space is empty
    return false;
}

//Initializes the fleet
void initFleet(PlayerBoard& board)  //Ships
{
    board.fleet[0] = {"carrier", 5, 0};
    board.fleet[1] = {"battleship", 4, 0};
    board.fleet[2] = {"cruiser", 3, 0};
    board.fleet[3] = {"submarine", 3, 0};
    board.fleet[4] = {"destroyer", 2, 0};
}
//Initializes the board
void initBoard(PlayerBoard& Player,     //Set of ships
               char shipfield[][10],    //Your map of ships
               char enemyfield[][10],   //Enemy map of ships
               int player,              //Player whose turn it is
               bool ai)
{
    initFleet(Player);

    //Resetting all the maps
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            shipfield[i][j] = ' ';
            enemyfield[i][j] = ' ';
        }
    }
    if(player == 3)
    {

        for(int i = 0; i < FLEET_SIZE; i++)
        {
            char ro2;
            int rrow;
            int rcol;
            Player.fleet[i].spaces = setShipAI(Player,
                                               Player.fleet[i],
                                               shipfield, ro2, rrow, rcol);
            displayBoards(shipfield, enemyfield);
        }

    }
    else
    {
        for(int i = 0; i < FLEET_SIZE; i++){
            cout << "Player " << player + 1 << " set your board.\n";
            displayBoards(shipfield, enemyfield);

            //Locations of the ships are stored in the playerboard struct
            Player.fleet[i].spaces =
                    setShip(Player, Player.fleet[i], shipfield);
        }
    }
    displayBoards(shipfield, enemyfield);
}
//Checks if the index is a hit or miss
void hitOrMiss(int player,      //Player whose turn it is
               PlayerBoard& oppships,    //Opponent's playerboard
               char yourshipfield[][10],    //Your field of ships
               char enemyshotfield[][10],   //Your hits and misses
               char enemyshipfield[][10])   //Enemy's field of ships

{
    char rowwshot;      //Temporary value that stores the row index
    int rowshot;        //Row value that is passed into the arrays
    int colshot;        //Column value that is passed into the arrays
    bool chosen;        //Tells the computer if a shot is valid or not
    displayBoards(yourshipfield, enemyshotfield);
    cout << "Player " << player + 1 << ":" << endl;
    do
    {
        chosen = false;
        cout << "Fire a shot: ";
        cin >> rowwshot >> colshot;
        //Converting the user coordinates into coordinates that the computer
            //can read
        rowwshot = static_cast<int>(toupper(rowwshot));
        //Getting rid of off-by-one errors
        rowshot = (rowwshot)-65;
        colshot--;

        //cout << rowshot << endl;
        //cout << colshot << endl;


        //Making sure that the shots entered are valid
        if(rowshot > 9 || colshot > 9)
        {
            cout << "Invalid\n";
            chosen = true;
        }
        else if(rowshot < 0 || colshot < 0)
        {
            cout << "Invalid\n";
            chosen = true;
        }
        else if(enemyshotfield[rowshot][colshot] == 'H' ||
                enemyshotfield[rowshot][colshot] == 'M')
        {
            cout << "You have already chosen that spot.\n";
            chosen = true;
        }

    //Loop will continue until the user chooses a valid guess
    }while(chosen);

    bool hit = false;
    for(unsigned i = 0; i < FLEET_SIZE; i++)
    {
        for (unsigned j = 0; j < oppships.fleet[i].size; j++)
        {
            if(oppships.fleet[i].spaces.at(j).row == rowshot &&
                    oppships.fleet[i].spaces.at(j).column == colshot)
            {
                cout << "Hit!!!\n";
                hit = true;
                //cout << "i = " << i << endl;
                //cout << "j = " << j << endl;
                enemyshotfield[rowshot][colshot] = 'H';
                enemyshipfield[rowshot][colshot] = 'H';
                oppships.fleet[i].hitcount++;
                if(oppships.fleet[i].hitcount == oppships.fleet[i].size)
                {
                    oppships.fleet[i].destroyed = true;
                    cout << "You sunk the " << oppships.fleet[i].name
                         << "!!!\n";
                }
            }
        }
    }
    if(!hit)
    {
        cout << "You missed.\n";
        enemyshotfield[rowshot][colshot] = 'M';
        enemyshipfield[rowshot][colshot] = 'M';
    }
    displayBoards(yourshipfield, enemyshotfield);
    //cin.get();
}
void aiAttack(PlayerBoard& oppships,        //Opponents ships
              char enemyshotfield[][10],    //Array of hits and misses
              char enemyshipfield[][10])    //Opponent's ships
{
    //cout << "aiAttack initiated" << endl;

    bool chosen;        //Determines if the shot is valid
    static int rowshot; //The row hit that the computer tests
    static int colshot; //The column hit that the computer tests
    static int nextrow; //The next row attack
    static int nextcol; //The next column attack
    static int direction;   //Direction to test the shots
    static int firstrow;    //Stores the first hit of the ship (row)
    static int firstcol;    //Stores the first hit of the ship (column)
    bool hit;           //True if the computer scores a hit on that turn
    bool deltaD;        //Tells the computer that there is a change in direction
    static bool shiphit;//True if the computer has hit a ship but hasn't
                            //destroyed it
    static bool destroyed;  //True if the ship is destroyed
    char rowletter;         //Letter that symbolizes a row

    hit = false;
    deltaD = false;

    //If the computer has not hit a ship, it chooses a random location
    if(!shiphit)
    {
        do
        {
            chosen = false;
            rowshot = rand() % 10;
            colshot = rand() % 10;
            if(enemyshotfield[rowshot][colshot] == 'H' ||
                    enemyshotfield[rowshot][colshot] == 'M')
            {
                chosen = true;
            }
        }while(chosen);
    }
    //Other wise, it targets a ship based on a previous hit
    else {
        rowshot = nextrow;        
        colshot = nextcol;
    }
    rowletter = static_cast<char>(rowshot + 65);

    cout << "The computer fired at " << rowletter << " " << colshot + 1 << endl;

    for(unsigned i = 0; i < FLEET_SIZE; i++)
    {
        for (unsigned j = 0; j < oppships.fleet[i].size; j++)
        {
            if(oppships.fleet[i].spaces.at(j).row == rowshot &&
                    oppships.fleet[i].spaces.at(j).column == colshot)
            {
                cout << "The computer scored a hit\n";
                //Stores the first hit and tells the computer to test hits to
                    //the right
                if(!shiphit)
                {
                    firstrow = rowshot;
                    firstcol = colshot;
                    direction = 1;
                }
                //Tells the computer that it has hit a ship and scored a hit on
                    //that turn
                shiphit = true;
                hit = true;
                //cout << "Direction: " << direction << endl;
                //cout << "i = " << i << endl;
                //cout << "j = " << j << endl;
                enemyshotfield[rowshot][colshot] = 'H';
                enemyshipfield[rowshot][colshot] = 'H';

                oppships.fleet[i].hitcount++;

                //Tells the computer if the hit destroyed the ship
                if(oppships.fleet[i].hitcount == oppships.fleet[i].size)
                {
                    oppships.fleet[i].destroyed = true;
                    destroyed = true;

                    //Destroying a ship resets everything
                    direction = 0;
                    shiphit = false;
                    cout << "The computer sunk your " << oppships.fleet[i].name;
                    cout << endl;
                }
            }
        }
    }
    if(!hit)
    {
        cout << "The computer missed\n";
        enemyshotfield[rowshot][colshot] = 'M';
        enemyshipfield[rowshot][colshot] = 'M';
        //If the computer has hit a ship in the previous few moves but not that
            //turn
        if(shiphit)
        {
            //deltaD will update if the ship has been hit on previous turns
            deltaD = true;
            direction++;
        }
    }
    //cout << "deltaD = " << deltaD << endl;
    //cout << "shiphit = " << shiphit << endl;


    if(shiphit)
    {
        //Ship will test hits to the right of the first hit
        if(direction == 1)
        {
            if(colshot + 1 > 9)
            {
                cout << "Direction should update" << endl;
                direction++;
            }
            if(deltaD)
            {
                nextrow = firstrow;
                nextcol = firstcol + 1;
            }
            else
            {
                nextrow = rowshot;
                nextcol = colshot + 1;
            }
        }

        //Ship will test hits above the first hit
        else if(direction == 2)
        {
            if(rowshot - 1 < 0)
            {
                cout << "Direction should update" << endl;
                direction++;
            }

            //If deltaD is true, the computer will go back to the first hit and
                //test a different direction
            if(deltaD)
            {
                nextrow = firstrow - 1;
                nextcol = firstcol;
            }
            else {
                nextrow = rowshot - 1;
                nextcol = colshot;
            }
        }

        //Ship will test hits to the left of the first hit
        else if(direction == 3)
        {
            if(colshot - 1 < 0)
            {
                cout << "Direction should update" << endl;
                direction++;
            }

            //If deltaD is true, the computer will go back to the first hit and
                //test a different direction
            if(deltaD)
            {
                nextrow = firstrow;
                nextcol = firstcol - 1;
            }
            else
            {
                nextrow = rowshot;
                nextcol = colshot - 1;
            }
        }
        //Ship will test hits below the first hit
        else if(direction == 4)
        {
            if(rowshot + 1 > 9)
            {
                cout << "Direction should update" << endl;
                direction = 1;
            }
            //If deltaD is true, the computer will go back to the first hit and
                //test a different direction
            if(deltaD)
            {
                nextrow = firstrow + 1;
                nextcol = firstcol;
            }
            else
            {
                nextrow = rowshot + 1;
                nextcol = colshot;
            }
        }
    }

//    cout << "Direction is " << direction << endl;

//    cout << "The first row hit is: " << firstrow << endl;
//    cout << "The first column hit is: " << firstcol << endl;
//    cout << "The next hit should be " << nextrow << ", " << nextcol << endl;
}

//Checks if the game has been won
bool gameWon(PlayerBoard p1)    //Set of ships
{
    int count = 0;

    //Loop to search through the array to check if the entire fleet has been
        //destroyed
    for(int i = 0; i < FLEET_SIZE; i++)
    {
        if(p1.fleet[i].destroyed)
        {
            count++;
        }
    }
    //Returns true if all of the ships in the fleet have been destroyed
    if(count == FLEET_SIZE)
        return true;

    return false;
}




