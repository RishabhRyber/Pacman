// gcc temp.c -lGL -lGLU -lglut


#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <string.h>

#define row 10
#define col 20
int placement[row][col];
int enem_dir[row][col]; //enem_dir store current direction of enemy at their index value 
int enem_hist[row][col]; //enem_hist store if enemy have already moved. 
int player_x,player_y;
int score=0;
/*
    -2 indicates horizontal walls
    -1 indicates vertical walls
    0 indicates neutral
    1 indicates food
    2 indicates enemies
    3 indicate player

*/
void initialize_pos(){
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++){
            placement[i][j]=1;
            enem_dir[i][j]=0;
            enem_hist[i][j]=0;
        }
        placement[0][0]=3;
        player_x=0;
        player_y=0;
        placement[5][5]=2;
        placement[3][4]=2;
        placement[1][7]=2;
        enem_dir[1][7]='r';
        enem_dir[3][4]='r';
        enem_dir[5][5]='r';

        placement[8][2]=-1;
        placement[1][4]=-1;
        placement[2][4]=-2;
        placement[2][5]=-2;
        placement[2][6]=-2;
        placement[2][7]=-2;
        
}

char nextDirection(int i,int j){
    
}

void moveEnemy(int i, int j){
    printf("%c\n",enem_dir[i][j]);
    if(enem_dir[i][j]=='r'){
        if((j+1)<col && placement[i][j+1]>0 ){
            placement[i][j]=1;
            placement[i][j+1]=2;
            enem_dir[i][j]=0;
            enem_dir[i][j+1]='r';
            enem_hist[i][j+1]=1;
            printf("left");
        }else
        {
            placement[i][j]=1;
            placement[i][j-1]=2;
            enem_dir[i][j]=0;
            enem_dir[i][j-1]='l';
            enem_hist[i][j-1]=1;

        }
            
    }
    else if(enem_dir[i][j]=='l'){
        
    }
    else if(enem_dir[i][j]=='u'){
        
    }
    else if(enem_dir[i][j]=='d'){
        
    }else if(enem_dir[i][j]==0){

    }
}

void moveEnemies(){

    for(int i=0;i<row;i++)
        for (int  j = 0; j < col; j++)
            enem_hist[i][j]=0;

    for(int i=0;i<row;i++){
        for (int  j = 0; j < col; j++)
        {
            if(placement[i][j]==2 && enem_hist[i][j]==0){
                moveEnemy(i,j);
            }
        }
        
    }
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

void showWall(int i,int j){
    glColor3f(1,1,0);
    if(placement[i][j]==-1){
        glLineWidth(10);
        glBegin(GL_LINES);
        glVertex2d(j*6+3,i*6+1);
        glVertex2d(j*6+3,(i+1)*6-1);
        glEnd();
    }else{
        glLineWidth(10);
        glBegin(GL_LINES);
        glVertex2d(j*6+3,i*6+3);
        glVertex2d((j+1)*6,i*6+3);
        glEnd();
    }
}

void showScoreBoard(){

    //Title
    glRasterPos2f(47,11*6);
    char *k=" P A C M A N ";
    for(int i=0;i<strlen(k);i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 , k[i]);

    //Score Part
    char s[15]={'S','C','O','R','E',':',' '};
    sprintf(s+7,"%d",score);
    int t = strlen(s);
    glRasterPos2f(6*8,10*6);
    for(int i=0;i<t;i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    moveEnemies();
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(placement[i][j]==1){
                showFood(i,j);
            }
            else if(placement[i][j]==3){
                showPlayer(i,j);
            }else if(placement[i][j]==2){
                showEnemy(i,j);
            }else if(placement[i][j]==-1||placement[i][j]==-2){
                showWall(i,j);
            }
        }
    }
    showScoreBoard();
    glFlush();
}

void init()
{
    glViewport(0, 0, 500, 500);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 120.0, 0, 70.0);
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
        }else if(placement[player_y+1][player_x]==-1 || placement[player_y+1][player_x]==-2){
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
        }else if(placement[player_y-1][player_x]==-1 || placement[player_y-1][player_x]==-2){
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
        }else if(placement[player_y][player_x+1]==-1 || placement[player_y][player_x+1] == -2){
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
        }else if(placement[player_y][player_x-1]==-1 || placement[player_y][player_x-1]==-2){
            // Wall on right block
            //do nothing for now
        }else if(placement[player_y][player_x-1]==2){
            // Enemy on right block
            exit(0);
        }
        break;

    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    initialize_pos();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(1200,650);
    glutCreateWindow("Pacman");
    glutDisplayFunc(display);
    glutKeyboardFunc(mykeys);

    init();
    glutMainLoop();
    return 0;
}
