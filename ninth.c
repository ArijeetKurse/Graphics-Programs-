#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main()
{
    int gd = DETECT, gm;

    int ballX = 50, ballY = 200;
    int dx = 3;

    int shooterY = 200;
    int score = 0;

    int key = 0;

    char s[10];   // ✅ DECLARED HERE

    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    srand(1);

    while(1)
    {
        cleardevice();

        setcolor(WHITE);
        circle(ballX, ballY, 10);

        setfillstyle(SOLID_FILL, RED);
        floodfill(ballX, ballY, WHITE);

        ballX += dx;

        if(ballX > getmaxx()-10 || ballX < 10)
        {
            dx = -dx;
            ballY = rand() % (getmaxy()-20) + 10;
        }

        line(20, shooterY-20, 20, shooterY+20);

        // ✅ NO DECLARATION HERE
        itoa(score, s, 10);
        outtextxy(10,10,"Score:");
        outtextxy(70,10,s);

        // Check key press
        if(kbhit())
        {
            key = getch();

            // Move shooter
            if(key == 'w') shooterY -= 10;
            if(key == 's') shooterY += 10;

            // Shoot (space)
            if(key == 32)
            {
                // hit detection
                if(abs(ballY - shooterY) < 20 && ballX < 100)
                {
                    score++;
                    ballX = 50;
                    ballY = rand() % getmaxy();
                }
            }
        }

        delay(30);
    }

    closegraph();
    return 0;
}