#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>

// -------- BEZIER (Midpoint subdivision) --------
void drawBezier(float x1, float y1, float x2, float y2,
                float x3, float y3, float x4, float y4, int iter)
{
    float x12,y12,x23,y23,x34,y34;
    float x123,y123,x234,y234;
    float x1234,y1234;

    if(iter == 0)
    {
        line((int)x1,(int)y1,(int)x4,(int)y4);
        return;
    }

    // Midpoints
    x12 = (x1 + x2)/2;  y12 = (y1 + y2)/2;
    x23 = (x2 + x3)/2;  y23 = (y2 + y3)/2;
    x34 = (x3 + x4)/2;  y34 = (y3 + y4)/2;

    x123 = (x12 + x23)/2;  y123 = (y12 + y23)/2;
    x234 = (x23 + x34)/2;  y234 = (y23 + y34)/2;

    x1234 = (x123 + x234)/2;
    y1234 = (y123 + y234)/2;

    // Recursive calls
    drawBezier(x1,y1,x12,y12,x123,y123,x1234,y1234,iter-1);
    drawBezier(x1234,y1234,x234,y234,x34,y34,x4,y4,iter-1);
}

// -------- KOCH CURVE --------
void koch(int x1, int y1, int x2, int y2, int iter)
{
    int xA, yA, xB, yB, xC, yC;
    float angle = 60 * 3.14159 / 180;

    if(iter == 0)
    {
        line(x1,y1,x2,y2);
        return;
    }

    xA = (2*x1 + x2)/3;
    yA = (2*y1 + y2)/3;

    xB = (x1 + 2*x2)/3;
    yB = (y1 + 2*y2)/3;

    xC = xA + (int)((xB - xA)*cos(angle) - (yB - yA)*sin(angle));
    yC = yA + (int)((xB - xA)*sin(angle) + (yB - yA)*cos(angle));

    koch(x1,y1,xA,yA,iter-1);
    koch(xA,yA,xC,yC,iter-1);
    koch(xC,yC,xB,yB,iter-1);
    koch(xB,yB,x2,y2,iter-1);
}

// -------- FRACTAL LINE --------
void fractalLine(int x1, int y1, int x2, int y2, int iter)
{
    int xm, ym;

    if(iter == 0)
    {
        line(x1,y1,x2,y2);
        return;
    }

    xm = (x1 + x2)/2;
    ym = (y1 + y2)/2;

    // add variation
    ym = ym + (rand()%20 - 10);

    fractalLine(x1,y1,xm,ym,iter-1);
    fractalLine(xm,ym,x2,y2,iter-1);
}

// -------- MAIN --------
void main()
{
    int gd = DETECT, gm;
    int choice, iter;

    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    printf("1. Bezier Curve\n2. Koch Curve\n3. Fractal Line\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            printf("Enter iterations (<=4): ");
            scanf("%d",&iter);

            drawBezier(100,300, 150,100, 300,100, 350,300, iter);
            break;

        case 2:
            printf("Enter iterations (<=3): ");
            scanf("%d",&iter);

            koch(100,200, 400,200, iter);
            break;

        case 3:
            printf("Enter iterations (<=10): ");
            scanf("%d",&iter);

            fractalLine(100,200,400,200,iter);
            break;

        default:
            printf("Invalid choice");
    }

    getch();
    closegraph();
}