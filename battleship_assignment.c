#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//More preprocessor commands
#include <ctype.h>
#include <time.h>

//Aglay Saenz, Battleship Assignment 7, COP3223C-00158. The 2:30 to 3:20 class.

//JUST FOR REFERENCE, TO ANYONE SEEING THIS: When running this...
//PLEASE maximize the program, otherwise it looks very bad. I made this with the intent of viewing it with a full screen view.

#include "battleshipHeader.h"


//main function goes here.
int main()
{

    //Variables for players.
    short player = 0;
    short shot = 0;
    int menuSelect = 0;

    //Variables for directions.
    int north = 0;
    int south = 0;
    int east = 0;
    int west = 0;

    //Variables for counters.
    int i = 0;
    int counter = 0;

    //Variable as temporary ship symbol.
    char shipSymbol = '\0';

    //Game board arrays.
    Player playerOne;
    Player playerTwo;

    srand(time(0));

    welcomeScreen ();


    clearScreen();



    initializePlayer(&playerOne, PLAYERONE);


    clearScreen();


    initializePlayer(&playerTwo, PLAYERTWO);


    clearScreen();


    menuSelect = displayMenu();


    clearScreen();


    switch (menuSelect) {//Displays what choice the player picked.

        case MANUAL:
            printf("%s selected to place ships manually\n\n", playerOne.name);

            //displayGameBoard(playerOne, "Player 1");
            manualShipPlace(&playerOne);
            break;

        case RANDOM:
            printf("%s selected to place ships randomly\n\n", playerOne.name);

            //displayGameBoard(playerOne, "Player 1");
            randomShipPlace(&playerOne);
            break;

    }

randomShipPlace(&playerTwo);

//displayGameBoard(playerOne);

//displayGameBoard(playerTwo);

playGame(&playerOne, &playerTwo);


    return 0;

}


void clearScreen()
{
    system ("cls");

}


void welcomeScreen ()
{

    printf("BBBBB    AAAA   TTTTTT  TTTTTT  LL      EEEEEE   SSSSS  HH  HH  II  PPPP\n");
    printf("BB  BB  AA  AA    TT      TT    LL      EE      SS      HH  HH  II  PP  PP\n");
    printf("BBBBB   AA  AA    TT      TT    LL      EEE      SSSS   HHHHHH  II  PPPP\n");
    printf("BB  BB  AAAAAA    TT      TT    LL      EE          SS  HH  HH  II  PP\n");
    printf("BBBBB   AA  AA    TT      TT    LLLLLL  EEEEEE  SSSSS   HH  HH  II  PP\n\n\n");

    printf("RULES OF THE GAME:\n\n");
    printf("1. This is a two player game.\n");
    printf("2. Player 1 is you and Player 2 is the computer.\n");
    printf("3. Player 1 will be prompted if user wants to manually input coordinates for the game board or have the computer randomly generate a game board.\n");
    printf("4. There are five types of ships to be placed by longest length to the shortest; [c] Carrier has 5 cells. [b] Battleship has 4 cells, [r] Cruiser has 3 cells, [s] Submarine has 3 cells,\n   [d] Destroyer has 2 cells.\n");
    printf("5. The computer randomly selects which player goes first.\n");
    printf("6. The game begins as each player tries to guess the location of the ships of the opposing player's game board; [X] hit and [~] miss.\n");
    printf("7. First player to guess the location of all ships wins.\n\n");


    printf("Hit <ENTER> to continue!\n");

    char data;

    scanf("%c", &data);


}


int displayMenu()
{

    int select;


    while (select != MANUAL && select != RANDOM ) {


        printf("Select the option for human player ship placement. Do not put a letter character:\n");
        printf("[1] Manually\n");
        printf("[2] Randomly\n\n");
        printf("Enter Option:\n");

        select = getchar();


        if(select != MANUAL && select != RANDOM) {

            printf("User selection is invalid. Please try again.\n");

            }

            fflush(stdin);
    }

    return (select);
}


void displayGameBoard(Player player)
{
    int row = 0;
    int col = 0;

    printf("\n%s's game board\n\n", player.name);

    printf("---------------------------------------------\n");
    printf("|   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |\n");
    printf("---------------------------------------------\n");

    for(row = 0; row < ROWS; ++row) {
        printf("| %d |", row);

        for(col = 0; col < COLS; ++col)
        {

            printf(" %c |", player.gameBoard.board[row][col]);

        }

    printf("\n");
    }

    printf("---------------------------------------------\n");

}


void initializeBoard(Player * player)
{
    int row = 0;
    int col = 0;

    for (row = 0; row < ROWS; ++row) {

    memset(player->gameBoard.board, WATER, sizeof(player->gameBoard.board));

    }

}

void initializePlayer(Player *player, char *name)
{
    char playerName[20];

    GameBoard playerBoard;

    Ship ships[NUM_SHIPS];

    printf("Enter %s's name:\n", name);

    gets(playerName);

    strcpy(player->name, playerName);

    player->gameBoard = playerBoard;

    memcpy(player->ships, ships, NUM_SHIPS);

    initializeBoard(player);

    //displayGameBoard(*player);

    //getchar();

    clearScreen();

    initializeShips(player);

    //displayShips(*player);

   // getchar();

}

void initializeShips(Player *player)
{

    int s;

    for (s = 0; s < NUM_SHIPS; s++)
    {
        Ship boat;
        switch (s)
        {
                    case battleship:
                    strcpy(boat.name, "BATTLESHIP");
                    boat.length = BATTLESHIP_SZ;
                    boat.symbol = BATTLESHIP;
                    break;

                    case carrier:
                    strcpy(boat.name, "CARRIER");
                    boat.length = CARRIER_SZ;
                    boat.symbol = CARRIER;
                    break;

                    case cruiser:
                    strcpy(boat.name, "CRUISER");
                    boat.length = CRUISER_SZ;
                    boat.symbol = CRUISER;
                    break;

                    case destroyer:
                    strcpy(boat.name, "DESTROYER");
                    boat.length = DESTROYER_SZ;
                    boat.symbol = DESTROYER;
                    break;

                    case submarine:
                    strcpy(boat.name, "SUBMARINE");
                    boat.length = SUBMARINE_SZ;
                    boat.symbol = SUBMARINE;
                    break;
        }

boat.sunk = false;
boat.start.column = -1;
boat.start.row = -1;
player->ships[s] = boat;

    }

}


void displayShips(Player player)
{

    printf("%s's Ship Data\n", player.name);

    int h;

    for (h = 0; h < NUM_SHIPS; ++h) {
        printf("Name: %s\n", player.ships[h].name);
        printf("Length: %d\n", player.ships[h].length);
        printf("Symbol: %c\n", player.ships[h].symbol);
        printf("Is sunk: %s\n", (player.ships[h].sunk) ? "True" : "False");
        printf("Location: Row : %d Col: %d\n", player.ships[h].start.row, player.ships[h].start.column);
        printf("\n");
    }

}

//I'm assuming steps 7-10 go here

bool isValid(Player player, int row, int col, int length, char orientation)
{

    int p; //loop for rows
    int q; //loop for columns
    bool t = true; //boolean for storing TRUE

    if ((row < 0) || (row + length) > 9)
    {
        return false;
    }

    if ((col < 0) || (col + length) > 9)
    {
        return false;
    }

    if ((orientation != 'H') && (orientation != 'V'))
    {
        return false;
    }

    //7 e

    switch(orientation)
{
    case HORIZONTAL:

        for(q = col; q < (col + length); ++q)
    {
        if (player.gameBoard.board[row][q] != WATER)
        {
            return false;
        }
    }

    break;

    case VERTICAL:

    for(p = row; p < (row + length); ++p)
    {
        if (player.gameBoard.board[p][col] != WATER)
        {
            return false;
        }
    }

    break;

}

    return t;

}

//8

void placeShip (Player * player, int row, int col, Ship ship, char orientation)
{

    int r; //loop rows
    int c; //loop columns


    switch(orientation)
    {


    case HORIZONTAL:
        for(c = col; c < (ship.length + col); c++)
        {
            player->gameBoard.board[row][c] = ship.symbol;
        }
        break;

    case VERTICAL:
        for(r = row; r < (ship.length + row); r++)
        {
            player->gameBoard.board[r][col] = ship.symbol;
        }
        break;
    }
}


//manualShipPlace step 9

void manualShipPlace (Player * player)
{

    int shipNum;
    int row;
    int col;
    char orientation;
    bool valid = false;


    for (shipNum = 0; shipNum < NUM_SHIPS; shipNum++)
    {

    while (valid == false)

    {

    displayGameBoard(*player);

    printf("Enter the row and column (like so: 0 0) for the first cell of ship %s: \n", player->ships[shipNum].name); //. what???
    printf("Row:  Col:  ");
    scanf("%d  %d", &row, &col);

    fflush(stdin);

    printf("Enter the orientation. H for Horizontal, V for vertical: \n");
    scanf("%c", &orientation);

    orientation = toupper(orientation);

    printf("Checking row %d orient %c...\n", row, col, orientation);



    valid = isValid(*player, row, col, player->ships[shipNum].length, orientation);

    if (valid)
    {
        placeShip(player, row, col, player->ships[shipNum], orientation); //right player (first one?)
    }

     else
     {
         valid = false;

         printf("Invalid. Please try again.\n");
     }


    }

        valid = false;

    }
}


void randomShipPlace(Player * player)
{

int shipNum;
int row;
int col;
char orientation;
int const DIR = 2;
int const H = 0;
int const V = 1;
int o; //storing random value for orientation

bool valid = false;

fflush(stdin);

for (shipNum = 0; shipNum < NUM_SHIPS; shipNum++)
{

   while (valid == false)
        {
            row = (rand() % ROWS);
            col = (rand() % COLS);

            o  = (rand() % DIR);

            if(o == H)
                {
                  orientation = HORIZONTAL;
                }


            if(o == V)
                {
                  orientation = VERTICAL;
                }

            valid = isValid(*player, row, col, player->ships[shipNum].length, orientation);

            if (valid)
            {
                placeShip(player, row, col, player->ships[shipNum], orientation);

            }
            else
            {
                valid = false;
                printf("Invalid, Try again.\n");
            }
        }
        valid = false;
    }
}


//not correct values?

void playGame(Player * playerOne, Player * playerTwo)
{

  int currentPlayer = PLAYER1;
  Location target;

  while (true)
  {
     switch (currentPlayer)
     {
         case PLAYER1:

                printf("%s's turn!\n", playerOne->name);
                displayGameBoard(*playerOne);
                //get target from player
                target = getTarget(*playerOne);
                checkShot(playerTwo, target);

                break;

           case PLAYER2:

                printf("%s's turn!", playerTwo->name);
                target = getRandomTarget();
                checkShot(playerOne, target);

                break;
     }

         currentPlayer = switchPlayer(currentPlayer);


         clearScreen();

     }


}

int switchPlayer(int currentPlayer)
{
    if(currentPlayer == PLAYER1) //CURLIES?
        return PLAYER2;

    else if(currentPlayer == PLAYER2)
        return PLAYER1;

}


Location getTarget(Player player)
{

    Location target;

    fflush (stdin);

    printf("%s Enter Target as row and col (ie. 2 4): ", player.name);

    scanf("%d %d", &target.row, &target.column);

    fflush(stdin);

    return target;

}


Location getRandomTarget()
{
    Location target;

    target.row = (rand() % ROWS);
    target.column = (rand() % COLS);

    return target;

}

void checkShot(Player * player, Location target)
{
    char symbol = player->gameBoard.board[target.row][target.column];

    switch(symbol)
    {
        case WATER:

            printf(" Row %d Col %d was a Miss!", target.row, target.column);
            getchar();
            updatePlayerData(player, target, MISS, symbol);

            break;

            //HIT; CHECK ORDER
        case BATTLESHIP:
        case CARRIER:
        case CRUISER:
        case DESTROYER:
        case SUBMARINE:

            printf(" Row %d Col %d was a Hit!", target.row, target.column);
            getchar();
            updatePlayerData(player, target, HIT, symbol);

            break;

        case HIT:
        case MISS:
        default:

            printf(" Already guessed that location, you lost a turn!\n");
            getchar();

            break;

    }

}

void updatePlayerData(Player * player, Location location, char result ,char ship)
{
    player->gameBoard.board[location.row][location.column] = result;

    if (result == HIT)
    {
        checkShips(player, location, ship);
    }

}

void checkShips(Player * player, Location location, char ship)
{
    const int battleshipIdx = 0;
    const int carrierIdx = 1;
    const int cruiserIdx = 2;
    const int destroyerIdx = 3;
    const int submarineIdx = 4;

    int sunkCount = 0;
    int shipNum;

    switch(ship)
    {
        case BATTLESHIP:

            player->ships[battleshipIdx].length--;

            if(player->ships[battleshipIdx].length == 0)
                printf("%s's BATTLESHIP is sunk!", player->name);

            getchar();

            break;

        case CARRIER:

            player->ships[carrierIdx].length--;

            if(player->ships[carrierIdx].length == 0)
                printf("%s's CARRIER is sunk!", player->name);

            getchar();

            break;

        case CRUISER:

            player->ships[cruiserIdx].length--;

            if (player->ships[cruiserIdx].length == 0)
                printf("%s's CRUISER is sunk!", player->name);

            getchar();

            break;

        case DESTROYER:

            player->ships[destroyerIdx].length--;

            if (player->ships[destroyerIdx].length == 0)
                printf("%s's DESTROYER is sunk!", player->name);

            getchar();

            break;

        case SUBMARINE:

            player->ships[submarineIdx].length--;

            if (player->ships[submarineIdx].length == 0)
                printf("%s's SUBMARINE is sunk!", player->name);

            getchar();

            break;
    }

    for(shipNum = 0; shipNum < NUM_SHIPS; shipNum++)
    {
        if(player->ships[shipNum].length == 0)
            sunkCount++;

        if(sunkCount == NUM_SHIPS)
            endGame(*player);
    }

}

void endGame(Player player)
{
    printf("%s has lost this game!", player.name);
    getchar();


    exit(0);

}




