#include <GL/freeglut.h>
#include <stdio.h>
#include <iostream>//cout
#include <fstream>
#include <stdlib.h>//some string functions

using namespace std;
//comment just for test

// i - стовпчики (x), n - рядки (y)

const int I=10, N=10;//Fields amount
const int Scale=50;//Fields size
const int w = Scale*I, h = Scale*N;
int timer = 100; //game speed
int mov_x = 5, mov_x_max = 0, mov_y = 0, type = 0;
bool figure[4][4], global_field[10][10];
void display(void);




void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
}

void DrawField()//Drowing of Fields
{
    glColor3f(1,1,1);//Color of Fields
    glBegin(GL_LINES);
    //xy
    for (int i=0; i<=w; i+=Scale)
      {glVertex3f(i,0,0); glVertex3f(i,h,0);}
    for (int n=0; n<=h; n+=Scale)
      {glVertex3f(0,n,0); glVertex3f(w,n,0);}

    glEnd();
}

void DrawCube(int x, int y, int color)
{
    if(x >= ::I)
        cout << "Error 1: Cube X position out of game field!" << endl;
    else if(y>= ::N)
        cout << "Error 1: Cube Y position out of game field!" << endl;
    else
    {
        glBegin(GL_POLYGON);

        if(color==0)
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

void global_field_init()
{
    for(int i=0; i<10; i++)
        for(int n=0;n<10;n++)
            ::global_field[i][n]=false;
}

void figure_init()
{
    for(int i=0; i<4; i++)
        for(int n=0;n<4;n++)
            ::figure[i][n]=false;

}

void DrawFigure(int type)
{
//cout<<"DrawFigure()"<<endl;
    switch(type)
    {
        case 0:
            ::figure[0][0]=true;
            ::mov_x_max = 0;//зміщення x відносно координати x (якщо фігура по x займає ще одну клітинку поряд з початковою клатинкою то зміщення x = 1 якщо фігура це один кубик то зміщення 0)
            break;
        case 1:
            ::figure[0][0]=true;
            ::figure[1][0]=true;
            ::mov_x_max = 1;
            break;
        case 2:
            ::figure[0][0]=true;
            ::figure[1][0]=true;
            ::figure[1][1]=true;
            ::mov_x_max = 1;
            break;
        case 3:
            ::figure[0][0]=true;
            ::figure[1][0]=true;
            ::figure[2][0]=true;
            ::mov_x_max = 2;
            break;
        case 4:
            ::figure[0][0]=true;
            ::figure[1][0]=true;
            ::figure[2][0]=true;
            ::figure[1][1]=true;
            ::mov_x_max = 2;
            break;
        case 5:
            ::figure[0][0]=true;
            ::figure[1][0]=true;
            ::figure[2][0]=true;
            ::figure[3][0]=true;
            ::mov_x_max = 3;
            break;
        case 6:
            ::figure[0][0]=true;
            ::figure[1][0]=true;
            ::figure[0][1]=true;
            ::figure[1][1]=true;
            ::mov_x_max = 1;
            break;
    }
}

void transp_figure()//it needs dome chainging (after transp change position)
{
    //cout<<"transp: "<<endl;
    bool transp[4][4];
    for(int i=0; i<4; i++)
        for(int n=0;n<4;n++)
            transp[i][n] = ::figure[i][n];

        for(int i=0; i<4; i++)
        {
            for(int n=0;n<4;n++)
            {
                figure[i][n]=transp[n][i];
                //cout<<figure[i][n]<< ' ';
            }
            //cout<<endl;
        }

}


void add_px_to_global_field(int x, int y)
{
    ::global_field[x][y]=true;
}

void global_field_show()
{
    int i, n;
    for(i=0; i<10; i++)
        for(n=0;n<10;n++)
        {
            //cout<<::figure[i][n]<<endl;
            if(::global_field[i][n]!=false)
                DrawCube(i, n, 0);
        }

}

bool fig_pos_checker( int x, int y)
{
    int i, n;

    for(i=0; i<4; i++)
        for(n=0;n<4;n++)
            if(::figure[i][n]!=false)
                if(::global_field[x+i][y+n+1]==true)
                    return true;
    return false;

}

void figure_show( int x, int y)
{
    int i, n;
    for(i=0; i<4; i++)
        for(n=0;n<4;n++)
        {
            if(::figure[i][n]!=false)
            {
                   DrawCube(x+i, y+n, 1);
            }
        }
}

void score()
{
    int o=0;
    for(int n=0; n<10; n++)
    {
        for(int i=0; i<10; i++)
            if(::global_field[i][n]==true)
            {
                cout<<"+1"<<endl;
                o++;
                if(o>=9)
                     for(int n1=n-1; n1>0; n1--)
                        for(int i1=0; i1<10; i1++)
                        {
                            ::global_field[i1][n1]=::global_field[i1][n1+1];
                            ::global_field[i1][n]=false;
                        }

            }
        o = 0;
    }
}

void moving()
{

            global_field_show();//old figures
            figure_show(::mov_x, ::mov_y);//current moving figure
            ::mov_y++;//y moving

}

void game_over()
{
    for(int i=0; i<10; i++)
        if(::global_field[i][1]==true)
        {
            cout<<"Game over! Press, any key to continue!"<<endl;
            for(int i=0; i<10; i++)//erase of ::global_field
                for(int n=0;n<10;n++)
                    ::global_field[i][n]=true;
        }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();//for all scene
    int r_x = 0 + ::Scale;//узгодити
    int r_y = 0 + ::Scale;
    int r_z = 0;
    glTranslatef(r_x, r_y, r_z);//transform scene possition x y z
    //glRotatef(::x, 1.0, 0.0, 0.0);//full scene rotation
    //glRotatef(::y, 0.0, 1.0, 0.0);//full scene rotation
    //glRotatef(::z, 0.0, 0.0, 1.0);//full scene rotation
    //glTranslatef(-1*r_x, -1*r_y, -1*r_z);//rotate round point x y z


    int max_y_iterator = 9;//max possible amount of y (number y-1 because counting beine from 0)
    if(::type == 2 || ::type == 4 || ::type == 6)//two floor figures
        max_y_iterator = 8;

    if(::mov_y >= max_y_iterator || fig_pos_checker(::mov_x, ::mov_y))
    {
        //write figure to global_field array
        int i, n;
        for(i=0; i<4; i++)
            for(n=0;n<4;n++)
            {
                //cout<<::figure[i][n]<<endl;
                if(::figure[i][n]!=false)
                    add_px_to_global_field(::mov_x + i, ::mov_y + n );
            }



        ::mov_x = rand() % (10 - mov_x_max);//random spawn in x range according to x size of figure
        ::mov_y = 0; //moving from top to the bottom
        ::type = rand() % 7;//6 possible figures from 0 to 6
        //cout << "::mov_y >=10"<< endl;

        //creation of new figure
        figure_init();
        DrawFigure(::type);//init figure array with figure number(::type)
    }
    moving();//move along y and recall figure and global_field show functions





    score();//проблема





    game_over();

    DrawField();//draw net function

    glPopMatrix();//for all scene
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);//узгодити
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1 * ::Scale, w + ::Scale, -1 * ::Scale, h + ::Scale, -1.0, 1.0);// x range; y range; z range
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



void key(unsigned char key, int x, int y)//change x, y, z for full scene rotating
{
printf("%d", key);
    switch(key)
    {
    case 97:
         //a
         ::mov_x--;//moving of the current figure along x
        break;
    case 100:
        //d
        ::mov_x++;//moving of the current figure along x
        break;
    case 32:
        //space
        transp_figure();//rotation of figures
        break;
    case 43://+
        ::timer-=100;//game speed changing
        break;
    case 45://-
        ::timer+=100;//game speed changing
        break;
        case 121://y
        global_field_init();
        for(int i=0; i<100; i++)
            cout<<endl;
        break;
    }

}


void timf(int value) // Timer function
{
    //x limitation
    if(::mov_x>10 - ::mov_x_max)
        ::mov_x = 9 - ::mov_x_max;
    if(::mov_x<=0)
        ::mov_x = 0;
    //game speed limitation
    if(::timer>=1000)//min
        ::timer = 1000;
    if(::timer<=100)//max
        ::timer = 100;

    display();



    glutTimerFunc(::timer, timf, 0); // Setup next timer
}


int main(int argc, char** argv)
{
//one time used functions
    global_field_init();//init arr for saving position of used figures
    srand(time(NULL)); /* seed random number generator */
//glut
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (::w + 2 * ::Scale, ::h + 2 * ::Scale);
    glutInitWindowPosition (1366/2 - ::w/2 - ::Scale, 250);//y = 250 because problem with vertical line in os
    glutCreateWindow ("Tetris");//argv[0]
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(::timer, timf, 0);//timer
    glutKeyboardFunc(key);//key function
    glutMainLoop();



    return 0;
}


