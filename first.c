#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

void drawLineDDA(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;

    float x = x1;
    float y = y1;

    int i;
    for(i = 0; i <= steps; i++)
    {
        putpixel((int)(x + 0.5), (int)(y + 0.5), WHITE);
        x += xInc;
        y += yInc;
    }
}

void drawLineBresenham(int x1, int y1, int x2, int y2)
{
    int dx, dy, sx, sy, err, e2;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);

    sx = (x1 < x2) ? 1 : -1;
    sy = (y1 < y2) ? 1 : -1;

    err = dx - dy;

    while(1)
    {
        putpixel(x1, y1, WHITE);

        if (x1 == x2 && y1 == y2)
            break;

        e2 = 2 * err;

        if (e2 > -dy)
        {
            err = err - dy;
            x1 = x1 + sx;
        }

        if (e2 < dx)
        {
            err = err + dx;
            y1 = y1 + sy;
        }
    }
}
void main()
{
    int gd = DETECT, gm;

    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    // DDA Line
    drawLineDDA(100, 100, 300, 200);

    // Bresenham Line
    drawLineBresenham(100, 200, 300, 300);

    getch();
    closegraph();
}