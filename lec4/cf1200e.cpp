#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int border[N];

int Border(string s1,string s2){
	int j=0,n=s1.size(),m=s2.size(),res=0,x=min(n,m);
	for(int i=1;i<x;i++){
		while(j>0&&s1[i]!=s2[j]) j=border[j-1];
		if(s1[i]==s2[j]) j++;
		border[i]=j;
		res=max(res,border[i]);
	}
	return res;
}

int main(){
	int n;cin>>n;
	string t="",p="";
	for(int i=1;i<=n;i++){
		cin>>p;
		if(t=="") t=p;
		else{
			int len=p.size();
			int x=Border(t,p);
			for(int j=x;j<len;j++) t+=p[j];
		}
	}
	cout<<t;
	return 0;
}