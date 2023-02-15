#ifndef BATTLESHIPHEADER_H_INCLUDED
#define BATTLESHIPHEADER_H_INCLUDED

//Global constants
#define MANUAL 49
#define RANDOM 50

//More constants
#define ROWS 10
#define COLS 10
#define WATER '~'
#define PLAYERS 2
#define PLAYER1 0
#define PLAYER2 1
#define NUM_SHIPS 5
#define HORIZONTAL 'H'
#define VERTICAL 'V'
#define CARRIER 'C'
#define BATTLESHIP 'B'
#define CRUISER 'R'
#define SUBMARINE 'S'
#define DESTROYER 'D'
#define CARRIER_SZ 5
#define BATTLESHIP_SZ 4
#define CRUISER_SZ 3
#define SUBMARINE_SZ 3
#define DESTROYER_SZ 2

#define PLAYERONE "Player 1"
#define PLAYERTWO "Player 2"

//More macros
#define HIT 'X'
#define MISS '.'


//structs
typedef struct gameboard {

char board[ROWS][COLS];

}GameBoard;

typedef struct location {

int row;
int column;

}Location;

typedef struct ship {

char name[11];
char symbol;
int length;
bool sunk;

Location start;

}Ship;

typedef struct human {

    char name[20];
    GameBoard gameBoard;
    Ship ships[NUM_SHIPS];

} Player;

enum ships {battleship, carrier, cruiser, destroyer, submarine}ship;

//function prototypes.
void welcomeScreen ();
int displayMenu();
void displayGameBoard();

//More prototypes.
void clearScreen();
void initializeBoard();
void initializePlayer(Player * player, char *name);
void initializeShips();
void displayShips();

//MORE function prototypes

void playGame(Player * playerOne, Player * playerTwo);
int switchPlayer(int currentPlayer);
Location getTarget(Player player);
Location getRandomTarget();
void checkShot(Player * player, Location target);
void updatePlayerData(Player * player, Location location, char result, char ship);
void checkShips(Player * player, Location location, char ship);
void endGame(Player player);

#endif // BATTLESHIPHEADER_H_INCLUDED
