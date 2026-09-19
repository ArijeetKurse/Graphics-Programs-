#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <dos.h>

// -------- Bresenham Line Drawing --------
void drawLine(int x1, int y1, int x2, int y2)
{
    int dx, dy, sx, sy, err, e2;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    sx = (x1 < x2) ? 1 : -1;
    sy = (y1 < y2) ? 1 : -1;
    err = dx - dy;

    while (1)
    {
        putpixel(x1, y1, WHITE);

        if (x1 == x2 && y1 == y2)
            break;

        e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

// -------- Midpoint Circle Drawing --------
void drawCircle(int xc, int yc, int r)
{
    int x, y, p;

    x = 0;
    y = r;
    p = 1 - r;

    while (x <= y)
    {
        putpixel(xc + x, yc + y, WHITE);
        putpixel(xc - x, yc + y, WHITE);
        putpixel(xc + x, yc - y, WHITE);
        putpixel(xc - x, yc - y, WHITE);
        putpixel(xc + y, yc + x, WHITE);
        putpixel(xc - y, yc + x, WHITE);
        putpixel(xc + y, yc - x, WHITE);
        putpixel(xc - y, yc - x, WHITE);

        x++;

        if (p < 0)
            p = p + 2 * x + 1;
        else
        {
            y--;
            p = p + 2 * (x - y) + 1;
        }
    }
}

// -------- Main Animation --------
void main()
{
    int gd = DETECT, gm;
    int i;

    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    for (i = 50; i < 400; i += 5)
    {
        cleardevice();

        drawLine(0, 300, 640, 300);   // road
        drawCircle(i, 280, 20);       // moving ball

        delay(50);
    }

    getch();
    closegraph();
}