#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, foodX, foodY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection direction;
void Setup()
{
    gameOver = false;
    direction = STOP;
    x = width / 2;
    y = height / 2;
    foodX = rand() % width;
    foodY = rand() % height;
    score = 0;
}

void Draw()
{
    system("cls");
    cout << "Score: " << score << endl;
    for(int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    for(int i = 0; i < height; i ++){
        for(int j = 0; j < width + 1; j ++){
            if(j == 0 || j == width)
                cout << "#";
            if(i == y && j == x)
                cout << "O";
            else if(i == foodY && j == foodX)
                cout << "X";
            else
            {
                bool print = false;
                for(int k = 0; k < nTail; k ++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }

                }
                if(!print)
                    cout << " ";
            }

        }
        cout << endl;
    }

    for(int i= 0; i < width + 2; i++)
        cout << "#";
}

void Input()
{
    if(_kbhit())
    {
        if(_getch() == 224)
            switch(_getch())
        {
            case 75:
                if(direction != RIGHT)
                    direction = LEFT;
                break;
            case 77:
                if(direction != LEFT)
                    direction = RIGHT;
                break;
            case 72:
                if(direction != DOWN)
                    direction = UP;
                break;
            case 80:
                if(direction != UP)
                    direction = DOWN;
                break;
            default:
                break;
        }
        else if(_getch() == 'x')
        {
            gameOver = true;
        }
    }
}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for(int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch(direction)
    {
        case LEFT:
            x --;
            break;
        case RIGHT:
            x ++;
            break;
        case UP:
            y --;
            break;
        case DOWN:
            y ++;
            break;
        default:
            break;
    }
    if(x >= width)x = 0;
    else if(x < 0)x = width - 1;
    if(y >= height)y = 0;
    else if(y < 0)y = height - 1;
    for(int i = 0; i < nTail; i++)
    {
        if(tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }
    if (x == foodX && y == foodY)
    {
        nTail ++;
        score ++;
        foodX = rand() % width;
        foodY = rand() % height;
    }

}

int main() {
    Setup();
    while(!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(50);
    }
    cout << endl;
    cout << "\nGAME OVER!  SCORE: " << score;
    return 0;
}
