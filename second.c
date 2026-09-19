#include <stdio.h>
#include <graphics.h>
#include <conio.h>

// Plot 8 symmetric points
void plotCirclePoints(int xc, int yc, int x, int y, int color) {
    putpixel(xc + x, yc + y, color);
    putpixel(xc - x, yc + y, color);
    putpixel(xc + x, yc - y, color);
    putpixel(xc - x, yc - y, color);
    putpixel(xc + y, yc + x, color);
    putpixel(xc - y, yc + x, color);
    putpixel(xc + y, yc - x, color);
    putpixel(xc - y, yc - x, color);
}

// Midpoint Circle
void drawCircleMidpoint(int xc, int yc, int r) {
    int x = 0, y = r;
    int p = 1 - r;

    while (x <= y) {
        plotCirclePoints(xc, yc, x, y, WHITE);
        x++;

        if (p < 0) {
            p = p + 2 * x + 1;
        } else {
            y--;
            p = p + 2 * x - 2 * y + 1;
        }
    }
}

// Bresenham Circle
void drawCircleBresenham(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;

    while (x <= y) {
        plotCirclePoints(xc, yc, x, y, YELLOW);
        x++;

        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            y--;
            d = d + 4 * (x - y) + 10;
        }
    }
}

void main() {
    int gd = DETECT, gm;
    int xc, yc, r, choice;

    // INPUT FIRST (text mode)
    printf("Enter center (xc yc): ");
    scanf("%d %d", &xc, &yc);

    printf("Enter radius: ");
    scanf("%d", &r);

    printf("\n1. Midpoint Circle\n2. Bresenham Circle\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    // INIT GRAPHICS AFTER INPUT
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    if (graphresult() != grOk) {
        printf("Graphics error!");
        getch();
        return;
    }

    cleardevice();

    switch (choice) {
        case 1:
            drawCircleMidpoint(xc, yc, r);
            outtextxy(10, 10, "Midpoint Circle");
            break;

        case 2:
            drawCircleBresenham(xc, yc, r);
            outtextxy(10, 10, "Bresenham Circle");
            break;

        default:
            outtextxy(10, 10, "Invalid choice!");
    }

    getch();  // HOLD SCREEN
    closegraph();
}