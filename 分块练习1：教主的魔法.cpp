#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>
#include<algorithm>
#include<string.h>
using namespace std; 
vector<int>v[300001];
int n,q,a[3000001],block[3000001],l,r,c,sum[3000001],n1,ans;
char ch;
void resort(int x)
{
	v[x].clear();
	for(int j=(x-1)*n1+1;j<=min(x*n1,n);++j)
	v[x].push_back(a[j]);
	sort(v[x].begin(),v[x].end());
}
void add(int lr,int rr,int d)
{
	if(block[lr]==block[rr]) 
	{
		for(int i=lr;i<=rr;++i) a[i]+=d;
		resort(block[lr]);
	}
	else 
	{
		for(int i=lr;i<=block[lr]*n1;++i)  a[i]+=d;
		resort(block[lr]);
		for(int i=(block[rr]-1)*n1+1;i<=rr;++i)  a[i]+=d;
		resort(block[rr]);
		for(int i=block[lr]+1;i<block[rr];++i) sum[i]+=d;
	}
	
}
void cha(int lr,int rr,int d)
{
	ans=0; 
	if(block[lr]==block[rr]) 
	{
		for(int i=lr;i<=rr;++i)
			if(a[i]>=d-sum[block[lr]]) 
				ans++; 
	}
	else
	{
	for(int i=lr;i<=block[lr]*n1;++i) if(a[i]+sum[block[lr]]>=d) ans++;
	for(int i=(block[rr]-1)*n1+1;i<=rr;++i) if(a[i]+sum[block[rr]]>=d) ans++; 
 	for(int i=block[lr]+1;i<block[rr];++i) 
	{
	/*	int c=d-sum[i];
		int a1=lower_bound(v[i].begin(),v[i].end(),c)-v[i].begin();
		ans=ans+n1-a1;*/
		int lx=0,rx=n1;
		while (lx<rx)
		{
			int mid=(lx+rx)/2;
			if(v[i][mid]<d-sum[i])  lx=mid+1;
			else rx=mid;
		}
		ans=ans+n1-lx;//事实证明手打二分要比stl库的函数调用要快。 
	}
	}
	cout<<ans<<endl;
}
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int main()
{
	freopen("P2801_4.in","r",stdin);
	freopen("1.out","w",stdout); 
	n=read();q=read();
	n1=sqrt(n);
	memset(sum,0,sizeof(sum));
	for(int i=1;i<=n;++i) a[i]=read();
	for(int i=1;i<=n;++i)
	{
			block[i]=(i-1)/n1+1;
			v[block[i]].push_back(a[i]);
	}
	for(int i=1;i<=block[n];++i)
		sort(v[i].begin(),v[i].end());
/*	for(int i=1;i<=n1+1;++i) 
	{
		for(int j=(i-1)*n1+1;j<=min(i*n1,n);++j)
			{
				v[i].push_back(a[j]);
				block[j]=i;
				//cout<<i<<" "<<j<<endl;
			}
		sort(v[i].begin(),v[i].end());	
	}*/
//	cout<<block[n]<<endl;
//	for(int j=0;j<v[n1+1].size();++j)	cout<<v[n1+1][j]<<" ";
	while(q!=0)
	{
		scanf("%s",&ch);
		l=read();r=read();c=read();
		if(ch=='A') cha(l,r,c);
		else add(l,r,c);
		q--;
	}
	return 0;
	//特殊数据的卡位（十分容易RE），考虑问题时是否又考虑到特殊情况，与题目的一般性解法，与优化之处。 
}
