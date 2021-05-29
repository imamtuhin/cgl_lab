#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <windows.h>
#include <glut.h>
#include <GL.h>
#include <conio.h>
#include <ctime>
#include <iostream>
#include <cmath>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "cube_colors.h"

using namespace std;

int time_val;
char title[] = "merge number";
int windowWidth  = 440;
int windowHeight = 480;
float refreshMillis = 4;
float variable = 0;
bool timer_flag = true;
bool size_flag;
float size_koef = 0;
float space_between_squares;
float one_segment_size;
float offset = 0.2f;


typedef struct SQUARE
{
    int value;
    float x;
    float y;
    float dx,rx;
    float dy,ry;
    int delta_value;
    bool need_refresh;
    bool start_flag;
    bool size;

} Square ;

typedef struct gameinfo
{
    bool max_num;
    Square matrix[4][4];
    int scores;
} GameStats;

GameStats CreateGameStats(Square matrix[4][4], int scores, bool max_num)
{
    GameStats stats;
    stats.scores = scores;
    stats.max_num = max_num;
    return  stats;
}
typedef struct _Element
{
    GameStats value;
    struct _Element *next;
} Element;

typedef struct TStack
{
    Element *head;
} Stack;

void Create(Stack * stack)
{
    stack->head = NULL;
}

void Destroy(Stack * stack)
{
    while(stack->head)
    {
        Element *tmp = stack->head;
        stack->head = stack->head->next;
        free(tmp);
    }
}

int Push(Stack * stack, GameStats val)
{
    Element *tmp = (Element*)malloc(sizeof(GameStats));

    if(!tmp)
        return 0;

    if (stack->head)
    {
        tmp->next = stack->head;
        tmp->value = val;
        stack->head = tmp;
    }
    else
    {
        tmp->value = val;
        tmp->next = NULL;
        stack->head = tmp;
    }
    return 1;
}

int Pop(Stack * stack, GameStats *val)
{
    if(!stack->head)
        return 0;

    Element *tmp = stack->head;
    *val = stack->head->value;

    stack->head = stack->head->next;

    free(tmp);

    return 1;
}

void Show(Stack * stack)
{
    Stack buf;
    Create(&buf);

    while (stack->head)
    {
        GameStats value;
        Pop(stack, &value);
        Push(&buf,value);
    }

    while (buf.head)
    {
        GameStats value;
        Pop(&buf, &value);
        Push(stack,value);
    }

    Destroy(&buf);

}

typedef struct VECTOR2
{
    float x;
    float y;
} Vector2;

Vector2 center_points[4][4];

Square squares[4][4];
int startlerp;

typedef void (*ButtonCallback)();
Square matrix[4][4];
int scores = 0;
int high_scores = 0;
Stack stack;
GameStats stats;
bool move_flag = false;
bool max_num = false;
bool maxcube_flag = false;
bool endgame_flag = false;
bool need_random  = false;
Vector2 bottom_left = {-0.7f, -0.7f};
Vector2 up_left = {-0.7f, 0.5};
Vector2 up_right = {0.7f, 0.5f};
Vector2 bottom_right = {0.7f, -0.7f};

  typedef struct Button
{
    int   x;
    int   y;
    int   w;
    int   h;
    ButtonCallback callbackFunction;
} Button;

void NewGame();
Button NewGameButton = {55,80, 80,40, NewGame };
void GameStatusCheck();

void drawAxes()
{

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);{
        glColor3f(0.0f,1.0f,0.0f);
        glVertex3f( 1000,0,0);
        glVertex3f(-1000,0,0);

        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f(0,-1000,0);
        glVertex3f(0, 1000,0);

        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f(0,0, 1000);
        glVertex3f(0,0,-1000);
    }glEnd();
}


void drawGrid()
{
	int i;
    glColor3f(0.6, 0.6, 0.6);	//grey
    glBegin(GL_LINES);{
        for(i=-5;i<=5;i++){

            if(i==0)
                continue;	//SKIP the MAIN axes

            //lines parallel to Y-axis
            glVertex3f(i*20, -90, 0);
            glVertex3f(i*20,  90, 0);

            //lines parallel to X-axis
            glVertex3f(-90, i*20, 0);
            glVertex3f( 90, i*20, 0);
        }
    }glEnd();

}

void initGL()
{
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(1, 0.996f, 0.937f, 1);
}

void RenderBitmapString(float x, float y,float z, void *font,char *string)
{
    char *c;
    glRasterPos3f(x,y,z);
    for (c=string; *c != '\0'; c++)
        glutBitmapCharacter(font, *c);
}

void UpdateHighScores()
{
      high_scores = scores;
}

void AddScores(int new_scores)
{
    scores += new_scores;
    if (scores > high_scores)
        UpdateHighScores();
}

void board ()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            if ((matrix[i][j].dx != matrix[i][j].x) && matrix[i][j].dx != 0)
            {
                    matrix[i][j].x -=  matrix[i][j].rx;
                    matrix[i][j].dx +=  matrix[i][j].rx;
            }

            if ((matrix[i][j].dy != matrix[i][j].y) && matrix[i][j].dy != 0)
            {
                matrix[i][j].y -=  matrix[i][j].ry;
                matrix[i][j].dy +=  matrix[i][j].ry;
            }
        }

}

void cubeSizeTimer(int value)
{
    size_flag = false;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j< 4; j++)
        {
            matrix[i][j].start_flag = false;
        }


    GameStatusCheck();
    size_koef = 0;
    timer_flag = true;
}

void ResizeSquare()
{
    size_koef += 0.02;
}

void CreateRandom(int value)
{
    int i = rand() % 4;
    int j = rand() % 4;

    if (matrix[i][j].value == 0)
    {
        srand((unsigned)time(NULL));
        int chance = rand() % 9;

        if (chance == 8) matrix[i][j].value = 4;
        else matrix[i][j].value = 2;

        matrix[i][j].start_flag = true;
        matrix[i][j].need_refresh = false;

        size_flag = true;
        glutTimerFunc(100, cubeSizeTimer, 0);

    }
    else CreateRandom(200);
}

void moveup()
{

    if (!timer_flag)
        return;

    for (int j = 0; j < 4; j++)
        for (int i = 0; i < 3; i++)
            {
                int index = i + 1;
                for (; index < 3; index++)
                {
                    if (matrix[index][j].value != 0)
                        break;
                }

                if ((matrix[i][j].value == matrix[index][j].value) && matrix[i][j].value > 0)
                {
                    matrix[i][j].value += matrix[index][j].value;
                   AddScores(matrix[index][j].value);

                    matrix[index][j].value = 0;


                    matrix[index][j].dy = matrix[i][j].y;
                    matrix[index][j].ry = (matrix[index][j].y - matrix[index][j].dy) / 15;

                    matrix[index][j].need_refresh = true;
                    i += 1;
                }
            }

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 4; j++)
                if (matrix[i][j].value == 0)
                {
                    int index;
                    for (index = i+ 1; index < 3 ; index++)
                    {
                        if (matrix[index][j].value != 0)
                            break;
                    }

                    matrix[i][j].value += matrix[index][j].value;
                    matrix[index][j].value = 0;

                    if (matrix[index][j].dy == 0)
                    {
                        matrix[index][j].dy = matrix[i][j].y;
                        matrix[index][j].ry = (matrix[index][j].y - matrix[index][j].dy) / 15;
                    }

                    matrix[i][j].need_refresh = true;
                }

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
            {
                if ((matrix[i][j].value == 0) && (matrix[i][j].delta_value == 0))
                {
                    matrix[i][j].dx = 0;
                    matrix[i][j].dy = 0;
                    matrix[i][j].rx = 0;
                }
            }

}

void movedown()
{
    if (!timer_flag)
        return;

    for (int j = 0; j < 4; j++)
        for (int i = 3; i > 0; i--)
            {
                int index = i - 1;
                for (; index > 0; index--)
                {
                    if (matrix[index][j].value != 0)
                        break;
                }

                if ((matrix[i][j].value == matrix[index][j].value) && matrix[i][j].value > 0)
                {
                    matrix[i][j].value += matrix[index][j].value;
                    AddScores(matrix[index][j].value);
                    matrix[index][j].value = 0;

                    matrix[index][j].dy = matrix[i][j].y;
                    matrix[index][j].ry = (matrix[index][j].y - matrix[index][j].dy) / 15;

                    matrix[index][j].need_refresh = true;
                    i -= 1;
                }
            }

        for (int i = 3; i > 0; i--)
            for (int j = 0; j < 4; j++)
                if (matrix[i][j].value == 0)
                {
                    int index;
                    for (index = i - 1; index > 0 ; index--)
                    {
                        if (matrix[index][j].value != 0)
                            break;
                    }

                    matrix[i][j].value += matrix[index][j].value;
                    matrix[index][j].value = 0;

                    if (matrix[index][j].dy == 0)
                    {
                        matrix[index][j].dy = matrix[i][j].y;
                        matrix[index][j].ry = (matrix[index][j].y - matrix[index][j].dy) / 15;
                    }


                    matrix[i][j].need_refresh = true;
                }

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
            {
                if ((matrix[i][j].value == 0) && (matrix[i][j].delta_value == 0))
                {
                    matrix[i][j].dx = 0;
                    matrix[i][j].dy = 0;
                    matrix[i][j].rx = 0;
                }
            }
}

void moveleft()
{
    if (!timer_flag)
        return;

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 3; j++)
            {
                int index = j + 1;
                for (; index < 3; index++)
                {
                    if (matrix[i][index].value != 0)
                        break;
                }

                if ((matrix[i][j].value == matrix[i][index].value) && matrix[i][j].value > 0)
                {
                    matrix[i][j].value += matrix[i][index].value;
                    AddScores(matrix[i][index].value);
                    matrix[i][index].value = 0;

                    matrix[i][index].dx = matrix[i][j].x;
                    matrix[i][index].rx = (matrix[i][index].x - matrix[i][index].dx) / 15;

                    matrix[i][index].need_refresh = true;
                    j += 1;

                }
            }

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 3; j++)
                if (matrix[i][j].value == 0)
                {
                    int index;
                    for (index = j+ 1; index < 3 ; index++)
                    {
                        if (matrix[i][index].value != 0)
                            break;
                    }

                    matrix[i][j].value += matrix[i][index].value;
                    matrix[i][index].value = 0;

                    if (matrix[i][index].dx == 0)
                    {
                        matrix[i][index].dx = matrix[i][j].x;
                        matrix[i][index].rx = (matrix[i][index].x - matrix[i][index].dx) / 15;
                    }


                    matrix[i][j].need_refresh = true;
                }

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
            {
                if ((matrix[i][j].value == 0) && (matrix[i][j].delta_value == 0))
                {
                    matrix[i][j].dx = 0;
                    matrix[i][j].dy = 0;
                    matrix[i][j].rx = 0;
                }
            }

}

void moveright()
{
    if (!timer_flag)
        return;

    for (int i = 0; i < 4; i++)
        for (int j = 3; j > 0; j--)
        {
            int index = j-1;
            for (; index > 0; index--)
            {
               if (matrix[i][index].value != 0)
                   break;
            }

            if ((matrix[i][j].value == matrix[i][index].value) && matrix[i][j].value > 0)
            {
                matrix[i][j].value += matrix[i][index].value;
                AddScores(matrix[i][index].value);
                matrix[i][index].value = 0;

                matrix[i][index].dx = matrix[i][index].x;
                matrix[i][index].rx = (matrix[i][index].x - matrix[i][index].dx) / 15;

                matrix[i][index].need_refresh = true;
                j -= 1;
            }
        }

    for (int i = 0; i < 4; i++)
        for (int j = 3; j > 0; j--)
            if (matrix[i][j].value == 0)
            {
                int index;
                for (index = j-1; index > 0 ; index--)
                {
                    if (matrix[i][index].value != 0)
                        break;
                }

                matrix[i][j].value += matrix[i][index].value;
                matrix[i][index].value = 0;

                if (matrix[i][index].dx == 0)
                {
                    matrix[i][index].dx = matrix[i][j].x;
                    matrix[i][index].rx = (matrix[i][index].x - matrix[i][index].dx) / 15;
                }


                matrix[i][j].need_refresh = true;
            }

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            if ((matrix[i][j].value == 0) && (matrix[i][j].delta_value == 0))
            {
                matrix[i][j].dx = 0;
                matrix[i][j].dy = 0;
                matrix[i][j].rx = 0;
            }
        }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1,1,1,0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    //best score
    glBegin(GL_QUADS);
        glColor3f(0.9f, 0.2f, 0.3f);
        glVertex2f(up_right.x - 0.4f, 1 - (1 - up_right.y - offset)+ offset);
        glVertex2f(up_right.x - 0.4f, 1 - (1 - up_right.y - offset));
        glVertex2f(up_right.x,1 - (1 - up_right.y - offset));
        glVertex2f(up_right.x, 1 - (1 - up_right.y - offset)+ offset);
    glEnd();

    //score
    glBegin(GL_QUADS);
        glColor3f(0.8f, 0.3f, 0.14f);
        glVertex2f(up_right.x - 0.85f, 1 - (1 - up_right.y - offset)+ offset);
        glVertex2f(up_right.x - 0.85f, 1 - (1 - up_right.y - offset));
        glVertex2f(up_right.x-0.45f,1 - (1 - up_right.y - offset));
        glVertex2f(up_right.x-0.45f, 1 - (1 - up_right.y - offset)+ offset);
    glEnd();

    // New game
    glBegin(GL_QUADS);
    glColor3f(0.6f, 0.8f, 0.3f);
    glVertex2f(up_left.x + 0.3f, 1 - (1 - up_left.y - offset) - 0.17f);
    glVertex2f(up_left.x + 0.3f, 1 - (1 - up_left.y - offset) - 0.03f);
    glVertex2f(up_left.x,1 - (1 - up_left.y - offset) - 0.03f);
    glVertex2f(up_left.x, 1 - (1 - up_left.y - offset) - 0.17f);
    glEnd();

    // border
    glBegin(GL_QUADS);
        glColor3f(0.34f, 0.99f, 1.05f);
        glVertex2f(bottom_left.x, bottom_left.x - offset);
        glVertex2f(up_left.x, up_left.y);
        glVertex2f(up_right.x , up_right.y);
        glVertex2f(bottom_right.x, bottom_right.y - offset);
    glEnd();

    //board
    float current_x, current_y;
    current_x = current_y = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j< 4; j++)
        {
            glBegin(GL_POLYGON);
            glColor3f(0.6f, 0.8f, 0.5f);
            glVertex2f(center_points[i][j].x - one_segment_size / 2, center_points[i][j].y + one_segment_size / 2);
            glVertex2f(center_points[i][j].x + one_segment_size / 2, center_points[i][j].y + one_segment_size / 2);
            glVertex2f(center_points[i][j].x + one_segment_size / 2, center_points[i][j].y - one_segment_size / 2);
            glVertex2f(center_points[i][j].x - one_segment_size / 2, center_points[i][j].y - one_segment_size / 2);
            glEnd();

        }

    }

    //cube

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j< 4; j++)
        {
            if ((matrix[i][j].dx > 0.0f || matrix[i][j].dy > 0.0f || matrix[i][j].dx < 0.0f || matrix[i][j].dy < 0.0f) && matrix[i][j].delta_value > 0  )
            {
                glBegin(GL_QUADS);
                    Color color = GetColor(matrix[i][j].delta_value);
                    glColor3f(color.r, color.g , color.b);
                    glVertex2f(matrix[i][j].x - one_segment_size / 2, matrix[i][j].y  - one_segment_size / 2);
                    glVertex2f(matrix[i][j].x - one_segment_size / 2, matrix[i][j].y + one_segment_size / 2);
                    glVertex2f(matrix[i][j].x + one_segment_size / 2, matrix[i][j].y + one_segment_size / 2);
                    glVertex2f(matrix[i][j].x + one_segment_size / 2, matrix[i][j].y - one_segment_size / 2);
                glEnd();

                color = GetTextColor(matrix[i][j].delta_value);
                glColor3f(color.r, color.g , color.b);
                char c[20];
                sprintf(c, "%d", matrix[i][j].delta_value);

                if (matrix[i][j].value > 0)
                    RenderBitmapString(center_points[i][j].x-(0.02f*strlen(c)),center_points[i][j].y-0.02f,-1,GLUT_BITMAP_HELVETICA_18,c);
            }
            else if (matrix[i][j].value > 0 && !matrix[i][j].need_refresh)
            {

                glBegin(GL_QUADS);
                    Color color = GetColor(matrix[i][j].value);
                    glColor3f(color.r, color.g , color.b);

                    if (matrix[i][j].start_flag)
                    {
                        glVertex2f(matrix[i][j].x - (one_segment_size / 2 * size_koef), matrix[i][j].y  - (one_segment_size / 2 * size_koef));
                        glVertex2f(matrix[i][j].x - (one_segment_size / 2 * size_koef), matrix[i][j].y + (one_segment_size / 2 * size_koef));
                        glVertex2f(matrix[i][j].x + (one_segment_size / 2 * size_koef), matrix[i][j].y + (one_segment_size / 2 * size_koef));
                        glVertex2f(matrix[i][j].x + (one_segment_size / 2 * size_koef), matrix[i][j].y - (one_segment_size / 2 * size_koef));
                    }
                    else
                    {
                        glVertex2f(matrix[i][j].x - one_segment_size / 2, matrix[i][j].y  - one_segment_size / 2);
                        glVertex2f(matrix[i][j].x - one_segment_size / 2, matrix[i][j].y + one_segment_size / 2);
                        glVertex2f(matrix[i][j].x + one_segment_size / 2, matrix[i][j].y + one_segment_size / 2);
                        glVertex2f(matrix[i][j].x + one_segment_size / 2, matrix[i][j].y - one_segment_size / 2);
                    }
                glEnd();

                color = GetTextColor(matrix[i][j].value);
                glColor3f(color.r, color.g, color.b);
                char c[20];
                sprintf(c, "%d", matrix[i][j].value);

                if (matrix[i][j].value > 0)
                    RenderBitmapString(center_points[i][j].x-(0.02f*strlen(c)),center_points[i][j].y-0.02f,-1,GLUT_BITMAP_HELVETICA_18,c);
            }
        }
    }

    glColor3f(0.466f, 0.431f, 0.396f);
        RenderBitmapString(-0.71f,0.82f,-1,GLUT_BITMAP_HELVETICA_18,"merge number");
        RenderBitmapString(-0.35f,0.6f,-1,GLUT_BITMAP_HELVETICA_12,"left,right,up,down/W,S,A,D");
        RenderBitmapString(-0.35f,0.54f,-1,GLUT_BITMAP_HELVETICA_12,"to merge number");
    glColor3f(0.933f, 0.894f, 0.854f);
        RenderBitmapString((up_right.x - 0.85f) + 0.15f,1 - (1 - up_right.y - offset)+0.14f,-1,GLUT_BITMAP_HELVETICA_10,"Score");
        RenderBitmapString((up_right.x - 0.4f) + 0.15f,1 - (1 - up_right.y - offset)+0.14f,-1,GLUT_BITMAP_HELVETICA_10,"Best");
        RenderBitmapString((up_left.x + 0.1f),1 - (1 - up_right.y - offset)-0.11f,-1,GLUT_BITMAP_HELVETICA_10,"New");


    char char_scores[20];
    sprintf(char_scores, "%d", scores);
    RenderBitmapString(((up_right.x - 0.81f) + 0.17f)-(0.02f*strlen(char_scores)),1 - (1 - up_right.y - offset) + 0.05f,-1,GLUT_BITMAP_HELVETICA_18,char_scores);

    sprintf(char_scores, "%d", high_scores);
    RenderBitmapString(((up_right.x - 0.81f) + 0.61f)-(0.02f*strlen(char_scores)),1 - (1 - up_right.y - offset) + 0.05f,-1,GLUT_BITMAP_HELVETICA_18,char_scores);


    if (endgame_flag)
    {
        glBegin(GL_QUADS);
            glColor4f(1, 0.996f, 0.937f, 0.8f);
            glVertex2f(bottom_left.x, bottom_left.x - offset);
            glVertex2f(up_left.x, up_left.y);
            glVertex2f(up_right.x , up_right.y);
            glVertex2f(bottom_right.x, bottom_right.y - offset);
        glEnd();

        glColor3f(0.466f, 0.431f, 0.396f);
        RenderBitmapString(-0.4f,-0.15f,-1,GLUT_BITMAP_HELVETICA_18,"GAME OVER");
        RenderBitmapString(-0.5f,-0.3f,-1,GLUT_BITMAP_HELVETICA_12,"Press NEW GAME to try again");
    }


    if (maxcube_flag)
    {
        glBegin(GL_QUADS);
            glColor4f(1, 0.996f, 0.937f, 0.8f);
            glVertex2f(bottom_left.x, bottom_left.x - offset);
            glVertex2f(up_left.x, up_left.y);
            glVertex2f(up_right.x , up_right.y);
            glVertex2f(bottom_right.x, bottom_right.y - offset);
        glEnd();

        glColor3f(0.466f, 0.431f, 0.396f);
            RenderBitmapString(-0.6f,-0.15f,-1,GLUT_BITMAP_HELVETICA_18,"congrats!!! you reach 512 ");
            RenderBitmapString(-0.6f,-0.3f,-1,GLUT_BITMAP_HELVETICA_18,"Press any key to continue game");
    }

       glutSwapBuffers();
}

void timer(int value)
{
    glutPostRedisplay();
    time_val++;

    if (!timer_flag)
        board();

    if (size_flag)
        ResizeSquare();


    glutTimerFunc(refreshMillis, timer, 0);
}

void boardTimer(int value)
{
    time_val = 0;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            matrix[i][j].dx  =  0;
            matrix[i][j].dy  =  0;
            matrix[i][j].rx = 0;
            matrix[i][j].ry = 0;
              matrix[i][j].x = center_points[i][j].x;
              matrix[i][j].y = center_points[i][j].y;

            if (matrix[i][j].value > 0)
            {
                matrix[i][j].need_refresh = false;
                matrix[i][j].delta_value = 0;
            }
        }

    if (need_random)
    {
        glutTimerFunc(210, CreateRandom, 0);
        need_random = false;
    }
}

void Keyboard(unsigned char key, int x, int y)
{
    if (!maxcube_flag && !endgame_flag)
    {

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            matrix[i][j].delta_value = matrix[i][j].value;
        }

    switch (key)
    {

        case 100    : // d
        case 68     : // D
            moveright(); break;

        case 119    : // w
        case 87     : // W
            moveup(); break;

        case 115    : // s
        case 83     : // S
            movedown(); break;

        case 97     : // a
        case 65     : // A
            moveleft(); break;



        default:
            break;
    }

    bool check_for_new_random = true;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            if (matrix[i][j].value != matrix[i][j].delta_value)
            {
                check_for_new_random = false;
                break;
            }
        }

    if (!check_for_new_random)
        need_random = true;


    if (need_random)
    {
        timer_flag = false;
        startlerp = time_val;
        glutTimerFunc(100, boardTimer, 0);
    }
    else GameStatusCheck();

    }
    else
    {
        if (maxcube_flag)
            maxcube_flag = false;
        if (endgame_flag)
            if ((int)key == 27) //any key
            {

                exit(0);
            }
    }
}

void GameStatusCheck()
{
    bool free_square = false;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            if (matrix[i][j].value == 0)
            {
                free_square = true;
                break;
            }
        }

    if (!free_square)
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
            {
                    if ((matrix[i][j].value == matrix[i+1][j].value) ||
                        (matrix[i][j].value == matrix[i][j+1].value) ||
                        (matrix[3][j].value == matrix[3][j+1].value) ||
                        (matrix[i][3].value == matrix[i+1][3].value) )
                        free_square = true;
            }


    if (!free_square)
    {
        endgame_flag= true;
        return;
    }

    if (!max_num)
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
            {
                if (matrix[i][j].value == 512)
                {
                    maxcube_flag = true;
                    max_num = true;
                }
            }
    }
}

void Init()
{
    float full_space = fabsf(up_left.x) + fabsf(up_right.x);
    one_segment_size = ((full_space - full_space / 30) / 4);
    space_between_squares = one_segment_size / 8;
    one_segment_size -= space_between_squares;

    float free_space_x, free_space_y = space_between_squares;

    for (int i = 0; i < 4; i++)
    {
        free_space_x = space_between_squares;

        for (int j = 0; j < 4; j++)
        {
            center_points[i][j].x =  up_left.x  + free_space_x + (one_segment_size ) * (j+1) - (one_segment_size/2);
            center_points[i][j].y =  up_left.y  - free_space_y - (one_segment_size) * (i+1) + (one_segment_size/2) ;
            free_space_x += space_between_squares;
        }

        free_space_y += space_between_squares;
    }

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            matrix[i][j].value = 0;

    CreateRandom(200);
    CreateRandom(200);


    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            matrix[i][j].x = center_points[i][j].x;
            matrix[i][j].y = center_points[i][j].y;
        }
}

void PushToStats()
{
    stats = CreateGameStats(matrix,scores,max_num);

    Push(&stack, stats);
}

void NewGame()
{
    scores = 0;
    endgame_flag = false;
    maxcube_flag = false;
    while (Pop(&stack, &stats))
        {}
    Init();
}

int ButtonClick(Button* b,float x,float y)
{
    if(b)
    {
        if( x > b->x && x < b->x+b->w && y > b->y && y < b->y+b->h )
        {
            b->callbackFunction();
            return 1;
        }
    }
    return 0;
}

void MouseButton(int button,int state,int x, int y)
{
    printf("%d %d %d\n", button, x,y);

    if (state == GLUT_DOWN)
    {
        ButtonClick(&NewGameButton,x,y);
    }
}


void SpecialInput(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_DOWN:
            Keyboard(115,0,0);
            break;
        case GLUT_KEY_UP:
            Keyboard(119,0,0);
            break;
        case GLUT_KEY_LEFT:
            Keyboard(97,0,0);
            break;
        case GLUT_KEY_RIGHT:
            Keyboard(100,0,0);
            break;
    }
}


int main(int argc, char** argv)
{
    InitColors();
    NewGame();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-windowWidth)/2,(glutGet(GLUT_SCREEN_HEIGHT)-windowHeight)/2);
    glutCreateWindow(title);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SpecialInput);
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    initGL();
    glutMouseFunc(MouseButton);
    glutMainLoop();
    return 0;
}
