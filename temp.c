// gcc temp.c -lGL -lGLU -lglut


#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define row 10
#define col 20
int placement[row][col];
int player_x,player_y;
int score=0;
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
        placement[5][5]=2;
        placement[3][4]=2;
        placement[1][7]=2;
        placement[9][2]=2;

}

/* Note: x axis  extends column wise
         y axis extends row wise
         so placement[player_y][player_x] represents the current player position
*/
void showPlayer(int i,int j){
    glColor3f(0.2, 1, 0.2);
    glBegin(GL_QUAD_STRIP);
    glVertex2d(6*j+1,6*i+1);
    glVertex2d(6*(j+1)-1,6*i+1);
    glVertex2d(6*(j+1)-1,6*(i+1)-1);
    glVertex2d(6*j+1,6*(i+1)-1);
    glEnd();
}

void showEnemy(int i,int j){
    glColor3f(1, 0, 0);
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
            else if(placement[i][j]==3){
                showPlayer(i,j);
            }else if(placement[i][j]==2){
                showEnemy(i,j);
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





/*
     a->lefts
     d->right
     w->up
     s->down
*/
void mykeys(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        if(player_y == row-1)
            break;
        if(placement[player_y+1][player_x]==1){
            // Food on upper block
            placement[player_y][player_x]=0;
            player_y++;
            placement[player_y][player_x]=3;
            score++;            
        }else if(placement[player_y+1][player_x]==0){
            // Nothing on upper block
            placement[player_y][player_x]=0;
            player_y++;
            placement[player_y][player_x]=3;
        }else if(placement[player_y+1][player_x]==-1){
            // Wall on upper block
            //do nothing for now
        }else if(placement[player_y+1][player_x]==2){
            // Enemy on upper block
            exit(0);
        }
        break;
    case 's':
        if(player_y==0)
            break;
        if(placement[player_y-1][player_x]==1){
            // Food on lower block
            placement[player_y][player_x]=0;
            player_y--;
            placement[player_y][player_x]=3;
            score++;            
        }else if(placement[player_y-1][player_x]==0){
            // Nothing on lower block
            placement[player_y][player_x]=0;
            player_y--;
            placement[player_y][player_x]=3;
        }else if(placement[player_y-1][player_x]==-1){
            // Wall on lower block
            //do nothing for now
        }else if(placement[player_y-1][player_x]==2){
            // Enemy on lower block
            exit(0);
        }
        break;
    case 'd':
        if(player_x==col-1)
            break;
        if(placement[player_y][player_x+1]==1){
            // Food on right block
            placement[player_y][player_x]=0;
            player_x++;
            placement[player_y][player_x]=3;
            score++;            
        }else if(placement[player_y][player_x+1]==0){
            // Nothing on right block
            placement[player_y][player_x]=0;
            player_x++;
            placement[player_y][player_x]=3;
        }else if(placement[player_y][player_x+1]==-1){
            // Wall on right block
            //do nothing for now
        }else if(placement[player_y][player_x+1]==2){
            // Enemy on right block
            exit(0);
        }
        break;
    case 'a':
        if(player_x==0)
            break;
        if(placement[player_y][player_x-1]==1){
            // Food on right block
            placement[player_y][player_x]=0;
            player_x--;
            placement[player_y][player_x]=3;
            score++;            
        }else if(placement[player_y][player_x-1]==0){
            // Nothing on right block
            placement[player_y][player_x]=0;
            player_x--;
            placement[player_y][player_x]=3;
        }else if(placement[player_y][player_x-1]==-1){
            // Wall on right block
            //do nothing for now
        }else if(placement[player_y][player_x-1]==2){
            // Enemy on right block
            exit(0);
        }
        break;

    }
    moveEmemies();
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
