#include "Resource.h"

using namespace std;
Snake snake;
Food food;
Game game;

void CheckWin();
bool losed();
void loseMessage();

int main()
{
    game.startGame();
    food.newFood();
    snake.start();

    while (true)
    {
        game.getKey();

        switch (game.inputKey)
        {
        case Up:
            snake.moveToUP();
            snake.updateTail();
            Sleep(90);
            break;
        case Down:
            snake.moveToDown();
            snake.updateTail();
            Sleep(90);
            break;
        case Right:
            snake.moveToRight();
            snake.updateTail();
            Sleep(50);
            break;
        case Left:
            snake.moveToLeft();
            snake.updateTail();
            Sleep(50);
            break;
        case Esc:
            system("cls");
            return 0;
            break;
        default:
            game.inputKey = getch();
            break;
        }
        CheckWin();
        if (losed())
            break;
    }
    loseMessage();
    return 0;
}

void CheckWin()
{
    if (snake.x == food.x && snake.y == food.y)
    {
        snake.lenTail++;
        game.score = snake.lenTail * 20;
        consolecolor(color.cyanBright);
        gotoxy(2, 0);
        cout << " score:" << game.score << ' ';
        food.newFood();
    }
}

bool losed()
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

void gameReset()
{
    game.reset();
    snake.lenTail = 0;
    snake.x = 10;
    snake.y = 11;
    snake.Head = 26;
}

void loseMessage()
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
        gameReset();
        main();
    }
}