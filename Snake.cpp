#include <iostream>  // cout - cin
#include <conio.h>   // getch()
#include <windows.h> // Sleep()
#include "random.h"
#include "gotoxy.h"

using namespace std;

#define up_key 72
#define down_key 80
#define right_key 77
#define left_key 75
#define Esc_key 27

int score = 0;
char input = 0;
struct Snake{
    int x = 10,
        y = 11;
};
struct Food{
    int x,y;
    char face = 2;
};
struct Wallborder{
    const int top = 1,
        buttom = 23,
        left = 2,
        right = 77;
};

Snake snake;
Food food;
Wallborder wall;

void move_up();
void move_down();
void move_right();
void move_left();
void intro();

int main()
{
    intro();

    while (true)
    {
        if(_kbhit())
            input = getch();
        
        switch (input)
        {
            case up_key:
                if(snake.y >wall.top)
                    move_up();
                Sleep(100);
                break;
            case down_key:
                if(snake.y<wall.buttom)
                    move_down();
                Sleep(100);
                break;
            case right_key:
                if(snake.x<wall.right)
                    move_right();
                Sleep(50);
                break;
            case left_key:
                if(snake.x>wall.left)
                    move_left();
                Sleep(50);
                break;
            case Esc_key:
                goto exit;
                break;
        }
        
    }

    exit:
    system("cls");
    return 0;
}
void intro()
{
    system("cls");
    system("title snake");
    system("mode con cols=80 lines=26");
    
    for (int i=0,j=25; i<26 && j>=0 ; i++,j--)
        {gotoxy(0, j);cout << "||";gotoxy(78, i);cout << "||";Sleep(10);}

    for (int i=2,j=77; i<78 && j>1 ;i++,j--)
        {gotoxy(i, 0);cout << "="; gotoxy(j, 24);cout << "=";Sleep(10);}

    food.x = random(wall.left, wall.right);
    food.y = random(wall.top, wall.buttom);
    gotoxy(2, 0);   cout << " score:" << score << "  ";
    gotoxy(3, 25);  cout << "Creator:Amir Hamzeh";
    gotoxy(32, 25); cout << "use keys" <<'['<< (char) 24 <<','<<(char) 25 << ',' << (char) 26 << ',' << '<' <<']';
    gotoxy(63, 25); cout << "EXIT = [Esc]";
    gotoxy(food.x, food.y);cout.put(food.face);
    gotoxy(snake.x, snake.y); cout.put(26); gotoxy(snake.x, snake.y);

}
void check_place()
{
    if (snake.x == food.x && snake.y == food.y)
    {
        cout.put(' ');
        gotoxy(2, 0); cout << " "<< "score:" << ++score << "  ";

        food.x = random(wall.left, wall.right);
        food.y = random(wall.top, wall.buttom);

        gotoxy(food.x, food.y); cout.put(food.face);
        gotoxy(snake.x, snake.y);
    }
}
void move_up()
{
    cout.put(' ');
    snake.y--;
    gotoxy(snake.x,snake.y);
    cout.put(24);//↑
    gotoxy(snake.x, snake.y);
    check_place();
}
void move_down()
{
    cout.put(' ');
    snake.y++;
    gotoxy(snake.x, snake.y);
    cout.put(25);//↓
    gotoxy(snake.x, snake.y);
    check_place();
}
void move_right()
{
    cout.put(' ');
    snake.x++;
    gotoxy(snake.x, snake.y);
    cout.put(26);//→
    gotoxy(snake.x, snake.y);
    check_place();
}
void move_left()
{
    cout.put(' ');
    snake.x--;
    gotoxy(snake.x, snake.y);
    cout<<'<';//←
    gotoxy(snake.x, snake.y);
    check_place();
}