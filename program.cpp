#include<iostream>
#include<cstdio>
#include<stdlib.h>
#include<iomanip>
#include<math.h>
#include<limits.h>
#include<string.h>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
#include<map>
#include<bitset>
#include<fstream>
#define mod 1000000007
#define MAX 100000000

using namespace std;
#define scan(a) scanf("%d",&a);
#define print(a) printf("%d\n",a);
#define mem(a,v) memset(a,v,sizeof(a))
#define clr(a) memset(a,0,sizeof(a))
#define pb(x) push_back(x)
#define sort(a) sort(a.begin(),a.end())
#define inf 1e9
#define mp(a,b) make_pair(a,b)
#define V vector
#define S string
#define Gu getchar_unlocked
#define Pu putchar_unlocked
#define Read(n) ch=Gu(); while (ch<'0') ch=Gu(); n=ch-'0'; ch=Gu(); while (!(ch<'0')) {n=10*n+ch-'0'; ch=Gu();}
#define Write(n) r=n; chptr=s; *chptr=r%10+'0'; r/=10; for (; r; r/=10) {++chptr; *chptr=r%10+'0'; } Pu(*chptr); for (; chptr!=s; ) Pu(*--chptr);
typedef long long LL;
typedef long double LD;
typedef long L;
typedef pair<int,int> pii;
const double pi=acos(-1.0);

double likelihood[10][28][28],prior[10],checkprob[28][28],posterior[10],numprob[10],ansprob[10][10],eachnumprob[10];
int cntnum[10],maxele,correctresult=0,testcnt[10];
void resetlike()
{
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<28;j++)
		{
			for(int k=0;k<28;k++)
				likelihood[i][j][k]=1;
		}
	}
}
int main()
{
   	/*int ch;
   	int r;
   	char s[12];
   	char *chptr;*/
   	
/////////////////// LOAD DATA ///////////////////
   	
   	ifstream tri("trainingimages");
   	ifstream trl("traininglabels");
   	ifstream tei("testimages");
   	ifstream tel("testlabels");
   	string s,st;
   	
///////////////////// TRANING EXAMPLES STARTS ///////////////////////
   	clr(ansprob);
   	resetlike();
   	clr(cntnum);	
	for(int i=0;i<5000;i++)			
	{
		getline(trl,s);
		int n=s[0]-'0';
		for(int j=0;j<28;j++)
		{
			getline(tri,st);
			for(int k=0;k<28;k++)
			{
				if(st[k]=='+' || st[k]=='#')
					likelihood[n][j][k]+=1;					
			}
		}
		cntnum[n]++;
	}
	
	for(int i=0;i<10;i++)		//LIKELIHOOD PROBABILTY
	{
		for(int j=0;j<28;j++)
		{
			for(int k=0;k<28;k++)
				likelihood[i][j][k]=(likelihood[i][j][k]/cntnum[i]);
		}
	}
	
	for(int i=0;i<10;i++)   // PRIOR PROBABILTY
 	{
		prior[i]=cntnum[i]/5000.0;
	}
	
////////////////////// TRANING EXAMPLES ENDS ///////////////
	
//////////////////// TESTING EXAMPLES STARTS ///////////////
	clr(checkprob);

	for(int i=0;i<1000;i++)			
	{
		clr(checkprob);
		getline(tel,s);
		int n=s[0]-'0';
		for(int j=0;j<28;j++)
		{
			getline(tei,st);
			for(int k=0;k<28;k++)
			{
				if(st[k]=='+' || st[k]=='#')
					checkprob[j][k]=1;					
			}
		}
		testcnt[n]++;
		////// ACCURACY CHECK /////
		clr(posterior);
		maxele=0;
		for(int j=0;j<10;j++)    //POSTERIOR PROBABILTY CALCULATION FOR EACH NUMBER
		{
			posterior[j]+=log(prior[j]);
			for(int k=0;k<28;k++)
			{
				for(int l=0;l<28;l++)
				{
					if(checkprob[k][l]==0)
						posterior[j]+=log(1-likelihood[j][k][l]);
					else
						posterior[j]+=log(likelihood[j][k][l]);
				}
			}
			if(posterior[j]>posterior[maxele])
				maxele=j;
		}
		ansprob[maxele][n]++;
		if(maxele==n)
			correctresult++;   // NO. OF CORRECT RESULTS
	}
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
			ansprob[j][i]=(double)(ansprob[j][i]/(double)testcnt[i]);   // FINAL PROBABILTY OF NUMBERS
	}
	
	/////////////////// TESTING EXAMPLES ENDS ////////////////
	
	////////////////// PRINT RESULTS/////////////////
	
	cout<<"Correct results are "<<correctresult<<" out of 1000 test data."<<endl<<endl;;
	
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			if(i==j)
				eachnumprob[i]=ansprob[i][i]*100.0;
			cout<<setprecision(2)<<ansprob[i][j]*100.0<<"  ";
		}
		cout<<endl;
	}
	cout<<endl;
	for(int i=0;i<10;i++)
		cout<<"Number="<<i<<" --> "<<setprecision(2)<<eachnumprob[i]<<endl;
	
	////////////////END OF PROGRAM////////////////

	return 0;
}


