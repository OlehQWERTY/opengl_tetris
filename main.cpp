/*
avoid colision
*/

#include <GL/freeglut.h>
//#include <stdio.h>
#include <iostream>
//#include <fstream>
#include <stdlib.h> // some string functions


using namespace std;


static int movX = 0, movY = 0, timerSpeed = 400;

bool ** initArr(int x, int y) // init arr[x][y] with false and give memory for this array
{

    bool ** ptrArr = new bool* [10];
    for (int count = 0; count < 10; count++)
        ptrArr[count] = new bool [10];
    for (int i = 0; i < x; i++)
        for (int n = 0; n < y; n++)
            ptrArr[i][n] = false;
    return ptrArr;
}

void deleteArr(bool ** &ptrArr, int i)
{
    for (int count = 0; count < i; count++)
        delete [] ptrArr[count];

    cout << "Delete ptrArr[" << i << ']' << endl;
}

void maxXY(bool **arr, int sizeX, int sizeY, int &maxX, int &maxY)
{
    int iterrationMaxY = 0;
    for (int i = 0; i < sizeX; i++)
    {
        for (int n = 0; n < sizeY; n++)
        {
            if(arr[i][n] == true)
            {
                iterrationMaxY++;
                maxX = i+1;
            }
        }
        cout << "iterrationMaxY = " << iterrationMaxY << endl;
        if(iterrationMaxY > maxY)
            maxY = iterrationMaxY;
        iterrationMaxY = 0;
    }
}

bool limitArrInField(bool ** &arr, int sizeX1, int sizeY1, int sizeX2, int sizeY2, int &x, int &y, int maxX, int maxY)
{
// arr - inserted arr, sizeX1 & sizeY1 - size of arr, sizeX2 & sizeY2 - size of limittation, x & y - position for inserting arr in limittation
    if(x + maxX > sizeX2 || y + maxY > sizeY2 || x < 0 || y < 0)
    {
        if(x < 0) // if x out of available range this return it in 0 - 10 range
            x = 0;
        if(x + maxX >= 10)
            x = 10 - maxX;
        cout << "Error. Your array out of main array." << endl;
        return false;
    }
    else
        ;
    return true;
}

bool avoidColision()
{

}

void initGameObj(bool ** &ptrArr, int type)
{
    // cout << "DrawFigure()" << endl;
    switch(type)
    {
        case 0:
            ptrArr[0][0] = true;
            break;
        case 1:
            ptrArr[0][0] = true;
            ptrArr[1][0] = true;
            break;
        case 2:
            ptrArr[0][0] = true;
            ptrArr[1][0] = true;
            ptrArr[1][1] = true;
            break;
        case 3:
            ptrArr[0][0] = true;
            ptrArr[1][0] = true;
            ptrArr[2][0] = true;
            break;
        case 4:
            ptrArr[0][0] = true;
            ptrArr[1][0] = true;
            ptrArr[2][0] = true;
            ptrArr[1][1] = true;
            break;
        case 5:
            ptrArr[0][0] = true;
            ptrArr[1][0] = true;
            ptrArr[2][0] = true;
            ptrArr[3][0] = true;
            break;
        case 6:
            ptrArr[0][0] = true;
            ptrArr[1][0] = true;
            ptrArr[0][1] = true;
            ptrArr[1][1] = true;
            break;
    }
}

void drawGameField(int widthPx, int heightPx, int scale)
{
    glColor3f(1,1,1); // Color of Fields
    glBegin(GL_LINES);
    for (int i = 0; i <= widthPx; i += scale)
    {
        glVertex2i(i, 0);
        glVertex2i(i, heightPx);
    }
    for (int n = 0; n <= heightPx; n += scale)
    {
        glVertex2i(0, n);
        glVertex2i(widthPx, n);
    }
    glEnd();
}

void drawCube(int x, int y, int color, int scale)
{
    glBegin(GL_POLYGON);
    switch(color)
    {
        case 0:
            glColor3f(0, 1, 1 );
            break;
        case 1:
            glColor3f(1, 0, 1);
            break;
        case 2:
            glColor3f(0, 0, 1);
            break;
        default:
            glColor3f(0.5, 0.5, 0.5);
            break;
    }

    glVertex2i(scale * x, y * scale);
    glVertex2i(scale * x, (y + 1) * scale);
    glVertex2i(scale * (x + 1), (y + 1) * scale);
    glVertex2i(scale * (x + 1), y * scale);

    glEnd();

}

void insertArrToArr(bool ** &arr, bool ** &arr2, int sizeX1, int sizeY1, int sizeX2, int sizeY2, int x, int y)
{
// arr - bigger arr, arr2 - inserted arr, sizeX1 & sizeY1 - size of arr, sizeX2 & sizeY2 - size of arr2, x & y - position for inserting arr2 in arr
    for (int i = 0; i < sizeX1; i++)
        for (int n = 0; n < sizeY1; n++)
            if(arr2[i][n] == true)
                if(x + i < sizeX1 || y + n < sizeY1)
                    arr[x+i][y+n] = true;
                else
                    cout << "Error. Your array out of main array." << endl;
}


void printArrOpenGl(bool **arr, int scale, int color, int sizeX, int sizeY, int x, int y)
{
    for (int i = 0; i < sizeX; i++)
        for (int n = 0; n < sizeY; n++)
            if(arr[i][n] == true)
                drawCube(i + x, n + y, color, scale);
}

void gameDisplay()
{
    bool ** gameFieldArr = initArr(10, 10);
    bool ** gameObjArr = initArr(4, 4);
    initGameObj(gameObjArr, 5);
    int maxX = 0, maxY = 0;
    maxXY(gameObjArr, 4, 4, maxX, maxY);
    cout << "maxX = " << maxX << endl;
    cout << "maxY = " << maxY << endl;
    static int color = 0;
    if(::movY >= 10) // moving object along y axis
    {
        ::movY = 0;
        ::movX = rand() % (10 - maxX + 1); // random spawn in x range according to x size of figure
        color = rand() % 3;
    }

    cout << "X = " << movX << endl;
    cout << "Y = " << movY << endl;

    limitArrInField(gameObjArr, 4, 4, 10, 10, ::movX, ::movY, maxX, maxY);
    printArrOpenGl(gameObjArr, 50, color, 4, 4, ::movX, ::movY);
    ::movY++; // moving object along y axis

    drawGameField(500, 500, 50);

    deleteArr(gameFieldArr, 10);
    deleteArr(gameObjArr, 4);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix(); // for all scene
    int scale = 50; // *************************** change this func
    int r_x = 0 + scale;
    int r_y = 0 + scale;
    int r_z = 0;
    glTranslatef(r_x, r_y, r_z);//transform scene possition x y z

    gameDisplay();


    glPopMatrix(); // for all scene
    glutSwapBuffers();
}

void reshape(int widthPx, int heightPx)
{
    glViewport (0, 0, widthPx, heightPx);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-50, widthPx + 50, -50, heightPx + 50);// x range; y range
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



void key(unsigned char key, int x, int y)//change x, y, z for full scene rotating
{
    //printf("%d", key);
    switch(key)
    {
        case 97: // a
             ::movX--; // moving of the current figure along x
            break;
        case 100: // d
            ::movX++; // moving of the current figure along x
            break;
        //case 32: // space
            //transpFigure(); // transformation of mooving figure
            //break;
        case 43: // +
            ::timerSpeed -= 100; // game speed changing
            break;
        case 45: // -
            ::timerSpeed += 100; // game speed changing
            break;
        /*case 121: // y
            globalFieldInit();
            for(int i = 0; i < 100; i++) // erase console output
                cout << endl;
            break;*/
    }

}


void timf(int value) // Timer function
{

    // game speed limitation
    if(::timerSpeed >= 1000) // min
        ::timerSpeed = 1000;
    if(::timerSpeed <= 100) // max
        ::timerSpeed = 100;

    display();
    glutTimerFunc(::timerSpeed, timf, 0); // Setup next timer
}

void init(void)
{
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    int widthPx = 600, heightPx = 600, scale = 50;
    glutInitWindowSize (widthPx, heightPx);
    glutInitWindowPosition (1366/2 - widthPx/2 - scale, 250); // y = 250 for making appeared window in the middle of 1366 * 768 screen
    glutCreateWindow ("Tetris");
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(::timerSpeed, timf, 0); // timer
    glutKeyboardFunc(key); // key function
    glutMainLoop();
}

int main(int argc, char** argv)
{
    // one time used functions
    srand(time(NULL)); // random number generator //
    // glut
    glutInit(&argc, argv);
    init();

    return 0;
}


