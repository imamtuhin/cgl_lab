#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <windows.h>
#include <glut.h>
#include <GL.h>
#include <conio.h>
#include <ctime>
#include <iostream>
#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
//#include <math.h>
#include <time.h>
#define pi (2*acos(0.0))

using namespace std;

double cameraHeight;
double cameraAngle;
double angle;
int c=0,rnum=0;
float re=0,bl=0,gr=0;
double incx=0,incy=0, ani_angle;
struct point
{
	double x,y,z;
};

struct point pos,l,u,r;
//double X=0,Z=0,a,b;
//int Y=-1;
struct point arra[100];
void movement();

/*
  void gotoxy(int x, int y)
    {
    COORD dwCursorPosition = { x, y };
    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), dwCursorPosition);
   }
*/

int q,a[5][5],win=0,lose=0,x=0,y=0,s=0,coun=0,aa[5][5];


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

void background()
{
    int a = 100;
    glBegin(GL_QUADS);
    {
        glColor3f(0.1, 0.2, 1);
        glVertex3f(a, a, 0);
        glColor3f(0.1, 0.2, 1);
        glVertex3f(a, -a, 0);

        glColor3f(0.2, 0.7, 0.7);
        glVertex3f(-a, -a, 0);
        glColor3f(0.2, 0.7, 0.7);
        glVertex3f(-a, a, 0);
    }
    glEnd();
}

void drawSquare(double a)
{
    //glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);{
		glVertex3f( a, a,2);
		glVertex3f( a,-a,2);
		glVertex3f(-a,-a,2);
		glVertex3f(-a, a,2);
	}glEnd();
}


void rectangle(float x, float y, float z, float a, float b, float red, float green, float blue)
{
    glColor3f(red, green, blue);

    glBegin(GL_QUADS);
    {
        glVertex3f(x, y, z);
        glVertex3f(x + a, y, z);

        glVertex3f(x + a, y - b, z);
        glVertex3f(x, y - b, z);
    }
    glEnd();
}


void showText(string text, float r, float g, float b, float x, float y, float z)
{
   // int i;
    glColor3f(r, g, b);
    glRasterPos3f(x, y, z);
    for (int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);

  glEnd();
}

void showText1(string text, float r, float g, float b, float x, float y, float z)
{
   // int i;
    glColor3f(r, g, b);
    glRasterPos3f(x, y, z);
    for (int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);

  glEnd();
}


/*
int rndm()
{
   int val;
    srand(time(0));
    q=rand()%50;
    srand(q);
    val=rand()%2;
    if(val==0)
    {
       re=0.99;
       bl=0.94;
       gr=0.11;
       rnum=2;
        //return 2;
    }
    else
    {

       re=0.38;
       bl=0.99;
       gr=0.11;
       rnum=4;
     //   return 4;
    }
}
*/
void ran()
{

    int put=0;
    srand(time(0));
    int r=1+rand()%16;

    int val;
    srand(time(0));
    q=rand()%50;
    srand(q);
    val=rand()%2;
    if(val==0)
    {
       re=0.99;
       bl=0.94;
       gr=0.11;
       rnum=2;
        //return 2;
    }
    else
    {

       re=0.38;
       bl=0.99;
       gr=0.11;
       rnum=4;
     //   return 4;
    }

    while(put==0)
    {
        switch (r)
        {
        case 1:
            if(a[1][1]==0)
            {
               // gotoxy(2,3);
              // a[1][1]=rndm();

                glPushMatrix();
                 showText("2", 0, 0, 0, 8, 7, 1);
//               showText1(to_string(rndm()), 0, 0, 0, 8, 7, 1);
               rectangle(0, 20, 0, 20, 20, re,bl,gr);
                 // quad();
                glPopMatrix();
                //a[1][1]=rndm();
                put=1;
                break;
            }
            else
            {
                r=2;
            }
            break;
            case 2:
             if(a[2][1]==0)
            {
               // gotoxy(8,3);
               // a[2][1]=rndm();
                glPushMatrix();

                 showText("2", 0, 0, 0, 28, 7, 1);
                //showText((rndm()), 0, 0, 0, 28, 7, 1);
                rectangle(20, 20, 0, 20, 20, re,bl,gr);
                 // quad();
                glPopMatrix();

                put=1;
                break;
            }
            else
            {
                r=3;
            }
            break;
            case 3:
             if(a[3][1]==0)
            {
               // gotoxy(14,3);
                //a[3][1]=rndm();
                glPushMatrix();

                 showText("2", 0, 0, 0, 48, 7, 1);
               // showText((rndm()), 0, 0, 0, 48, 7, 1);
                rectangle(40, 20, 0, 20, 20, re,bl,gr);
                 // quad();
                glPopMatrix();
                put=1;
                break;
            }
            else
            {
                r=4;
            }
            break;
            case 4:
             if(a[4][1]==0)
            {
               // gotoxy(20,3);
              //  a[4][1]=rndm();
                glPushMatrix();

                 showText("2", 0, 0, 0, 68, 7, 1);
               // showText((rndm()), 0, 0, 0, 68, 7, 1);
                rectangle(60, 20, 0, 20, 20, re,bl,gr);
                 // quad();
                glPopMatrix();
                put=1;
                break;
            }
            else
            {
                r=5;
            }
            break;
            case 5:
            if(a[1][2]==0)
            {
                //gotoxy(2,7);
              //  a[1][2]=rndm();
                glPushMatrix();

                 showText("2", 0, 0, 0, 8, 27, 1);
              // showText((rndm()), 0, 0, 0, 8, 27, 1);
                rectangle(0, 40, 0, 20, 20, re,bl,gr);
                 // quad();
                glPopMatrix();
                put=1;
                break;
            }
            else
            {
                r=6;
            }
            break;
            case 6:
             if(a[2][2]==0)
            {
               // gotoxy(8,7);
                //a[2][2]=rndm();
                glPushMatrix();

                 showText("2", 0, 0, 0, 28, 27, 1);
               // showText((rndm()), 0, 0, 0, 28, 27, 1);
                rectangle(20, 40, 0, 20, 20, re,bl,gr);
                 // quad();
                glPopMatrix();
                put=1;
                break;
            }
            else
            {
                r=7;
            }
            break;
            case 7:
             if(a[3][2]==0)
            {
               // gotoxy(14,7);
               // a[3][2]=rndm();
                glPushMatrix();

                 showText("2", 0, 0, 0, 48, 27, 1);
                //showText((rndm()), 0, 0, 0, 48, 27, 1);
                rectangle(40, 40, 0, 20, 20, re,bl,gr);
                 // quad();
                glPopMatrix();
                put=1;
                break;
            }
            else
            {
                r=8;
            }
            break;
            case 8:
             if(a[4][2]==0)
            {
               // gotoxy(20,7);
               // a[4][2]=rndm();

                glPushMatrix();

                 showText("2", 0, 0, 0, 68, 27, 1);
                //showText((rndm()), 0, 0, 0, 68, 27, 1);
                rectangle(60, 40, 0, 20, 20, re,bl,gr);
                 // quad();
                glPopMatrix();
                put=1;
                break;
            }
            else
            {
                r=9;
            }
            break;
            case 9:
            if(a[1][3]==0)
            {
               // gotoxy(2,11);
               // a[1][3]=rndm();

                glPushMatrix();

                 showText("2", 0, 0, 0, 8, 47, 1);
                //showText((rndm()), 0, 0, 0, 8, 47, 1);
                rectangle(0, 60, 0, 20, 20, re,bl,gr);
                 // quad();
                glPopMatrix();
                put=1;
                break;
            }
            else
            {
                r=10;
            }
            break;
            case 10:
             if(a[2][3]==0)
            {
                //gotoxy(8,11);
               // a[2][3]=rndm();
                glPushMatrix();

                 showText("2", 0, 0, 0, 28, 47, 1);
                //showText((rndm()), 0, 0, 0, 28, 47, 1);
                rectangle(20, 60, 0, 20, 20, re,bl,gr);
                 // quad();
                glPopMatrix();

                put=1;
                break;
            }
            else
            {
                r=11;
            }
            break;
            case 11:
             if(a[3][3]==0)
            {
               // gotoxy(14,11);
               // a[3][3]=rndm();

                glPushMatrix();

                 showText("2", 0, 0, 0, 48, 47, 1);
               // showText((rndm()), 0, 0, 0, 48, 47, 1);
                rectangle(40, 60, 0, 20, 20, re,bl,gr);
                 // quad();
                glPopMatrix();
                put=1;
                break;
            }
            else
            {
                r=12;
            }
            break;
            case 12:
             if(a[4][3]==0)
            {
               // gotoxy(20,11);
               // a[4][3]=rndm();
                glPushMatrix();

                 showText("2", 0, 0, 0, 68, 47, 1);
               // showText((rndm()), 0, 0, 0, 68, 47, 1);
                rectangle(60, 60, 0, 20, 20, re,bl,gr);
                 // quad();
                glPopMatrix();
                put=1;
                break;
            }
            else
            {
                r=13;
            }
            break;
            case 13:
            if(a[1][4]==0)
            {
                //gotoxy(2,15);
               // a[1][4]=rndm();
                glPushMatrix();

                 showText("2", 0, 0, 0, 8, 67, 1);
                //showText((rndm()), 0, 0, 0, 8, 67, 1);
                rectangle(0, 80, 0, 20, 20, re,bl,gr);
                 // quad();
                glPopMatrix();

                put=1;
                break;
            }
            else
            {
                r=14;
            }
            break;
            case 14:
             if(a[2][4]==0)
            {
               // gotoxy(8,15);
               // a[2][4]=rndm();

                glPushMatrix();

                 showText("2", 0, 0, 0, 28, 67, 1);
               // showText((rndm()), 0, 0, 0, 28, 67, 1);
                rectangle(20, 80, 0, 20, 20, re,bl,gr);
                 // quad();
                glPopMatrix();
                put=1;
                break;
            }
            else
            {
                r=15;
            }
            break;
            case 15:
             if(a[3][4]==0)
            {
               // gotoxy(14,15);
               // a[3][4]=rndm();
                glPushMatrix();

                 showText("2", 0, 0, 0, 48, 67, 1);
               // showText((rndm()), 0, 0, 0, 48, 67, 1);
                rectangle(40, 80, 0, 20, 20, re,bl,gr);
                 // quad();
                glPopMatrix();

                put=1;
                break;
            }
            else
            {
                r=16;
            }
            break;
            case 16:
             if(a[4][4]==0)
            {
               // gotoxy(20,15);
              //  a[4][4]=rndm();

                glPushMatrix();

                 showText("2", 0, 0, 0, 68, 67, 1);
//                showText("2", 0, 0, 0, 68, 67, 1);
                rectangle(60, 80, 0, 20, 20, re,bl,gr);
                 // quad();
                glPopMatrix();
                put=1;
                break;
            }
            else
            {
                r=1;
            }
            break;
        }
    }
}

void drawCircle(double radius,int segments)
{
    int i;
    struct point points[100];
    glColor3f(0.7,0.7,0.7);
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw segments using generated points
    for(i=0;i<segments;i++)
    {
        glBegin(GL_LINES);
        {
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}

void draw_cylinder(double radius,double height,int segments)
{
    int i;
     struct point points[2][100];
     for(i=0;i<=segments;i++)
    {
        points[0][i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[0][i].y=radius*sin(((double)i/(double)segments)*2*pi);
        points[0][i].z=0;

        points[1][i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[1][i].y=radius*sin(((double)i/(double)segments)*2*pi);
        points[1][i].z=height;
    }

    for (i=0;i<segments;i++)
    {
        glBegin(GL_QUADS);{
			    //upper hemisphere
			    glColor3f((i)%2,1,(i)%2);
				glVertex3f(points[0][i].x,points[0][i].y,points[0][i].z);
				glVertex3f(points[0][i+1].x,points[0][i+1].y,points[0][i+1].z);

				glColor3f((i)%2,(i)%2,1);
				glVertex3f(points[1][i+1].x,points[1][i+1].y,points[1][i+1].z);
				glVertex3f(points[1][i].x,points[1][i].y,points[1][i].z);

			}glEnd();


    }
}

void drawCone(double radius,double height,int segments)
{
    int i;
    double shade;
    struct point points[100];
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw triangles using generated points
    for(i=0;i<segments;i++)
    {
        //create shading effect
        if(i<segments/2)shade=2*(double)i/(double)segments;
        else shade=2*(1.0-(double)i/(double)segments);
        glColor3f(shade,shade,1);

        glBegin(GL_TRIANGLES);
        {
            glVertex3f(0,0,height);
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}


void drawSphere(double radius,int slices,int stacks)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		}
	}
	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{
        glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{
			    //upper hemisphere
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                //lower hemisphere

                glColor3f(1.0,(double)i/(double)stacks,(double)i/(double)stacks);
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
			}glEnd();



		}
	}
}

void quad()
{


  // Draw A Quad


        glBegin(GL_QUADS);
            glColor3f(0.0f,1.0f,0.0f);
            glVertex3f(10,10.0f,0.0f);					    // Top front Of The Quad (right)
            glVertex3f(20.0f,10.0f,0.0f);					// Top back Of The Quad (right)
            glVertex3f(20.0f,0.0f,0.0f);					// Bottom back Of The Quad (right)
            glVertex3f(10.0f,0.0f,0.0f);					// Bottom front Of The Quad (right)

        /*    glColor3f(1.0f,1.0f,0.0f);

            glVertex3f(-1.0f,1.0f,8.0f);					// Top front Of The Quad (left)
            glVertex3f(-1.0f,1.0f,1.0f);					// Top back Of The Quad (left)
            glVertex3f(-1.0f,-1.0f,1.0f);					// Bottom back Of The Quad (left)
            glVertex3f(-1.0f,-1.0f,8.0f);					// Bottom front Of The Quad (left)


            glColor3f(1.0f,0.0f,1.0f);

            glVertex3f(1.0f,1.0f,8.0f);					    // Right front Of The Quad (top)
            glVertex3f(1.0f,1.0f,1.0f);					    // Right back Of The Quad (top)
            glVertex3f(-1.0f,1.0f,1.0f);				    // Left back Of The Quad (top)
            glVertex3f(-1.0f,1.0f,8.0f);				    // Left front Of The Quad (top)


            glColor3f(0.0f,1.0f,1.0f);

            glVertex3f(1.0f,-1.0f,8.0f);					// Right front Of The Quad (bottom)
            glVertex3f(1.0f,-1.0f,1.0f);					// Right back Of The Quad (bottom)
            glVertex3f(-1.0f,-1.0f,1.0f);				    // Left back Of The Quad (bottom)
            glVertex3f(-1.0f,-1.0f,8.0f);				    // Left front Of The Quad (bottom)


            glColor3f(0.0f,0.0f,1.0f);

            glVertex3f(1.0f,1.0f,1.0f);					 // Top Right Of The Quad (Back)
            glVertex3f(-1.0f,1.0f,1.0f);					// Top Left Of The Quad (Back)
            glVertex3f(-1.0f,-1.0f,1.0f);					// Bottom Left Of The Quad (Back)
            glVertex3f(1.0f,-1.0f,1.0f);				// Bottom Right Of The Quad (Back)


            glColor3f(1.0f,0.0f,0.0f);

            glVertex3f(1.0f,1.0f,8.0f);					    // Top Right Of The Quad (Front)
            glVertex3f(-1.0f,1.0f,8.0f);					// Top Left Of The Quad (Front)
            glVertex3f(-1.0f,-1.0f,8.0f);					// Bottom Left Of The Quad (Front)
            glVertex3f(1.0f,-1.0f,8.0f);			// Bottom Right Of The Quad (Front)
*/

        glEnd();
}


void board()
{
  // Draw A Quad


        glBegin(GL_QUADS);
            glColor3f(0.6f,0.65f,0.58f);
            glVertex3f(-40,80.0f,0.0f);					    // Top front Of The Quad (right)
            glVertex3f(40.0f,80.0f,0.0f);					// Top back Of The Quad (right)
            glVertex3f(40.0f,0.0f,0.0f);					// Bottom back Of The Quad (right)
            glVertex3f(-40.0f,0.0f,0.0f);					// Bottom front Of The Quad (right)


        glEnd();
}


void drawSquare(GLint x1, GLint y1, GLint x2, GLint y2, GLint x3, GLint y3, GLint x4, GLint y4)
{


// Draw Square
glBegin(GL_POLYGON);
glVertex2i(x1, y1);
glVertex2i(x2, y2);
glVertex2i(x3, y3);
glVertex2i(x4, y4);
glEnd();
}

void checkingBoard()
{
  // Draw A Quad
 glBegin(GL_QUADS);
            glColor3f(0.6f,0.65f,0.58f);
            glVertex3f(-40,80.0f,0.0f);					    // Top front Of The Quad (right)
            glVertex3f(40.0f,80.0f,0.0f);					// Top back Of The Quad (right)
            glVertex3f(40.0f,0.0f,0.0f);					// Bottom back Of The Quad (right)
            glVertex3f(-40.0f,0.0f,0.0f);					// Bottom front Of The Quad (right)


        glEnd();
}

void previousBoard()
{
  // Draw A Quad

 glBegin(GL_QUADS);
            glColor3f(0.6f,0.65f,0.58f);
            glVertex3f(-40,80.0f,0.0f);					    // Top front Of The Quad (right)
            glVertex3f(40.0f,80.0f,0.0f);					// Top back Of The Quad (right)
            glVertex3f(40.0f,0.0f,0.0f);					// Bottom back Of The Quad (right)
            glVertex3f(-40.0f,0.0f,0.0f);

        glEnd();
}



void pyramid()
{
    glBegin(GL_TRIANGLES);

    glColor3f(1,1,0);

    glVertex3d(0,5,0);
    glVertex3d(5,-3,0);
    glVertex3d(-5,-3,0);

    glColor3f(1,0.5,0);

    glVertex3d(0,5,0);
    glVertex3d(5,-3,0);
    glVertex3d(0,0,5);

    glColor3f(0.5,0.5,0);

    glVertex3d(0,5,0);
    glVertex3d(0,0,5);
    glVertex3d(-5,-3,0);

    glColor3f(0.5,1,0);

    glVertex3d(0,0,5);
    glVertex3d(5,-3,0);
    glVertex3d(-5,-3,0);

    glEnd();
}

void drawSS()
{
    glColor3f(1,0,0);
    drawSquare(20);

    glRotatef(angle,0,0,1);
    glTranslatef(110,0,0);
    glRotatef(2*angle,0,0,1);
    glColor3f(0,1,0);
    drawSquare(15);

    glPushMatrix();
    {
        glRotatef(angle,0,0,1);
        glTranslatef(60,0,0);
        glRotatef(2*angle,0,0,1);
        glColor3f(0,0,1);
        drawSquare(10);
    }
    glPopMatrix();

    glRotatef(3*angle,0,0,1);
    glTranslatef(40,0,0);
    glRotatef(4*angle,0,0,1);
    glColor3f(1,1,0);
    drawSquare(5);
}

void keyboardListener(unsigned char key, int xx,int yy){
   /* double x,y,z;
    double rate = 0.01;
	switch(key){

		case '1':

			{
            x=l.x;y=l.y;z=l.z;
			l.x = l.x*cos(rate)+1*r.x*sin(rate);
			l.y = l.y*cos(rate)+r.y*sin(rate);
			l.z = l.z*cos(rate)+r.z*sin(rate);

			r.x = r.x*cos(rate)-x*sin(rate);
			r.y = r.y*cos(rate)-y*sin(rate);
			r.z = r.z*cos(rate)-z*sin(rate);}
			break;
        case '2':

			{
            x=l.x;y=l.y;z=l.z;
			l.x = l.x*cos(-rate)+r.x*sin(-rate);
			l.y = l.y*cos(-rate)+r.y*sin(-rate);
			l.z = l.z*cos(-rate)+r.z*sin(-rate);

			r.x = r.x*cos(-rate)-x*sin(-rate);
			r.y = r.y*cos(-rate)-y*sin(-rate);
			r.z = r.z*cos(-rate)-z*sin(-rate);
			}
			break;
        case '3':
            x=l.x;y=l.y;z=l.z;
			l.x = l.x*cos(rate)+u.x*sin(rate);
			l.y = l.y*cos(rate)+u.y*sin(rate);
			l.z = l.z*cos(rate)+u.z*sin(rate);

			u.x = u.x*cos(rate)-x*sin(rate);
			u.y = u.y*cos(rate)-y*sin(rate);
			u.z = u.z*cos(rate)-z*sin(rate);
			break;
        case '4':
            x=l.x;y=l.y;z=l.z;
			l.x = l.x*cos(-rate)+1*u.x*sin(-rate);
			l.y = l.y*cos(-rate)+u.y*sin(-rate);
			l.z = l.z*cos(-rate)+u.z*sin(-rate);

			u.x = u.x*cos(-rate)-x*sin(-rate);
			u.y = u.y*cos(-rate)-y*sin(-rate);
			u.z = u.z*cos(-rate)-z*sin(-rate);
			break;
        case '6':
            x=r.x;y=r.y;z=r.z;
			r.x = r.x*cos(rate)+u.x*sin(rate);
			r.y = r.y*cos(rate)+u.y*sin(rate);
			r.z = r.z*cos(rate)+u.z*sin(rate);

			u.x = u.x*cos(rate)-x*sin(rate);
			u.y = u.y*cos(rate)-y*sin(rate);
			u.z = u.z*cos(rate)-z*sin(rate);
			break;
        case '5':
            x=r.x;y=r.y;z=r.z;
			r.x = r.x*cos(-rate)+u.x*sin(-rate);
			r.y = r.y*cos(-rate)+u.y*sin(-rate);
			r.z = r.z*cos(-rate)+u.z*sin(-rate);

			u.x = u.x*cos(-rate)-x*sin(-rate);
			u.y = u.y*cos(-rate)-y*sin(-rate);
			u.z = u.z*cos(-rate)-z*sin(-rate);
			break;
		default:
			break;
	}  */

}


void specialKeyListener(int key, int x,int y)
{
	switch(key){
		case GLUT_KEY_UP:		//down arrow key
			/*  pos.x+=l.x;
			pos.y+=l.y;
			pos.z+=l.z;
			*/
			//incy+=10;
			//angle=0;
			break;
		case GLUT_KEY_DOWN:		// up arrow key
			/* pos.x-=l.x;
			pos.y-=l.y;
			pos.z-=l.z;  */
			break;

		case GLUT_KEY_LEFT :
			/* pos.x+=r.x;
			pos.y+=r.y;
			pos.z+=r.z;


			  }


			*/

                //incx-=10;
                //angle=0;

               break;


              // incy+=10*a;



		case GLUT_KEY_RIGHT :
			/* pos.x-=r.x;
			pos.y-=r.y;
			pos.z-=r.z;  */
                //incx+=10;
               // angle=0;


            //  incy-=10*a;
                   //default:
                break;

		case GLUT_KEY_PAGE_UP:
		  /*  pos.x+=u.x;
			pos.y+=u.y;
			pos.z+=u.z;  */
			break;
		case GLUT_KEY_PAGE_DOWN:
           /* pos.x-=u.x;
			pos.y-=u.y;
			pos.z-=u.z;  */
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
			break;
		case GLUT_KEY_END:
			break;

		default:
			break;
	}
}


void mouseListener(int button, int state, int x, int y)
{	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
		    if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP

			}
			break;


		case GLUT_RIGHT_BUTTON:
		    if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP

				//(600/cos(angle_c_x*pi/180))/cos(angle_t_x*pi/180);
			}
			break;
			//........

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}

void animation3d()
{
    //glTranslated(20,0,20);
    //glRotated(ani_angle,0,0,1 );
    //glTranslated(20,0,0);
    glColor3f(1,0.2,0);
    drawSphere(5,10,10);

    glPushMatrix();

    glColor3f(0,0.5,0.5);
    glRotated(1.5*ani_angle,0,0,1);
    glTranslated(20,0,0);
    glRotated(4*ani_angle,0,0,1);
    drawSphere(3,10,10);

    glPopMatrix();

    glPushMatrix();

    glColor3f(0.5,0.0,0.5);
    glRotated(ani_angle+40,0,0,1);
    glTranslated(30,0,0);
    drawSphere(3,10,10);

    glPopMatrix();

    glPushMatrix();

    glColor3f(0.5,0.5,0.5);
    glRotated(-1.9*ani_angle+60,0,1,1);
    glTranslated(45,0,0);
    drawSphere(7,40,40);

    glPopMatrix();

}

void display()
{

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1,1,1,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	//gluLookAt(100,100,100,	0,0,0,	0,0,1);
	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	//gluLookAt(pos.x,pos.y,pos.z,	pos.x+l.x,pos.y+l.y,pos.z+l.z,	u.x,u.y,u.z);
    gluLookAt(0,0,200,	0,0,0,	0,1,0);

	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();
	drawGrid();
	//gotoxy(10,10);
	//pu();
    ran();
    ran();

   // won();
   // pri();
  //  movement();

    //board();
    //glColor3f(1,0,0);
    //drawSquare(10);

   // drawSS();
   // drawSphere(50,30,30);
   // pyramid();
 /*  glPushMatrix();
   glTranslated(incx,incy,0);
   //glRotatef(angle,0 ,0,1);
   //glRotatef(90, 1, 0, 0);
   // glRotatef(angle,0 ,0,1);
        showText("2", 0, 0, 0, 8, 7, 1);
        //showText(to_string(SCORE), 1, 1, 1, 62, 82, 1);
        rectangle(0, 20, 0, 20, 20, 0.0, 1.0, 0.0);
       // quad();
  */ glPopMatrix();
    //draw_cylinder(20,40,10);

    showText1("SCORE: ", 1, 1, 1, 11, 81, 1);
    //showText1(to_string(SCORE), 1, 1, 1, 62, 82, 1);
    rectangle(10, 90, 0, 60, 10, 0.04, 0.32, 0.27);
   // board();
	background();


    //drawCircle(30,24);

   // drawCone(20,50,5);

	//drawSphere(30,24,20);
	//animation3d();




	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){

    incx+=0.05;
    ani_angle+=0.09;
	glutPostRedisplay();
}

void init(){
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	5000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv)
{
   // pos.x=0;
   // pos.y=-20;
   // pos.z=-20;
   // l.x=0;u.x=-1;r.x=0;
   // l.y=0;u.y=0;r.y=1;
   // l.z=1;u.z=0;r.z=0;

    //cout<<"Press 'W' to move up | Press 'S' to move down | Press 'A' to move Left | Press 'D' to move Right";
   // ran();
    //ran();
    //movement();

	glutInit(&argc,argv);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}





















/*
void drawSphere(double radius,int slices,int stacks,int up)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		if(up==3){
                r= 2*radius- radius*cos(((double)i/(double)stacks)*(pi/2));
		}else{
		     r=  radius*cos(((double)i/(double)stacks)*(pi/2));
		}
		for(j=0;j<=slices;j++)
		{
		    if(up!=3){
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		    }
		    else{
            points[i][j].x= r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=(r*sin(((double)j/(double)slices)*2*pi));
			points[i][j].z=h;

		    }
		}
	}
	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{
        //glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);

		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{
			    //upper hemisphere
			    glColor3f(j%2,j%2,j%2);
			    if(up==1 or up==-1 or up==3)
                {
                    glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
                    glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
                    glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
                    glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                }
                //lower hemisphere
                if(up==0 or up==-1)
                {

                    glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
                    glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
                    glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
                    glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
                }


			}glEnd();
		}
	}
}


void offline()
{

    glBegin(GL_QUADS);{
        //upper hemisphere
        glColor3f(.1,.1,.1);
        glVertex3f(200,-650,200);
        glVertex3f(200,-650,-200);
        glVertex3f(-200,-650,-200);
        glVertex3f(-200,-650,200);

    }glEnd();


    if(bullet==1 && abs(X)<200 && abs(Z)<200){
    Y++;
    arra[Y].x=X;
    arra[Y].z = Z;
    printf("%lf %lf %lf %lf\n",X,Z,angle_c_x,angle_c_z);

	bullet =0;

    }
    int j;
    for(j=0;j<=Y;j++){
        glColor3f(1.0,0.0,0.0);

            glBegin(GL_QUADS);{
            glVertex3f(arra[j].x+5 ,-649, arra[j].z+5);
            glVertex3f(arra[j].x+5,-649, arra[j].z-5);
            glVertex3f(arra[j].x-5,-649,arra[j].z-5 );
            glVertex3f(arra[j].x-5, -649, arra[j].z+5);
        }glEnd();
    }

    int segment =30;
    glRotatef(angle_c_z,0,0,1);
    glRotatef(angle_c_x,1,0,0);
    glRotatef(90,1,0,0);
    glTranslatef(0,0,20);
    drawSphere(20,segment,segment,0);
    draw_cylinder(20,100,segment);
    glTranslatef(0,0,100);
    drawSphere(20,segment,segment,1);
    double r,l;
    r=15;
    l=170;
    glTranslatef(0,0,20);

    glRotatef(angle_t_x,1,0,0);
    glRotatef(angle_t_z,0,0,1);

    glTranslatef(0,0,r);
    drawSphere(r,segment,segment,0);
    draw_cylinder(r,l,segment);
    glTranslatef(0,0,l);
    drawSphere(r,segment,segment,3);
}
*/
