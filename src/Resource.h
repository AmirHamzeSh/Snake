int random(int x, int y);
void gotoxy(int x, int y);

struct consoleColors
{
    int Blue = 1, Green = 2, Cyan = 3, Red = 4,
        Purple = 5, YellowDark = 6,
        DefaultWhite = 7, Gray = 8, blueBright = 9,
        greenBright = 10, cyanBright = 11, redBright = 12,
        pink = 13, yellow = 14, whiteBright = 15;
};
consoleColors color;

void consolecolor(int color);

// inputKeys
const int Up = 72,
          Down = 80,
          Right = 77,
          Left = 75,
          Esc = 27;

class Snake
{
public:
    int x = 10;
    int y = 11;
    char Head = 26;
    int tail_XY[2080][2080];
    int lenTail = 0;

    void start();
    void moveToUP();
    void moveToDown();
    void moveToRight();
    void moveToLeft();
    void updateTail();
};
class Wallborder
{
public:
    int top = 1,
        buttom = 23,
        left = 2,
        right = 77;
};
Wallborder wall;

class Food
{
public:
    int x, y;
    char face = 2;
    void newFood();
};

class Game
{
public:
    int score = 0,
        inputKey = 0,
        inputKeyPerv = 0,
        prevKey = 0;

    Snake snake;
    Food food;

    void reset();
    void startGame();
    void getKey();
    void loop();
    void CheckWin();
    bool losed();
    void loseMessage();
    ~Game();
};
