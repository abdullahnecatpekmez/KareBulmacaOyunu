#include <stdio.h>
#include <stdlib.h>
#define SATIR 10
#define SUTUN 20
struct veri
{
    int dogru;
    int sayac;
};

void atama(char [][SUTUN],int,int);
void yazdirma(char [][SUTUN],int [][SUTUN],int,int);
void kontrol(int,int,int);
void oyunlar(char[][SUTUN],int [][SUTUN],int ,int ,int ,int,int, struct veri*);


int main()
{

    int satir,sutun,isaretleme,birSay=0;
    int sat,sut,i=0,j=0;
    int matris[SATIR][SUTUN]= {{0}};
    char karala[SATIR][SUTUN];
    struct veri sayi;
    sayi.dogru=0;
    sayi.sayac=0;

    FILE *fptr;
    fptr=fopen("resim.txt.txt","r");
    if(fptr==NULL)
        printf("dosya acilamadi\n");
    else
        fscanf(fptr,"%d%d",&sat,&sut);

    for(i=0; i<sat; i++)
    {
        for(j=0; j<sut; j++)
        {
            fscanf(fptr,"%d",&matris[i][j]);
            if(matris[i][j]==1)
                birSay++;
            printf("%d",matris[i][j]);
        }
        printf("\n");
    }
    fclose(fptr);


    printf("\nbirlerin sayisi:%d\n",birSay);
    atama(karala,sat,sut);
    yazdirma(karala,matris,sat,sut);
    do
    {
        printf("\nsatir numarasini giriniz (1-%d):",sat);
        scanf("%d",&satir);
        kontrol(1,sat,satir);
        printf("\nsutun numarasini giriniz (1-%d):",sut);
        scanf("%d",&sutun);
        kontrol(1,sut,sutun);

        printf("\nisaretleme kodunu giriniz (1:dolu, 0:bos, 2:belirsiz):");
        scanf("%d",&isaretleme);
        kontrol(0,2,isaretleme);
        oyunlar(karala,matris,sat,sut,isaretleme,satir,sutun,&sayi);
        yazdirma(karala,matris,sat,sut);
        printf("sayac%d\n",sayi.sayac);
        printf("dogru sayisi%d\n",sayi.dogru);
        if(birSay==sayi.dogru&&sayi.sayac==0)
            printf("\nBuraya kadar...");


    }
    while(sayi.dogru<birSay || sayi.sayac!=0);

    return 0;
}

void oyunlar(char oyunalani[][SUTUN],int matris[][SUTUN],int sat,int sut,int isaretleme,int satir,int sutun,struct veri *say)
{
    char c=219;
    switch(isaretleme)
    {
    case 0:
        if(oyunalani[satir-1][sutun-1]==c)
        {
            (*say).sayac--;
             oyunalani[satir-1][sutun-1]='X';
            yazdirma( oyunalani,matris,sat, sut);
            break;

        }
        oyunalani[satir-1][sutun-1]='X';
        yazdirma( oyunalani,matris,sat, sut);





        break;
    case 1:
        if (matris[satir-1][sutun-1]==1)
        {

            if(oyunalani[satir-1][sutun-1]!=c)//burasi calismiyor 219 simgesi gerekiyor
            {
                oyunalani[satir-1][sutun-1]=219;
                (*say).dogru++;
                yazdirma( oyunalani,matris,sat, sut);
            }
        }
        else
        {
            oyunalani[satir-1][sutun-1]=219;
            (*say).sayac++;
            yazdirma( oyunalani,matris,sat, sut);

        }
        break;

    case 2:


        if(oyunalani[satir-1][sutun-1]==c)
        {
            (*say).sayac--;
            oyunalani[satir-1][sutun-1]='O';
           yazdirma( oyunalani,matris,sat, sut);
        }
        oyunalani[satir-1][sutun-1]='O';
        yazdirma( oyunalani,matris,sat, sut);


        break;


    }

}


void atama(char dizi[][SUTUN],int sat,int sut)//oyun alanina en basta O harfinin atanmasini saglar..
{
    int i,j;
    for (i=0; i<sat; i++)
        for (j=0; j<sut; j++)
            dizi[i][j]='O';

}
void yazdirma(char karala[][SUTUN],int matris[][SUTUN],int sat,int sut)//ekranda oyun alaninin goruntulenmesini saglayan fonksiyon..
{
    int j,i,yatay[sat][sut],dusey[sat][sut],x=0,y,k,a,b=0;
    int sayac=0;

    printf("  ");
    for (i=0; i<sut; i++)
        printf("%d",i+1);
    for (i=0; i<sat; i++)
        for(j=0; j<sut; j++)
        {
            yatay[i][j]=0;
            dusey[i][j]=0;
        }

    printf("\n");
    for (i=0; i<sat; i++)
    {
        printf("%2d",i+1);
        y=0;
        for (j=0; j<sut; j++)
        {
            printf("%c",karala[i][j]);
            if(matris[i][j]==1)
                yatay[x][y]++;

            if(matris[i][j+1]==0)
                y++;
        }
        x++;

        for(k=0; k<y; k++)
        {
            if(yatay[i][k]!=0)
                printf(" %d ",yatay[i][k]);

        }
        printf("\n");
    }
    a=0;
    for(i=0; i<sut; i++)
    {
        b=0;
        for(j=0; j<sat; j++)
        {
            if(matris[j][i]==1)
            {
                dusey[b][a]++;
                if(matris[j+1][i]==0)
                    b++;
            }
        }
        a++;

    }

    printf("\n");
    for(i=0; i<sat; i++)
    {
        sayac=0;
        printf("  ");
        for(k=0; k<sut; k++)
        {
            if(dusey[i][k]!=0)
            {
                printf("%d",dusey[i][k]);
                sayac=1;
            }
            if(sayac==0)
                printf(" ");

        }
        if(sayac==0)
            break;
        printf("\n\n");
    }
    printf("\n");


}

void kontrol(int alt,int ust,int kenar)
{
    while (kenar<alt || kenar>ust)//kullanicinin girdigi kenar sayisini kontrol eden while dongusu...
    {
        printf("hatali veri girisi yaptin!!\nLutfen %d ile %d arasinda bir  sayi olacak sekilde gir:",alt,ust);
        scanf("%d",&kenar);
    }

}
