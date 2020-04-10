// gcc temp.c -lGL -lGLU -lglut


#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define row 10
#define col 20
int placement[row][col];
int player_x,player_y;
/*
    0 indicates neutral
    1 indicates food
    2 indicates enemies
    3 indicate player
    -1 indicates walls

*/
void initialize_pos(){
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++){
            placement[i][j]=1;
            printf("lol%d ",placement[i][j]);
            
        }
        placement[0][0]=3;
        player_x=0;
        player_y=0;

}


void showPlayer(int i,int j){
    glColor3f(0.2, 1, 0.2);
    glBegin(GL_QUAD_STRIP);
    glVertex2d(6*j+1,6*i+1);
    glVertex2d(6*(j+1)-1,6*i+1);
    glVertex2d(6*(j+1)-1,6*(i+1)-1);
    glVertex2d(6*j+1,6*(i+1)-1);
    glEnd();
}

void showFood(int i,int j){
    glPointSize(2);
    glColor3f(0.5, 0.5, 1.0);

    glBegin(GL_POINTS);
    glVertex2d(j*6+2,i*6+2);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(placement[i][j]==1){
                showFood(i,j);
                printf("lol\n");
            }
            if(placement[i][j]==3){
                showPlayer(i,j);
            }
        }

    }
    glFlush();
}

void init()
{
    glViewport(0, 0, 500, 500);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 120.0, 0, 60.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(0.5, 0.5, 1.0);
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

/*normal keys interaction for transformation
u -- up, d--down, r--right l--left
i -- increase size, D -- decrease size
RL- rotate left  RR --rotate right
*/

void mykeys(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':

        glTranslatef(-2.0, 0.0f, 0.0f);
        break;
    case 'r':
        glTranslatef(2.0, 0.0f, 0.0f);
        break;
    case 'u':
        glTranslatef(0.0f, 2.0, 0.0f);
        break;
    case 'd':
        glTranslatef(0.0, -2.0, 0.0);
        break;
    case 'i':
        glScalef(1.5, 1.5, 1.5);
        break;
    case 'D':;
        glScalef(-0.5, -0.5, -0.5);
        break;
    case 'R':
        glRotatef(10, 1.0, 1.0, 0.0);
        break;
    case 'L':
        glRotatef(-10, 1.0, 0.0, 0.0);
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    initialize_pos();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(1200,600);
    glutCreateWindow("Transformation with out APIs");
    glutDisplayFunc(display);
    glutKeyboardFunc(mykeys);

    init();
    glutMainLoop();
    return 0;
}
