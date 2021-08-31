#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>  //getch(), kbhit()

// 作業空間：高20；寬80
#define High 20     //高
#define Width 80    //寬

char WorkSpace[High][Width+1];
char WorkSpaceEnd=0;

//亂數
int rm(int min, int max)
{
    return min+rand()%(max-min+1);
}

//清除作業空間
void ClearArray()
{
    for (int H=0 ; H<High; H++)
    {
        for (int W=0 ; W<Width; W++)
        {
            WorkSpace[H][W] = ' ';  // 清除作業空間=' '
        }
        WorkSpace[H][Width] = '\n';
    }
}
// 填作業空間
void FillPage()
{
    //  1. 填入80個字元的上邊線
    for (int W=0 ; W<71; W++)
        WorkSpace[0][W] = '=';
    //  2. 填入每列的字元
    for (int H=0 ; H<High-2; H++) // High-上下邊線
    {
        WorkSpace[H+1][0] = '|';  // 左邊線
        for (int W=0 ; W<Width-2; W++)
            WorkSpace[H+1][W+1] = ' ';  // 中間字元
        WorkSpace[H+1][Width-1] = '|';  // 右邊線
    }
    //  3. 劃出20個字元的下邊線
    for (int W=0 ; W<Width; W++)
        WorkSpace[High-1][W] = '=';
}

// 畫出作業空間
void PrintPage()
{
    printf("%s", WorkSpace);
}

struct AXIS{
    int X;
    int Y;
    };

#define SnakeAxisLength High*Width
struct AXIS SnakeAxis[SnakeAxisLength];    //10個蛇身位址空間

void ClearSnake() // 清除蛇身位址
{
    for (int i=0 ; i<SnakeAxisLength; i++)
    {
        SnakeAxis[i].X= 0;
        SnakeAxis[i].Y= 0;
    }
}
void SnakeHead() // 設定蛇頭位址
{
    SnakeAxis[0].X=(39);
    SnakeAxis[0].Y=(18);
}

int j=0;
void Score()  //計分板
{
    printf("分數:%4d",j);
}

int main()
{
    int dirHigh, dirLow=72;

    srand(time(NULL));

    ClearArray(); // 1. 清除作業空間

    FillPage(); // 2. 填作業空間

    ClearSnake(); //清除蛇身位址

    SnakeHead(); //設定蛇頭位址

    //第一個食物位址
    int foodY=rm(1,18);
    int foodX=rm(1,78);
    WorkSpace[foodY][foodX]='*';

    while (1)
    {
        if(SnakeAxis[0].Y == 0 || SnakeAxis[0].Y == 19  || SnakeAxis[0].X == 0 || SnakeAxis[0].X == 80 ) //撞到牆壁會結束
        {
            sleep(1);
            printf("你的分數為:%d\n請輸入任意鍵，按下Enter結束遊戲",j);
            int p,u=64-j;
            scanf("%d",&p);
            system("cls");
            printf("阿喨最低紀錄為64分 相差了%d分 \n",u);

            if(j>=0 && j<=10)
            {
                printf("實力分析:待加強\n");
            }

            if(j>10 && j<=20)
            {
                printf("實力分析:有點東西囉\n");
            }

            if(j>20 && j<=30)
            {
                printf("實力分析:有實力!\n");
            }

            if(j>30)
            {
                printf("實力分析:實力認可，再接再厲\n");
            }
                printf("GameOver");
                break;
        }

        Score(); //計分板

        if (SnakeAxis[0].Y == foodY && SnakeAxis[0].X == foodX)  //蛇吃到食物分數會+1
        {
            j++;
        }

        if (SnakeAxis[0].Y == foodY && SnakeAxis[0].X == foodX) //蛇碰到食物，食物會重新跑出
        {

            WorkSpace[foodY][foodX]=' ';
            srand(time(NULL));
            foodY=rm(1,18);
            foodX=rm(1,78);
            WorkSpace[foodY][foodX]='*';
        }

        // 把整隻蛇身的位址放入作業空間填為+
        for (int i=0 ; i<SnakeAxisLength; i++)
        {
            if(SnakeAxis[i].Y != 0 && SnakeAxis[i].X != 0)
                WorkSpace[SnakeAxis[i].Y][SnakeAxis[i].X]= '+';
        }

        PrintPage(); // 畫出作業空間

        for (int i=0 ; i<SnakeAxisLength; i++)
        {
            if(SnakeAxis[i].Y != 0 && SnakeAxis[i].X != 0)
                WorkSpace[SnakeAxis[i].Y][SnakeAxis[i].X]= ' ';
        }

        if(j>=0 && j<=5)
        {
            usleep(70000);
        }

        if(j>5 && j<=10)
        {
            usleep(40000);
        }

        if(j>10 && j<=15)
        {
            usleep(20000);
        }

        if(j>15 && j<=20)
        {
            usleep(10000);
        }

        if(j>20 && j<=25)
        {
            usleep(8000);
        }

        if(j>25)
        {
            usleep(5000);
        }

        while(kbhit())
        {
            dirHigh = getch();
            if(dirHigh==224)
                dirLow = getch();
        }
        if (dirHigh == 0x1b) break;

        if(dirLow==72) //up
        {
            // 蛇往上跑
            for(int i=SnakeAxisLength-1 ; i>0; i--)
            {
                if(SnakeAxis[i].Y != 0 && SnakeAxis[i].X != 0)
                SnakeAxis[i].Y = SnakeAxis[i-1].Y;
                SnakeAxis[i].X = SnakeAxis[i-1].X;
            }
            SnakeAxis[0].Y = SnakeAxis[0].Y-1;
        }
        else if(dirLow==80) //down
        {
            // 蛇往下跑
            for(int i=SnakeAxisLength-1 ; i>0; i--)
            {
                if(SnakeAxis[i].Y != 0 && SnakeAxis[i].X != 0)
                SnakeAxis[i].Y = SnakeAxis[i-1].Y;
                SnakeAxis[i].X = SnakeAxis[i-1].X;
            }
            SnakeAxis[0].Y = SnakeAxis[0].Y+1;
        }
        else if(dirLow==75) //left
        {
            // 蛇往左跑
            for(int i=SnakeAxisLength-1 ; i>0; i--)
            {
                if(SnakeAxis[i].Y != 0 && SnakeAxis[i].X != 0)
                SnakeAxis[i].Y = SnakeAxis[i-1].Y;
                SnakeAxis[i].X = SnakeAxis[i-1].X;
            }
            SnakeAxis[0].X = SnakeAxis[0].X-1;

        }
        else if(dirLow==77)//right
        {
            // 蛇往右跑
            for(int i=SnakeAxisLength-1 ; i>0; i--)
            {
                if(SnakeAxis[i].Y != 0 && SnakeAxis[i].X != 0)
                SnakeAxis[i].Y = SnakeAxis[i-1].Y;
                SnakeAxis[i].X = SnakeAxis[i-1].X;
            }
            SnakeAxis[0].X = SnakeAxis[0].X+1;
        }

       if(SnakeAxis[0].Y == foodY && SnakeAxis[0].X == foodX) //蛇吃到東西變長
        {
            for(int i=SnakeAxisLength-1 ; i>0; i--)
            {
                SnakeAxis[i].Y = SnakeAxis[i-1].Y;
                SnakeAxis[i].X = SnakeAxis[i-1].X;
            }
            SnakeAxis[0].Y = foodY;
            SnakeAxis[0].X = foodX;
        }
        system ("cls");
    }
    return 0;

}
