#include <graphics.h>
#include <conio.h>
#include <stdio.h>

#define MAX 10

// ----------- GLOBAL ARRAYS -----------
int x[MAX], y[MAX];
int n;

// ----------- DRAW POLYGON -----------
void drawPolygon()
{
    int i;
    for(i = 0; i < n - 1; i++)
        line(x[i], y[i], x[i+1], y[i+1]);

    line(x[n-1], y[n-1], x[0], y[0]);
}

// ----------- BOUNDARY FILL -----------
void boundaryFill(int x1, int y1, int fillColor, int boundaryColor)
{
    int current = getpixel(x1, y1);

    if(current != boundaryColor && current != fillColor)
    {
        putpixel(x1, y1, fillColor);

        boundaryFill(x1+1, y1, fillColor, boundaryColor);
        boundaryFill(x1-1, y1, fillColor, boundaryColor);
        boundaryFill(x1, y1+1, fillColor, boundaryColor);
        boundaryFill(x1, y1-1, fillColor, boundaryColor);
    }
}

// ----------- SCAN LINE FILL -----------
void scanlineFill()
{
    int i, j, k;
    int ymin = y[0], ymax = y[0];

    for(i = 1; i < n; i++)
    {
        if(y[i] < ymin) ymin = y[i];
        if(y[i] > ymax) ymax = y[i];
    }

    for(i = ymin; i <= ymax; i++)
    {
        int interx[MAX];
        k = 0;

        for(j = 0; j < n; j++)
        {
            int next = (j + 1) % n;

            if((y[j] < i && y[next] >= i) || (y[next] < i && y[j] >= i))
            {
                interx[k] = x[j] + (i - y[j]) * (x[next] - x[j]) / (y[next] - y[j]);
                k++;
            }
        }

        // sorting
        for(j = 0; j < k - 1; j++)
        {
            int temp;
            if(interx[j] > interx[j+1])
            {
                temp = interx[j];
                interx[j] = interx[j+1];
                interx[j+1] = temp;
            }
        }

        for(j = 0; j < k; j += 2)
        {
            line(interx[j], i, interx[j+1], i);
        }
    }
}

// ----------- EDGE FILL -----------
void edgeFill()
{
    int i, j;
    int ymin = y[0], ymax = y[0];

    for(i = 1; i < n; i++)
    {
        if(y[i] < ymin) ymin = y[i];
        if(y[i] > ymax) ymax = y[i];
    }

    for(i = ymin; i <= ymax; i++)
    {
        int inside = 0;

        for(j = 0; j < n; j++)
        {
            int next = (j + 1) % n;

            if((y[j] <= i && y[next] > i) || (y[next] <= i && y[j] > i))
            {
                int xint = x[j] + (i - y[j]) * (x[next] - x[j]) / (y[next] - y[j]);

                if(inside == 0)
                {
                    moveto(xint, i);
                    inside = 1;
                }
                else
                {
                    lineto(xint, i);
                    inside = 0;
                }
            }
        }
    }
}

// ----------- MAIN -----------
void main()
{
    int gd = DETECT, gm;
    int i, choice, seedx, seedy;

    printf("Enter number of vertices (max 10): ");
    scanf("%d", &n);

    printf("Enter coordinates:\n");
    for(i = 0; i < n; i++)
    {
        printf("x%d y%d: ", i+1, i+1);
        scanf("%d %d", &x[i], &y[i]);
    }

    printf("\nChoose Algorithm:\n");
    printf("1. Boundary Fill\n");
    printf("2. Scan Line Fill\n");
    printf("3. Edge Fill\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    drawPolygon();

    switch(choice)
    {
        case 1:
            printf("Enter seed point inside polygon: ");
            scanf("%d %d", &seedx, &seedy);
            boundaryFill(seedx, seedy, GREEN, WHITE);
            break;

        case 2:
            scanlineFill();
            break;

        case 3:
            edgeFill();
            break;

        default:
            printf("Invalid choice!");
    }

    getch();
    closegraph();
}