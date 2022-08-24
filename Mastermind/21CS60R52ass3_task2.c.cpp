#include <cstdio>
#include <iostream>
#include <vector>

 
using namespace std;
#include "togasat.hpp"

vector<vector<int> > vec;

void findSAT(int lp[100]){
    togasat::Solver solver;
    
    for(int i=0; i< vec.size(); i++){
        solver.addClause(vec[i]);
    }
    solver.solve();
    solver.printAnswer(lp);
    
}

/*****numerics to Alphabhet conversion******/

char p(int n)
{
    switch(n)
        {
            case 1: return 'A';
            case 2: return 'B';
            case 3: return 'C';
            case 4: return 'D';
            case 5: return 'E';
            case 6: return 'F';
            case 7: return 'G';
            case 8: return 'H';
        }
}

/******codechecker code to colour code*******/

void find(int pr[100],char cc[])
{
    int x,y;
    for(int i=0;i<4;i++)
    {
        x=(pr[i]/4)+1;
        y=pr[i]%4;
        //printf("%d ",x);
        if(y!=0)
        {
            cc[y]=p(x);
        }
        else
        {
            cc[4]=p(x-1);
        }
        
    }
}

/****** Black and White generator *******/

void codechecker(char cm[],char cc[],int pq[2])
{
    int b=0,w=0,che[100]={0};
    int chel[100]={0};
    int chi[100]={0};
    for(int i=1;i<5;i++)
    {
        if(cm[i]==cc[i])
        {
            b++;
            che[i]=1;
            chi[i]=1;
        }
        if(che[i]!=1)
        {
            for( int j=1;j<5;j++)
            {
                if(cm[i]==cc[j] && chel[i]==0 && chi[j]==0)
                {
                    w++;
                    chel[i]=1;
                    chi[j]=1;
                }
            }
        }
    }
    /*if(b==4 || b==3)
    {
        w=0;
    }*/
    pq[0]=b;
    pq[1]=w;
}

/******powers of 2 calculator*******/

int pow2(int n)
{
    if(n==1||n==2||n==4||n==8||n==16||n==32||n==64||n==128) return 1;
    else return 0;
}
int pow3(int n)
{
    if(n==3||n==5||n==6||n==9||n==10||n==12) return 1;
    else return 0;
}
int pow4(int n)
{
    if(n==7||n==11||n==13||n==14) return 1;
    else return 0;
}


/***********clauses generator **************/

int clausegenerator(int arr[100],int b,int w)
{
    int abc[100];
    std::vector<int> clause;
    if(w>=0 && b==0)
    {
        for(int i=0;i<4;i++)
        {
            clause.push_back(-arr[i]);
            vec.push_back(clause);
            clause.clear();
        }
    }
    
    if(w>=0 && b==1)
    {
        for(int i=0;i<16;i++)
        {
            if(!pow2(i))
            {
                int k=i;
                for(int j=0;j<4;j++)
                {
                    abc[(arr[j])]=k%2;
                    k=k/2;
                }
                for(int j=0;j<4;j++)
                {
                    if(abc[(arr[j])]==0) clause.push_back(arr[j]);
                    else clause.push_back(-arr[j]);
                }
                vec.push_back(clause);
                clause.clear();
            }
        }
    }
    if(w>=0 && b==2)
    {
        for(int i=0;i<16;i++)
        {
            if(!pow3(i))
            {
                int k=i;
                for(int j=0;j<4;j++)
                {
                    abc[(arr[j])]=k%2;
                    k=k/2;
                }
                for(int j=0;j<4;j++)
                {
                    if(abc[(arr[j])]==0) clause.push_back(arr[j]);
                    else clause.push_back(-arr[j]);
                }
                vec.push_back(clause);
                clause.clear();
            }
        }
    }
    
    if(w>=0 && b==3)
    {
        for(int i=0;i<16;i++)
        {
            if(!pow4(i))
            {
                int k=i;
                for(int j=0;j<4;j++)
                {
                    abc[(arr[j])]=k%2;
                    k=k/2;
                }
                for(int j=0;j<4;j++)
                {
                    if(abc[(arr[j])]==0) clause.push_back(arr[j]);
                    else clause.push_back(-arr[j]);
                }
                vec.push_back(clause);
                clause.clear();
            }
        }
    }
}



/************** main starts here *********************/


int main(void)
{    
    std::vector<int> clause;
    int k,a[100];
    int l=0;
    int lp[100];
    
    int i=0;
    int c,ab[400],pr[100];
    char cm[400];
    int pq[2]={0};
    srand(time(0));
    printf("CODE MAKER code is: ");
    while(i<4)
    {
        c=(rand()%8)+1;
        ab[++i]=c;
    }
    for(i=1;i<5;i++)
    {
        cm[i]=p(ab[i]);
        printf("%c",cm[i]);
    }
    printf("\n");
    
    /**************codebreaker*************/
    char cc[100];
    for(int p=0;p<4;p++)
    {
        int ga=p+29;
        int gg=p+1;
        for(int i=0;i<256;i++)
        {
            if(!pow2(i))
            {
                k=i;
                for(int j=ga;j>=1;j=j-4)
                {
                    a[j]=k%2;
                    k=k/2;
                }
                for(int j=gg;j<=32;j=j+4)
                {
                    if(a[j]==0) clause.push_back(j);
                    else clause.push_back(-j);
                }
                vec.push_back(clause);
                clause.clear();
            }
        }
    }
    int mpr=0;
    while(pq[0]<4)
    {
        mpr++;
        findSAT(lp);
        int kin=0;
        for(int i=0;i<32;i++)
        {
            if(lp[i]>0) pr[kin++]=lp[i];
        }
        find(pr,cc);
        printf("Guess %d is : ",mpr);
        for(int i=1;i<5;i++)
        printf("%c",cc[i]);
        codechecker(cm,cc,pq);
        printf(" => black: %d,white: %d ",pq[0],pq[1]);
        clausegenerator(pr,pq[0],pq[1]);
        //findSAT(lp);
        printf("\n");
    }
}