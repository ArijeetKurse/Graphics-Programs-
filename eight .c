#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>

#define N 8

// Cube vertices (x,y,z)
float cube[N][3] = {
    {50,50,50}, {100,50,50}, {100,100,50}, {50,100,50},
    {50,50,100}, {100,50,100}, {100,100,100}, {50,100,100}
};

// Edges of cube
int edges[12][2] = {
    {0,1},{1,2},{2,3},{3,0},
    {4,5},{5,6},{6,7},{7,4},
    {0,4},{1,5},{2,6},{3,7}
};

// Projection (ignore z)
void project(float x, float y, float z, int *xp, int *yp)
{
    *xp = (int)(x + 200);
    *yp = (int)(y + 200);
}

// Draw cube
void drawCube(float obj[N][3], int color)
{
    int i;
    int x1,y1,x2,y2;

    setcolor(color);

    for(i=0;i<12;i++)
    {
        project(obj[edges[i][0]][0], obj[edges[i][0]][1], obj[edges[i][0]][2], &x1, &y1);
        project(obj[edges[i][1]][0], obj[edges[i][1]][1], obj[edges[i][1]][2], &x2, &y2);

        line(x1,y1,x2,y2);
    }
}

// Copy cube
void copyCube(float src[N][3], float dest[N][3])
{
    int i,j;
    for(i=0;i<N;i++)
        for(j=0;j<3;j++)
            dest[i][j] = src[i][j];
}

// Translation
void translate(float obj[N][3], int tx, int ty, int tz)
{
    int i;
    for(i=0;i<N;i++)
    {
        obj[i][0] += tx;
        obj[i][1] += ty;
        obj[i][2] += tz;
    }
}

// Scaling
void scale(float obj[N][3], float sx, float sy, float sz)
{
    int i;
    for(i=0;i<N;i++)
    {
        obj[i][0] *= sx;
        obj[i][1] *= sy;
        obj[i][2] *= sz;
    }
}

// Rotation about X-axis
void rotateX(float obj[N][3], float angle)
{
    int i;
    float rad = angle * 3.14159 / 180;
    float y,z;

    for(i=0;i<N;i++)
    {
        y = obj[i][1];
        z = obj[i][2];

        obj[i][1] = y*cos(rad) - z*sin(rad);
        obj[i][2] = y*sin(rad) + z*cos(rad);
    }
}

// -------- MAIN --------
int main()
{
    int gd = DETECT, gm;

    float temp[N][3];

    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    // Original cube
    copyCube(cube, temp);
    drawCube(temp, WHITE);
    outtextxy(10,10,"Original Cube");
    getch();

    // Translation
    copyCube(cube, temp);
    translate(temp, 100, 50, 50);
    drawCube(temp, GREEN);
    outtextxy(10,30,"Translated");
    getch();

    // Scaling
    copyCube(cube, temp);
    scale(temp, 1.5, 1.5, 1.5);
    drawCube(temp, CYAN);
    outtextxy(10,50,"Scaled");
    getch();

    // Rotation
    copyCube(cube, temp);
    rotateX(temp, 45);
    drawCube(temp, YELLOW);
    outtextxy(10,70,"Rotated X-axis");
    getch();

    closegraph(ALL_WINDOWS);
    return 0;
}