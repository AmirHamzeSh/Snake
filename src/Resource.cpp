#include "Resource.h"

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

void consolecolor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Snake::start()
{
    gotoxy(x, y);
    consolecolor(color.greenBright);
    cout.put(Head);
    gotoxy(x, y);
}
void Snake::moveToUP()
{
    gotoxy(x, y);
    cout.put(' ');
    Head = 24;
    gotoxy(x, --y);
    consolecolor(color.greenBright);
    cout.put(Head);
    gotoxy(x, y);
    updateTail();
}
void Snake::moveToDown()
{
    gotoxy(x, y);
    cout.put(' ');
    Head = 25;
    gotoxy(x, ++y);
    consolecolor(color.greenBright);
    cout.put(Head);
    gotoxy(x, y);
    updateTail();
}
void Snake::moveToRight()
{
    gotoxy(x, y);
    cout.put(' ');
    Head = 26;
    gotoxy(++x, y);
    consolecolor(color.greenBright);
    cout.put(Head);
    gotoxy(x, y);
    updateTail();
}
void Snake::moveToLeft()
{
    gotoxy(x, y);
    cout.put(' ');
    Head = '<';
    gotoxy(--x, y);
    consolecolor(color.greenBright);
    cout.put(Head);
    gotoxy(x, y);
    updateTail();
}
void Snake::updateTail()
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

void Food::newFood()
{
    x = random(wall.left, wall.right);
    y = random(wall.top, wall.buttom);
    gotoxy(x, y);
    consolecolor(color.redBright);
    cout.put(face);
    gotoxy(x, y);
}

void Game::reset()
{
    score = 0;
    inputKey = 0;
    snake.lenTail = 0;
    snake.x = 10;
    snake.y = 11;
    snake.Head = 26;
}
void Game::startGame()
{
    system("cls");
    SetConsoleTitleW(L"Snake Game");
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

    food.newFood();
    snake.start();
    loop();
}
void Game::getKey()
{
    if (_kbhit())
        inputKey = getch();
}
Game::~Game()
{
    consolecolor(color.DefaultWhite);
    system("cls");
}
void Game::loop()
{
    while (true)
    {
        getKey();

        switch (inputKey)
        {
        case Up:
            snake.moveToUP();
            Sleep(90);
            break;
        case Down:
            snake.moveToDown();
            Sleep(90);
            break;
        case Right:
            snake.moveToRight();
            Sleep(50);
            break;
        case Left:
            snake.moveToLeft();
            Sleep(50);
            break;
        case Esc:
            system("cls");
            exit(0);
            break;
        default:
            inputKey = getch();
            break;
        }
        CheckWin();
        if (losed())
            break;
    }
    loseMessage();
}
bool Game::losed()
{
    if (snake.x > wall.right || snake.x < wall.left || snake.y < wall.top || snake.y > wall.buttom)
        return true;
    else
    {
        for (int i = 1; i <= snake.lenTail; i++)
        {
            if (snake.x == snake.tail_XY[i][0] && snake.y == snake.tail_XY[i][1])
            {
                return true;
            }
        }
        return false;
    }
}

void Game::loseMessage()
{
    Sleep(500);
    gotoxy(35, 12);
    consolecolor(color.Red);
    cout << "you lose!";
    consolecolor(color.whiteBright);
    gotoxy(25, 13);
    cout << "press Enter to Restart or Exit";
    if (getche() == 13)
    {
        reset();
        startGame();
    }
}
void Game::CheckWin()
{
    if (snake.x == food.x && snake.y == food.y)
    {
        snake.lenTail++;
        score = snake.lenTail * 20;
        consolecolor(color.cyanBright);
        gotoxy(2, 0);
        cout << " score:" << score << ' ';
        food.newFood();
    }
}