#include <graphics.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>

#define INSIDE 0
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

// Clipping window
int xmin = 100, ymin = 100, xmax = 400, ymax = 300;

// -------- REGION CODE --------
int computeCode(int x, int y)
{
    int code = INSIDE;

    if (x < xmin) code |= LEFT;
    else if (x > xmax) code |= RIGHT;
    if (y < ymin) code |= BOTTOM;
    else if (y > ymax) code |= TOP;

    return code;
}

// -------- COHEN SUTHERLAND --------
void cohenSutherland(int x1, int y1, int x2, int y2)
{
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);

    int accept = 0;

    while (1)
    {
        if ((code1 == 0) && (code2 == 0))
        {
            accept = 1;
            break;
        }
        else if (code1 & code2)
        {
            break;
        }
        else
        {
            int codeOut;
            int x, y;

            if (code1 != 0)
                codeOut = code1;
            else
                codeOut = code2;

            if (codeOut & TOP)
            {
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;
            }
            else if (codeOut & BOTTOM)
            {
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;
            }
            else if (codeOut & RIGHT)
            {
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;
            }
            else
            {
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                x = xmin;
            }

            if (codeOut == code1)
            {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            }
            else
            {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }

    if (accept)
    {
        setcolor(GREEN);
        line(x1, y1, x2, y2);
    }
}

// -------- MIDPOINT CLIPPING --------
void midpointClip(int x1, int y1, int x2, int y2)
{
    int code1, code2;
    int xm, ym;

    code1 = computeCode(x1, y1);
    code2 = computeCode(x2, y2);

    if ((code1 == 0) && (code2 == 0))
    {
        setcolor(YELLOW);
        line(x1, y1, x2, y2);
        return;
    }

    if (code1 & code2)
    {
        return;
    }

    xm = (x1 + x2) / 2;
    ym = (y1 + y2) / 2;

    if (abs(x1 - x2) < 2 && abs(y1 - y2) < 2)
        return;

    midpointClip(x1, y1, xm, ym);
    midpointClip(xm, ym, x2, y2);
}

// -------- MAIN --------
void main()
{
    int gd = DETECT, gm;
    int x1, y1, x2, y2, choice;

    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    // Draw clipping window
    rectangle(xmin, ymin, xmax, ymax);

    printf("Enter line (x1 y1 x2 y2): ");
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

    // Draw original line
    setcolor(RED);
    line(x1, y1, x2, y2);

    printf("\n1. Cohen Sutherland\n2. Midpoint Clipping\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            cohenSutherland(x1, y1, x2, y2);
            break;

        case 2:
            midpointClip(x1, y1, x2, y2);
            break;

        default:
            printf("Invalid choice");
    }

    getch();
    closegraph();
}