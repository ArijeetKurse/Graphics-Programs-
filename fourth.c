#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

// Draw axes
void drawAxes() {
    int midx = getmaxx() / 2;
    int midy = getmaxy() / 2;

    line(midx, 0, midx, getmaxy());
    line(0, midy, getmaxx(), midy);
}

// Convert Cartesian → Screen
void convertToScreen(int *x, int *y) {
    int midx = getmaxx() / 2;
    int midy = getmaxy() / 2;

    *x = midx + (*x);
    *y = midy - (*y);
}

// Draw triangle
void drawTriangle(int x[], int y[], int color) {
    int i;
    int sx[3], sy[3];

    setcolor(color);

    for(i = 0; i < 3; i++) {
        sx[i] = x[i];
        sy[i] = y[i];
        convertToScreen(&sx[i], &sy[i]);
    }

    line(sx[0], sy[0], sx[1], sy[1]);
    line(sx[1], sy[1], sx[2], sy[2]);
    line(sx[2], sy[2], sx[0], sy[0]);
}

// Translation
void translate(int x[], int y[], int tx, int ty, int xt[], int yt[]) {
    int i;
    for(i = 0; i < 3; i++) {
        xt[i] = x[i] + tx;
        yt[i] = y[i] + ty;
    }
}

// Scaling
void scale(int x[], int y[], float sx, float sy, int xs[], int ys[]) {
    int i;
    for(i = 0; i < 3; i++) {
        xs[i] = (int)(x[i] * sx + 0.5);
        ys[i] = (int)(y[i] * sy + 0.5);
    }
}

// Rotation
void rotate(int x[], int y[], float angle, int xr[], int yr[]) {
    int i;
    float rad = angle * 3.14159 / 180.0;

    for(i = 0; i < 3; i++) {
        xr[i] = (int)(x[i]*cos(rad) - y[i]*sin(rad) + 0.5);
        yr[i] = (int)(x[i]*sin(rad) + y[i]*cos(rad) + 0.5);
    }
}

// Reflection
void reflectX(int x[], int y[], int xf[], int yf[]) {
    int i;
    for(i = 0; i < 3; i++) {
        xf[i] = x[i];
        yf[i] = -y[i];
    }
}

// -------- MAIN --------
void main() {
    int gd = DETECT, gm;

    int x[3] = {50, 100, 75};
    int y[3] = {50, 50, 100};

    int xt[3], yt[3];
    int xs[3], ys[3];
    int xr[3], yr[3];
    int xf[3], yf[3];

    int choice;
    char ch;

    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    do {
        cleardevice();
        drawAxes();

        // Show original always
        drawTriangle(x, y, WHITE);
        outtextxy(10,10,"Original");

        printf("\nMENU:\n");
        printf("1. Translation\n");
        printf("2. Scaling\n");
        printf("3. Rotation\n");
        printf("4. Reflection (X-axis)\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: {
                int tx, ty;
                printf("Enter tx, ty: ");
                scanf("%d %d", &tx, &ty);

                translate(x, y, tx, ty, xt, yt);
                drawTriangle(xt, yt, GREEN);
                outtextxy(10,30,"Translated");
                break;
            }

            case 2: {
                float sx, sy;
                printf("Enter sx, sy: ");
                scanf("%f %f", &sx, &sy);

                scale(x, y, sx, sy, xs, ys);
                drawTriangle(xs, ys, CYAN);
                outtextxy(10,30,"Scaled");
                break;
            }

            case 3: {
                float angle;
                printf("Enter angle: ");
                scanf("%f", &angle);

                rotate(x, y, angle, xr, yr);
                drawTriangle(xr, yr, YELLOW);
                outtextxy(10,30,"Rotated");
                break;
            }

            case 4: {
                reflectX(x, y, xf, yf);
                drawTriangle(xf, yf, RED);
                outtextxy(10,30,"Reflected");
                break;
            }

            default:
                printf("Invalid choice!\n");
        }

        getch();

        printf("\nDo you want to continue? (y/n): ");
        ch = getche();

    } while(ch == 'y' || ch == 'Y');

    closegraph();
}