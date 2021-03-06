// gcc temp.c -lGL -lGLU -lglut
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <string.h>

#define WINNING_SCORE 150
#define row 10
#define col 20
int placement[row][col];
int enem_dir[row][col];  //enem_dir store current direction of enemy at their index value
int enem_hist[row][col]; //enem_hist store if enemy have already moved.
int player_x, player_y;
int score = 0;

int paused = 0;
int game_over=0;
int game_won=0;

/*
    -2 indicates horizontal walls
    -1 indicates vertical walls
    0 indicates neutral
    1 indicates food
    2 indicates enemies
    3 indicate player

*/

void initialize_pos()
{
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
        {
            placement[i][j] = 1;
            enem_dir[i][j] = 0;
            enem_hist[i][j] = 0;
        }
    placement[0][0] = 3;
    player_x = 0;
    player_y = 0;
    //Enemy setup
    placement[4][4] = 2;
    placement[3][4] = 2;
    placement[1][7] = 2;

    enem_dir[3][4] = 'r';
    enem_dir[1][7] = 'u';
    enem_dir[4][4] = 'r';
    //Wall Setup
    // Wall upper block
    placement[9][2] = 2;
    enem_dir[9][2] = 'r';
    placement[9][1] = -1;
    placement[8][1] = -2;
    placement[8][2] = -2;
    placement[8][3] = -2;
    placement[8][4] = -2;
    placement[8][5] = -2;
    placement[8][6] = -2;
    placement[8][7] = -2;
    placement[8][8] = -2;
    placement[8][9] = 0;
    placement[8][10] = -2;
    placement[8][11] = -2;
    placement[8][12] = -2;
    placement[8][13] = -2;
    placement[8][14] = -2;
    placement[8][15] = -2;
    placement[8][16] = -2;
    placement[9][16] = -1;

    // Wall middle left
    placement[5][3] = -2;
    placement[5][4] = -2;
    placement[5][6] = -2;
    placement[5][7] = -2;
    placement[5][8] = -2;
    placement[5][9] = -2;
    placement[3][3] = -2;
    placement[3][4] = -2;
    placement[3][5] = -2;
    placement[3][6] = -2;
    placement[3][7] = -2;
    placement[3][8] = -2;
    placement[3][9] = -2;
}
void gameOver()
{
    paused=1;
    game_over=1;
    glRasterPos2f(47, 6 * 6);
    char *k = " G A M E -  O V E R ";
    for (int i = 0; i < strlen(k); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, k[i]);

    //Score Part
    char *s="Press R to Restart";
    glRasterPos2f(6 * 8, 5 * 6);
    int t=strlen(s);
    for (int i = 0; i < t; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
    return;
}

void gameWon()
{
    paused=1;
    game_won=1;
    game_over=1;
    glRasterPos2f(47, 6 * 6);
    char *k = " Y O U -  W O N !!!!!! ";
    for (int i = 0; i < strlen(k); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, k[i]);

    //Score Part
    char *s="Press R to Replay";
    glRasterPos2f(6 * 8, 5 * 6);
    int t=strlen(s);
    for (int i = 0; i < t; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
    return;
}
void restartGame(){
    initialize_pos();
    game_over=0;
    paused=0;
    score=0;
    game_won=0;
}
void moveEnemy(int i, int j)
{

    printf("%c\n", enem_dir[i][j]);
    if (enem_dir[i][j] == 'r')
    {
        if ((j + 1) < col && placement[i][j + 1] >= 0)
        {
            if (placement[i][j + 1] == 3)
            {
                gameOver();
                return;
            }
            placement[i][j] = 0;
            placement[i][j + 1] = 2;
            enem_dir[i][j] = 0;
            enem_dir[i][j + 1] = 'r';
            enem_hist[i][j + 1] = 1;
            printf("left");
        }
        else
        {
            if (placement[i][j - 1] == 3)
            {
                gameOver();
                return;
            }
            placement[i][j] = 1;
            placement[i][j - 1] = 2;
            enem_dir[i][j] = 0;
            enem_dir[i][j - 1] = 'l';
            enem_hist[i][j - 1] = 1;
        }
    }
    else if (enem_dir[i][j] == 'l')
    {
        if ((j - 1) >= 0 && placement[i][j - 1] >= 0)
        {
            if (placement[i][j - 1] == 3)
            {
                gameOver();
                return;
            }
            placement[i][j] = 1;
            placement[i][j - 1] = 2;
            enem_dir[i][j] = 0;
            enem_dir[i][j - 1] = 'l';
            enem_hist[i][j - 1] = 1;
            printf("right");
        }
        else
        {
            if (placement[i][j + 1] == 3)
            {
                gameOver();
                return;
            }
            placement[i][j] = 1;
            placement[i][j + 1] = 2;
            enem_dir[i][j] = 0;
            enem_dir[i][j + 1] = 'r';
            enem_hist[i][j + 1] = 1;
        }
    }
    else if (enem_dir[i][j] == 'u')
    {
        if ((i + 1) < row && placement[i + 1][j] >= 0)
        {
            if (placement[i + 1][j] == 3)
            {
                gameOver();
                return;
            }
            placement[i][j] = 1;
            placement[i + 1][j] = 2;
            enem_dir[i][j] = 0;
            enem_dir[i + 1][j] = 'u';
            enem_hist[i + 1][j] = 1;
            printf("up");
        }
        else
        {
            if (placement[i - 1][j] == 3)
            {
                gameOver();
                return;
            }
            placement[i][j] = 1;
            placement[i - 1][j] = 2;
            enem_dir[i][j] = 0;
            enem_dir[i - 1][j] = 'd';
            enem_hist[i - 1][j] = 1;
        }
    }
    else if (enem_dir[i][j] == 'd')
    {
        if ((i - 1) >= 0 && placement[i - 1][j] >= 0)
        {
            if (placement[i - 1][j] == 3)
            {
                gameOver();
                return;
            }
            placement[i][j] = 1;
            placement[i - 1][j] = 2;
            enem_dir[i][j] = 0;
            enem_dir[i - 1][j] = 'd';
            enem_hist[i - 1][j] = 1;
            printf("down");
        }
        else
        {
            if (placement[i + 1][j] == 3)
            {
                gameOver();
                return;
            }
            placement[i][j] = 1;
            placement[i + 1][j] = 2;
            enem_dir[i][j] = 0;
            enem_dir[i + 1][j] = 'u';
            enem_hist[i + 1][j] = 1;
        }
    }
    else if (enem_dir[i][j] == 0)
    {
        enem_dir[i][j] == 'u';
    }

    glutPostRedisplay();
}

void moveEnemies()
{
    if (paused == 0)
    {
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                enem_hist[i][j] = 0;

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (placement[i][j] == 2 && enem_hist[i][j] == 0)
                {
                    moveEnemy(i, j);
                }
            }
        }
    }
    glutTimerFunc(1000, moveEnemies, 0);
}

/* Note: x axis  extends column wise
         y axis extends row wise
         so placement[player_y][player_x] represents the current player position
*/
void showPlayer(int i, int j)
{
    glColor3f(0.2, 1, 0.2);
    glBegin(GL_QUAD_STRIP);
    glRotated(45, 1, 1, 0);
    glVertex2d(6 * j + 1, 6 * i + 1);
    glVertex2d(6 * (j + 1) - 1, 6 * i + 1);
    glVertex2d(6 * (j + 1) - 1, 6 * (i + 1) - 1);
    glVertex2d(6 * j + 1, 6 * (i + 1) - 1);
    glEnd();
    glRotated(0, 0, 0, 0);
}

void showEnemy(int i, int j)
{
    glColor3f(1, 0, 0);
    glBegin(GL_QUAD_STRIP);
    glVertex2d(6 * j + 1, 6 * i + 1);
    glVertex2d(6 * (j + 1) - 1, 6 * i + 1);
    glVertex2d(6 * (j + 1) - 1, 6 * (i + 1) - 1);
    glVertex2d(6 * j + 1, 6 * (i + 1) - 1);
    glEnd();
}

void showFood(int i, int j)
{
    glPointSize(2);
    glColor3f(0.5, 0.5, 1.0);
    glBegin(GL_POINTS);
    glVertex2d(j * 6 + 2, i * 6 + 2);
    glEnd();
}

void showWall(int i, int j)
{
    glColor3f(1, 1, 0);
    if (placement[i][j] == -1)
    {
        glLineWidth(10);
        glBegin(GL_LINES);
        glVertex2d(j * 6 + 3, i * 6 + 1);
        glVertex2d(j * 6 + 3, (i + 1) * 6 - 1);
        glEnd();
    }
    else
    {
        glLineWidth(10);
        glBegin(GL_LINES);
        glVertex2d(j * 6 + 3, i * 6 + 3);
        glVertex2d((j + 1) * 6, i * 6 + 3);
        glEnd();
    }
}

void showScoreBoard()
{

    //Title
    glRasterPos2f(47, 11 * 6);
    char *k = " P A C M A N ";
    for (int i = 0; i < strlen(k); i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, k[i]);

    //Score Part
    char s[15] = {'S', 'C', 'O', 'R', 'E', ':', ' '};
    sprintf(s + 7, "%d", score);
    int t = strlen(s);
    glRasterPos2f(6 * 8, 10 * 6);
    for (int i = 0; i < t; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (placement[i][j] == 1)
            {
                showFood(i, j);
            }
            else if (placement[i][j] == 3)
            {
                showPlayer(i, j);
            }
            else if (placement[i][j] == 2)
            {
                showEnemy(i, j);
            }
            else if (placement[i][j] == -1 || placement[i][j] == -2)
            {
                showWall(i, j);
            }
        }
    }
    if(game_over){
        if(game_won)
            gameWon();
        else
            gameOver();
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
    moveEnemies();
}

/*
     a->lefts
     d->right
     w->up
     s->down
*/
void mykeys(unsigned char key, int x, int y)
{
    printf("%c", key);
    if(game_over && key=='r'){
        restartGame();
    }

    if (paused && key == 'r')
    {
        paused = 0;
    }
    if (paused)
    {
        return;
    }
    switch (key)
    {
    case 'p':
        paused = 1;
        break;
    case 'w':
        if (player_y == row - 1)
            break;
        if (placement[player_y + 1][player_x] == 1)
        {
            // Food on upper block
            placement[player_y][player_x] = 0;
            player_y++;
            placement[player_y][player_x] = 3;
            score++;
            if(score>WINNING_SCORE){
                gameWon();
            }
        }
        else if (placement[player_y + 1][player_x] == 0)
        {
            // Nothing on upper block
            placement[player_y][player_x] = 0;
            player_y++;
            placement[player_y][player_x] = 3;
        }
        else if (placement[player_y + 1][player_x] == -1 || placement[player_y + 1][player_x] == -2)
        {
            // Wall on upper block
            //do nothing for now
        }
        else if (placement[player_y + 1][player_x] == 2)
        {
            // Enemy on upper block
            gameOver();
        }
        break;
    case 's':
        if (player_y == 0)
            break;
        if (placement[player_y - 1][player_x] == 1)
        {
            // Food on lower block
            placement[player_y][player_x] = 0;
            player_y--;
            placement[player_y][player_x] = 3;
            score++;
            if(score>WINNING_SCORE){
                gameWon();
            }
        }
        else if (placement[player_y - 1][player_x] == 0)
        {
            // Nothing on lower block
            placement[player_y][player_x] = 0;
            player_y--;
            placement[player_y][player_x] = 3;
        }
        else if (placement[player_y - 1][player_x] == -1 || placement[player_y - 1][player_x] == -2)
        {
            // Wall on lower block
            //do nothing for now
        }
        else if (placement[player_y - 1][player_x] == 2)
        {
            // Enemy on lower block
            gameOver();
        }
        break;
    case 'd':
        if (player_x == col - 1)
            break;
        if (placement[player_y][player_x + 1] == 1)
        {
            // Food on right block
            placement[player_y][player_x] = 0;
            player_x++;
            placement[player_y][player_x] = 3;
            score++;
            if(score>WINNING_SCORE){
                gameWon();
            }
        }
        else if (placement[player_y][player_x + 1] == 0)
        {
            // Nothing on right block
            placement[player_y][player_x] = 0;
            player_x++;
            placement[player_y][player_x] = 3;
        }
        else if (placement[player_y][player_x + 1] == -1 || placement[player_y][player_x + 1] == -2)
        {
            // Wall on right block
            //do nothing for now
        }
        else if (placement[player_y][player_x + 1] == 2)
        {
            // Enemy on right block
            gameOver();
        }
        break;
    case 'a':
        if (player_x == 0)
            break;
        if (placement[player_y][player_x - 1] == 1)
        {
            // Food on right block
            placement[player_y][player_x] = 0;
            player_x--;
            placement[player_y][player_x] = 3;
            score++;
            if(score>WINNING_SCORE){
                gameWon();
            }
        }
        else if (placement[player_y][player_x - 1] == 0)
        {
            // Nothing on right block
            placement[player_y][player_x] = 0;
            player_x--;
            placement[player_y][player_x] = 3;
        }
        else if (placement[player_y][player_x - 1] == -1 || placement[player_y][player_x - 1] == -2)
        {
            // Wall on right block
            //do nothing for now
        }
        else if (placement[player_y][player_x - 1] == 2)
        {
            // Enemy on right block
            gameOver();
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
    glutInitWindowSize(1200, 650);
    glutCreateWindow("Pacman");
    glutDisplayFunc(display);
    glutKeyboardFunc(mykeys);

    init();
    glutMainLoop();
    return 0;
}
