/*
    1) Makes score function to work (it`s work. Just rewrite drawFigure and so on...)
    2) Dell all global variables and rewrite all functions in more universal way
    3) Limit for x movement when another figure here
    4) Save all figures as arrays and rewrite draw function for printing array according to coordinates
    5) Obj programing

    6) When we transform figure with amount of x bigger than 2 then we get figure with 3 floors along y. It creates some problems.
*/




#include <GL/freeglut.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h> // some string functions

using namespace std;

// i - column (x), n - row (y)

const int I = 10, N = 10; // Fields amount
const int Scale = 50; // Fields size
const int w = Scale * I, h = Scale * N;
int timer = 100; // Game speed
int mov_x = 5, mov_x_max = 0, mov_y = 0, type = 0;
bool figure[4][4], global_field[10][10];


void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
}

void drawField() // Drowing of Fields
{
    glColor3f(1,1,1); // Color of Fields
    glBegin(GL_LINES);
    // xy
    for (int i = 0; i <= w; i += Scale)
        {glVertex3f(i,0,0); glVertex3f(i,h,0);}
    for (int n = 0; n <= h; n += Scale)
        {glVertex3f(0,n,0); glVertex3f(w,n,0);}
    glEnd();
}

void drawCube(int x, int y, int color)
{
    if(x >= ::I)
        cout << "Error 1: Cube X position out of game field!" << endl;
    else if(y >= ::N)
        cout << "Error 1: Cube Y position out of game field!" << endl;
    else
    {
        glBegin(GL_POLYGON);

        if(color == 0)
            glColor3f( 0, 1, 1 );
        else
            glColor3f( 1, 0, 1);

        int y_amount_px = ::N * ::Scale;
        glVertex3f( ::Scale * x, y_amount_px - ::Scale * y, 0.0 );
        glVertex3f( ::Scale * x, y_amount_px -  ::Scale * (y + 1), 0.0 );
        glVertex3f( ::Scale * (x + 1), y_amount_px -  ::Scale * (y + 1), 0.0 );
        glVertex3f( ::Scale * (x + 1), y_amount_px - ::Scale * y, 0.0 );

        glEnd();
    }

}

void globalFieldInit()
{
    for(int i = 0; i < 10; i++)
        for(int n = 0;n < 10;n++)
            ::global_field[i][n]=false;
}

void figureInit()
{
    for(int i = 0; i < 4; i++)
        for(int n = 0;n < 4;n++)
            ::figure[i][n] = false;

}

void drawFigure(int type)
{
    // cout << "DrawFigure()" << endl;
    switch(type)
    {
        case 0:
            ::figure[0][0] = true;
            ::mov_x_max = 0; // how many x`s does this figure include
            break;
        case 1:
            ::figure[0][0] = true;
            ::figure[1][0] = true;
            ::mov_x_max = 1;
            break;
        case 2:
            ::figure[0][0] = true;
            ::figure[1][0] = true;
            ::figure[1][1] = true;
            ::mov_x_max = 1;
            break;
        case 3:
            ::figure[0][0] = true;
            ::figure[1][0] = true;
            ::figure[2][0] = true;
            ::mov_x_max = 2;
            break;
        case 4:
            ::figure[0][0] = true;
            ::figure[1][0] = true;
            ::figure[2][0] = true;
            ::figure[1][1] = true;
            ::mov_x_max = 2;
            break;
        case 5:
            ::figure[0][0] = true;
            ::figure[1][0] = true;
            ::figure[2][0] = true;
            ::figure[3][0] = true;
            ::mov_x_max = 3;
            break;
        case 6:
            ::figure[0][0] = true;
            ::figure[1][0] = true;
            ::figure[0][1] = true;
            ::figure[1][1] = true;
            ::mov_x_max = 1;
            break;
    }
}

void transpFigure()
{
    bool transp[4][4];
    for(int i = 0; i < 4; i++)
        for(int n = 0; n < 4; n++)
            transp[i][n] = ::figure[i][n];

        for(int i = 0; i < 4; i++)
        {
            for(int n = 0; n < 4; n++)
            {
                figure[i][n] = transp[n][i];
            }
        }
}


void addPxToGlobalField(int x, int y)
{
    ::global_field[x][y] = true;
}

void globalFieldShow()
{
    int i, n;
    for(i = 0; i < 10; i++)
        for(n = 0; n < 10; n++)
        {
            //cout << ::figure[i][n] << endl;
            if(::global_field[i][n] != false)
                drawCube(i, n, 0);
        }

}

bool figPosChecker( int x, int y)
{
    int i, n;
    for(i = 0; i < 4; i++)
        for(n = 0; n < 4; n++)
            if(::figure[i][n] != false)
                if(::global_field[x + i][y + n + 1] == true)
                    return true;
    return false;

}

void figureShow( int x, int y)
{
    int i, n;
    for(i = 0; i < 4; i++)
        for(n = 0; n < 4; n++)
            if(::figure[i][n] != false)
                   drawCube(x + i, y + n, 1);
}

void score()
{
    unsigned long int testCounter = 0;
    int o = 0;
    for(int n = 0; n < 10; n++)
    {
        for(int i = 0; i < 10; i++)
            if(::global_field[i][n] == true)
            {
                cout << testCounter << endl;
                o++;
                if(o >= 9)
                    cout << "full row: " << n << endl;
                    /*for(int n1 = n - 1; n1 > 0; n1--)
                        for(int i1 = 0; i1 < 10; i1++)
                        {
                            ::global_field[i1][n1] = ::global_field[i1][n1 + 1];
                            //::global_field[i1][n] = false;
                        }*/
            }
        o = 0;
    }
    cout << "score()" << endl;
}

void moving()
{
    globalFieldShow(); // old figures
    figureShow(::mov_x, ::mov_y); // current moving figure
    ::mov_y++; // y moving
}

void gameOver()
{
    for(int i = 0; i < 10; i++)
        if(::global_field[i][1] == true)
        {
            cout << "Game over! Press, any key to continue!" << endl;
            for(int i = 0; i < 10; i++) // erase of ::global_field
                for(int n = 0; n < 10; n++)
                    ::global_field[i][n] = true;
        }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix(); // for all scene
    int r_x = 0 + ::Scale;
    int r_y = 0 + ::Scale;
    int r_z = 0;
    glTranslatef(r_x, r_y, r_z);//transform scene possition x y z
    //glRotatef(::x, 1.0, 0.0, 0.0);//full scene rotation
    //glRotatef(::y, 0.0, 1.0, 0.0);//full scene rotation
    //glRotatef(::z, 0.0, 0.0, 1.0);//full scene rotation
    //glTranslatef(-1 * r_x, -1 * r_y, -1 * r_z);//rotate round point x y z


    int max_y_iterator = 9;//max possible amount of y (number y-1 because counting beine from 0)
    if(::type == 2 || ::type == 4 || ::type == 6)//two floor figures
        max_y_iterator = 8;

    if(::mov_y >= max_y_iterator || figPosChecker(::mov_x, ::mov_y))
    {
        //write figure to global_field array
        int i, n;
        for(i = 0; i < 4; i++)
            for(n = 0; n < 4; n++)
            {
                //cout<< ::figure[i][n] <<endl;
                if(::figure[i][n] != false)
                    addPxToGlobalField(::mov_x + i, ::mov_y + n );
            }

        ::mov_x = rand() % (10 - mov_x_max); // random spawn in x range according to x size of figure
        ::mov_y = 0; // moving from top to the bottom
        ::type = rand() % 7; // 6 possible figures from 0 to 6
        // cout << "::mov_y >=10"<< endl;
        // creation of new figure
        figureInit();
        drawFigure(::type); // init figure array with figure number(::type)
    }
    moving(); // move along y and recall figure and global_field show functions

    score(); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! problem

    gameOver();
    drawField(); // draw net function
    glPopMatrix(); // for all scene
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1 * ::Scale, w + ::Scale, -1 * ::Scale, h + ::Scale, -1.0, 1.0);// x range; y range; z range
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



void key(unsigned char key, int x, int y)//change x, y, z for full scene rotating
{
    //printf("%d", key);
    switch(key)
    {
        case 97: // a
             ::mov_x--; // moving of the current figure along x
            break;
        case 100: // d
            ::mov_x++; // moving of the current figure along x
            break;
        case 32: // space
            transpFigure(); // transformation of mooving figure
            break;
        case 43: // +
            ::timer -= 100; // game speed changing
            break;
        case 45: // -
            ::timer += 100; // game speed changing
            break;
        case 121: // y
            globalFieldInit();
            for(int i = 0; i < 100; i++) // erase console output
                cout << endl;
            break;
    }

}


void timf(int value) // Timer function
{
    // x limitation
    if(::mov_x > 10 - ::mov_x_max)
        ::mov_x = 9 - ::mov_x_max;
    if(::mov_x <= 0)
        ::mov_x = 0;
    // game speed limitation
    if(::timer >= 1000) // min
        ::timer = 1000;
    if(::timer <= 100) // max
        ::timer = 100;

    display();
    glutTimerFunc(::timer, timf, 0); // Setup next timer
}


int main(int argc, char** argv)
{
    // one time used functions
    globalFieldInit(); // init arr for saving position of used figures
    srand(time(NULL)); // random number generator //
    // glut
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (::w + 2 * ::Scale, ::h + 2 * ::Scale);
    glutInitWindowPosition (1366/2 - ::w/2 - ::Scale, 250); // y = 250 for making appeared window in the middle of 1366 * 768 screen
    glutCreateWindow ("Tetris");
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(::timer, timf, 0); // timer
    glutKeyboardFunc(key); // key function
    glutMainLoop();

    return 0;
}


