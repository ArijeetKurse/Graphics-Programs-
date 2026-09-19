
#include <graphics.h>
#include <conio.h>
#include <stdio.h>

#define MAX 20

// Clipping window
int xmin = 150, ymin = 150, xmax = 450, ymax = 350;

// Function to draw polygon
void drawPolygon(int x[], int y[], int n, int color)
{
    int i;
    setcolor(color);

    for(i = 0; i < n - 1; i++)
        line(x[i], y[i], x[i+1], y[i+1]);

    line(x[n-1], y[n-1], x[0], y[0]);
}

// Check inside for each edge
int inside(int x, int y, int edge)
{
    switch(edge)
    {
        case 0: return x >= xmin; // left
        case 1: return x <= xmax; // right
        case 2: return y >= ymin; // bottom
        case 3: return y <= ymax; // top
    }
    return 0;
}

// Find intersection
void intersect(int x1, int y1, int x2, int y2, int *x, int *y, int edge)
{
    float m;

    if (x2 != x1)
        m = (float)(y2 - y1) / (x2 - x1);
    else
        m = 0;

    if(edge == 0) // left
    {
        *x = xmin;
        *y = y1 + (xmin - x1) * m;
    }
    else if(edge == 1) // right
    {
        *x = xmax;
        *y = y1 + (xmax - x1) * m;
    }
    else if(edge == 2) // bottom
    {
        *y = ymin;
        if(x2 != x1)
            *x = x1 + (ymin - y1) / m;
    }
    else if(edge == 3) // top
    {
        *y = ymax;
        if(x2 != x1)
            *x = x1 + (ymax - y1) / m;
    }
}

// Sutherland Hodgman Clipping
int clip(int x[], int y[], int n, int edge)
{
    int newx[MAX], newy[MAX];
    int i, k = 0;

    int x1, y1, x2, y2;
    int in1, in2;

    for(i = 0; i < n; i++)
    {
        x1 = x[i];
        y1 = y[i];
        x2 = x[(i+1)%n];
        y2 = y[(i+1)%n];

        in1 = inside(x1, y1, edge);
        in2 = inside(x2, y2, edge);

        if(in1 && in2)
        {
            newx[k] = x2;
            newy[k] = y2;
            k++;
        }
        else if(in1 && !in2)
        {
            intersect(x1,y1,x2,y2,&newx[k],&newy[k],edge);
            k++;
        }
        else if(!in1 && in2)
        {
            intersect(x1,y1,x2,y2,&newx[k],&newy[k],edge);
            k++;
            newx[k] = x2;
            newy[k] = y2;
            k++;
        }
    }

    for(i = 0; i < k; i++)
    {
        x[i] = newx[i];
        y[i] = newy[i];
    }

    return k;
}

// -------- MAIN --------
void main()
{
    int gd = DETECT, gm;
    int x[MAX], y[MAX];
    int n, i;

    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    // Draw clipping window
    rectangle(xmin, ymin, xmax, ymax);

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter polygon points:\n");
    for(i = 0; i < n; i++)
    {
        scanf("%d %d", &x[i], &y[i]);
    }

    // Draw original polygon
    drawPolygon(x, y, n, RED);

    // Apply clipping (4 edges)
    n = clip(x, y, n, 0); // left
    n = clip(x, y, n, 1); // right
    n = clip(x, y, n, 2); // bottom
    n = clip(x, y, n, 3); // top

    // Draw clipped polygon
    drawPolygon(x, y, n, GREEN);

    getch();
    closegraph();
}