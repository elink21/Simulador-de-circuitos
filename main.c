#include <stdio.h>
#include<math.h>
#include <stdlib.h>
#include <string.h>
struct atrib{
    int ni;
    int nf;
};

struct resistor{
    float ohms;
    //float current;
    float watt;
    struct atrib pos;
}resistors[20];

struct voltageSource{
    float voltage;
    float current;
    struct atrib pos;
}voltageSources[5];


/*void printResistors(struct resistor resistors[20])
{
    printf("I\t N1 \t N2 \t Value \tPow \n\n");
    for(int i=0;i<20;i++)
    {
        struct resistor r=resistors[i];
        printf("%d\t %d\t %d\t %.2f\t %.2f \n",i,r.pos.ni,r.pos.nf, r.ohms,r.watt);
    }
}*/
int main()
{
    int i=0,j=0,k=0,p1,p2;
    int shareConnection=0;
    float rt=0,vt=0,ct=0;
    float mul;
    char address[100]="C:/gnuplot/bin/gnuplot.exe -p -e \"plot ";
    char voltage[10];
    char realEnd[20];
    char filter[3]="Nul";
    while(strcmp(filter,"mul")!=0)
    {
        scanf("%s",&filter);
        if(strcmp(filter,"res")==0)
        {
            scanf("%d%d%f%f",&resistors[i].pos.ni,&resistors[i].pos.nf,&resistors[i].ohms,&resistors[i].watt);
            i++;
        }
        else if(strcmp(filter,"vol")==0)
        {
            scanf("%d%d%f%f",&voltageSources[j].pos.ni,&voltageSources[j].pos.nf,&voltageSources[j].voltage,&
                  voltageSources[j].current);
            j++;
        }
    }
    scanf("%d%d",&p1,&p2);
    for(int x=0;x<i;x++)
    {
        shareConnection=0;
        for(int y=x+1;y<i;y++)
        {
            if(resistors[x].pos.ni== resistors[y].pos.ni && resistors[x].pos.nf==resistors[y].pos.nf && resistors[x].pos.ni!=-1
               &&resistors[y].pos.ni!=-1)
               {
                   shareConnection=1;
               }
        }
        if(shareConnection) resistors[x].ohms=1/resistors[x].ohms;
        for(int y=x+1;y<i;y++)
        {
            if(resistors[x].pos.ni== resistors[y].pos.ni && resistors[x].pos.nf==resistors[y].pos.nf && resistors[x].pos.ni!=-1
               &&resistors[y].pos.ni!=-1)
            {
                resistors[y].pos.ni=-1;
                resistors[y].pos.nf=-1;
                resistors[x].ohms+=1.0/resistors[y].ohms;
                resistors[y].ohms=0;

            }
        }
        if(shareConnection)
        {
            resistors[x].ohms=1.0/resistors[x].ohms;

        }
    }
    for(int x=0;x<i;x++)
    {
        rt+=resistors[x].ohms;
    }
    for(int x=0;x<j;x++)
    {
        vt+=voltageSources[x].voltage;
    }
    ct=vt/rt;
    //printResistors(resistors);a
    printf("%0.2f ohms --%0.2f V --%0.8f A",rt,vt,ct);
    for(int x=0;x<i;x++)
    {
        if(p1==resistors[x].pos.ni&&p2==resistors[x].pos.nf)
        {
            mul=ct*resistors[x].ohms;
            printf("\nMedicion= %0.1f V\n",ct*resistors[x].ohms);
        }
    }
    for(int x=0;x<j;x++)
    {
        if(ct>voltageSources[x].current)
        {
            printf("\nLa fuente %d no satisface el circuito en intensidad",x);
        }
    }
    for(int x=0;x<i;x++)
    {

        if(   (ct*ct)*resistors[x].ohms>resistors[x].watt )
        {
            printf("\nLa resistencia %d se quemara",x);
        }
    }

    sprintf(voltage,"%f",mul);
    sprintf(realEnd,",%f\" ",vt);
    strcat(address,voltage);
    strcat(address,realEnd);
    printf("\n");
    puts(address);
    system(address);

    return 0;
}
