using namespace std;

int random(int x, int y)
{
    srand(time(0));
    return rand() % (y - x + 1) + x;
}
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
struct consoleColors
{
    const int
        Blue = 1,
        Green = 2,
        Cyan = 3,
        Red = 4,
        Purple = 5,
        YellowDark = 6,
        DefaultWhite = 7,
        Gray = 8,
        blueBright = 9,
        greenBright = 10,
        cyanBright = 11,
        redBright = 12,
        pink = 13,
        yellow = 14,
        whiteBright = 15;
};
consoleColors color;
void consolecolor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// inputKeys
#define Up 72
#define Down 80
#define Right 77
#define Left 75
#define Esc 27

class Snake
{
public:
    int x = 10;
    int y = 11;
    char Head = 26;
    int tail_XY[2080][2080];
    int lenTail = 0;

    void start()
    {
        gotoxy(x, y);
        consolecolor(color.greenBright);
        cout.put(Head);
        gotoxy(x, y);
    }

    void moveToUP()
    {
        gotoxy(x, y);
        cout.put(' ');
        Head = 24;
        gotoxy(x, --y);
        consolecolor(color.greenBright);
        cout.put(Head);
        gotoxy(x, y);
    }
    void moveToDown()
    {
        gotoxy(x, y);
        cout.put(' ');
        Head = 25;
        gotoxy(x, ++y);
        consolecolor(color.greenBright);
        cout.put(Head);
        gotoxy(x, y);
    }
    void moveToRight()
    {
        gotoxy(x, y);
        cout.put(' ');
        Head = 26;
        gotoxy(++x, y);
        consolecolor(color.greenBright);
        cout.put(Head);
        gotoxy(x, y);
    }
    void moveToLeft()
    {
        gotoxy(x, y);
        cout.put(' ');
        Head = '<';
        gotoxy(--x, y);
        consolecolor(color.greenBright);
        cout.put(Head);
        gotoxy(x, y);
    }
    void updateTail()
    {
        if (lenTail > 0)
        {
            consolecolor(color.greenBright);
            gotoxy(tail_XY[lenTail][0], tail_XY[lenTail][1]);
            cout.put(' ');

            for (int i = lenTail; i > 0; i--)
            {
                tail_XY[i][0] = tail_XY[i - 1][0];
                tail_XY[i][1] = tail_XY[i - 1][1];
                gotoxy(tail_XY[i][0], tail_XY[i][1]);
                cout.put('o');
            }
        }
        tail_XY[0][0] = x;
        tail_XY[0][1] = y;
    }
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
    void newFood()
    {
        x = random(wall.left, wall.right);
        y = random(wall.top, wall.buttom);
        gotoxy(x, y);
        consolecolor(color.redBright);
        cout.put(face);
        gotoxy(x, y);
    }
};
class Game
{
public:
    int score = 0,
        inputKey = 0,
        prevKey = 0;
    void reset()
    {
        score = 0;
        inputKey = 0;
    }
    void startGame()
    {
        system("cls");
        system("title Snake Game");
        system("mode con cols=80 lines=26");

        consolecolor(color.YellowDark);
        for (int i = 0, j = 25; i < 26 && j >= 0; i++, j--)
        {
            gotoxy(0, j);
            cout << "||";
            gotoxy(78, i);
            cout << "||";
            Sleep(10);
        }

        for (int i = 2, j = 77; i < 78 && j > 1; i++, j--)
        {
            gotoxy(i, 0);
            cout << "=";
            gotoxy(j, 24);
            cout << "=";
            Sleep(10);
        }
        consolecolor(color.cyanBright);
        gotoxy(2, 0);
        cout << " score:" << score << "  ";
        gotoxy(3, 25);
        cout << "Creator:Amir Hamzeh";
        gotoxy(32, 25);
        cout << "use keys" << '[' << (char)24 << ',' << (char)25 << ',' << (char)26 << ',' << '<' << ']';
        gotoxy(63, 25);
        cout << "EXIT = [Esc]";
    }
    ~Game()
    {
        consolecolor(color.DefaultWhite);
        system("cls");
    }
};
