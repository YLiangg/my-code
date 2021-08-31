#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>  //getch(), kbhit()

// �@�~�Ŷ��G��20�F�e80
#define High 20     //��
#define Width 80    //�e

char WorkSpace[High][Width+1];
char WorkSpaceEnd=0;

//�ü�
int rm(int min, int max)
{
    return min+rand()%(max-min+1);
}

//�M���@�~�Ŷ�
void ClearArray()
{
    for (int H=0 ; H<High; H++)
    {
        for (int W=0 ; W<Width; W++)
        {
            WorkSpace[H][W] = ' ';  // �M���@�~�Ŷ�=' '
        }
        WorkSpace[H][Width] = '\n';
    }
}
// ��@�~�Ŷ�
void FillPage()
{
    //  1. ��J80�Ӧr�����W��u
    for (int W=0 ; W<71; W++)
        WorkSpace[0][W] = '=';
    //  2. ��J�C�C���r��
    for (int H=0 ; H<High-2; H++) // High-�W�U��u
    {
        WorkSpace[H+1][0] = '|';  // ����u
        for (int W=0 ; W<Width-2; W++)
            WorkSpace[H+1][W+1] = ' ';  // �����r��
        WorkSpace[H+1][Width-1] = '|';  // �k��u
    }
    //  3. ���X20�Ӧr�����U��u
    for (int W=0 ; W<Width; W++)
        WorkSpace[High-1][W] = '=';
}

// �e�X�@�~�Ŷ�
void PrintPage()
{
    printf("%s", WorkSpace);
}

struct AXIS{
    int X;
    int Y;
    };

#define SnakeAxisLength High*Width
struct AXIS SnakeAxis[SnakeAxisLength];    //10�ӳD����}�Ŷ�

void ClearSnake() // �M���D����}
{
    for (int i=0 ; i<SnakeAxisLength; i++)
    {
        SnakeAxis[i].X= 0;
        SnakeAxis[i].Y= 0;
    }
}
void SnakeHead() // �]�w�D�Y��}
{
    SnakeAxis[0].X=(39);
    SnakeAxis[0].Y=(18);
}

int j=0;
void Score()  //�p���O
{
    printf("����:%4d",j);
}

int main()
{
    int dirHigh, dirLow=72;

    srand(time(NULL));

    ClearArray(); // 1. �M���@�~�Ŷ�

    FillPage(); // 2. ��@�~�Ŷ�

    ClearSnake(); //�M���D����}

    SnakeHead(); //�]�w�D�Y��}

    //�Ĥ@�ӭ�����}
    int foodY=rm(1,18);
    int foodX=rm(1,78);
    WorkSpace[foodY][foodX]='*';

    while (1)
    {
        if(SnakeAxis[0].Y == 0 || SnakeAxis[0].Y == 19  || SnakeAxis[0].X == 0 || SnakeAxis[0].X == 80 ) //��������|����
        {
            sleep(1);
            printf("�A�����Ƭ�:%d\n�п�J���N��A���UEnter�����C��",j);
            int p,u=64-j;
            scanf("%d",&p);
            system("cls");
            printf("���g�̧C������64�� �ۮt�F%d�� \n",u);

            if(j>=0 && j<=10)
            {
                printf("��O���R:�ݥ[�j\n");
            }

            if(j>10 && j<=20)
            {
                printf("��O���R:���I�F���o\n");
            }

            if(j>20 && j<=30)
            {
                printf("��O���R:����O!\n");
            }

            if(j>30)
            {
                printf("��O���R:��O�{�i�A�A���A�F\n");
            }
                printf("GameOver");
                break;
        }

        Score(); //�p���O

        if (SnakeAxis[0].Y == foodY && SnakeAxis[0].X == foodX)  //�D�Y�쭹�����Ʒ|+1
        {
            j++;
        }

        if (SnakeAxis[0].Y == foodY && SnakeAxis[0].X == foodX) //�D�I�쭹���A�����|���s�]�X
        {

            WorkSpace[foodY][foodX]=' ';
            srand(time(NULL));
            foodY=rm(1,18);
            foodX=rm(1,78);
            WorkSpace[foodY][foodX]='*';
        }

        // ��㰦�D������}��J�@�~�Ŷ���+
        for (int i=0 ; i<SnakeAxisLength; i++)
        {
            if(SnakeAxis[i].Y != 0 && SnakeAxis[i].X != 0)
                WorkSpace[SnakeAxis[i].Y][SnakeAxis[i].X]= '+';
        }

        PrintPage(); // �e�X�@�~�Ŷ�

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
            // �D���W�]
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
            // �D���U�]
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
            // �D�����]
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
            // �D���k�]
            for(int i=SnakeAxisLength-1 ; i>0; i--)
            {
                if(SnakeAxis[i].Y != 0 && SnakeAxis[i].X != 0)
                SnakeAxis[i].Y = SnakeAxis[i-1].Y;
                SnakeAxis[i].X = SnakeAxis[i-1].X;
            }
            SnakeAxis[0].X = SnakeAxis[0].X+1;
        }

       if(SnakeAxis[0].Y == foodY && SnakeAxis[0].X == foodX) //�D�Y��F���ܪ�
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
