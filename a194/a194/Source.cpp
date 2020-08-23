#include<iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <cstdlib>
#include <climits>
using namespace std;


int gcd(int a, int b)
{
	if (b == 0)
		return a;
	else
		return gcd(b, a % b);
}

pair<int,int> findSlope(pair<int,int> a ,pair<int,int> b) 
{
	if(a.first==b.first){return pair<int,int> (0,1);}
    if(a.second==b.second){return pair<int,int> (1,0);}
    
	pair<int, int> tmp(a.first - b.first,a.second - b.second);
	int g = gcd(abs(tmp.first), abs(tmp.second));
	return pair<int,int> (tmp.first/g,tmp.second/g);
}

int main() 
{
	int N;
	while (scanf("%d", &N) != EOF) 
	{
		vector< pair<int, int> >  points;
		vector< pair<int, int> > slopes;
		for (int i = 0; i < N;i++) 
		{
			pair <int, int> tmp;
			scanf("%d %d",&tmp.first,&tmp.second);
			points.push_back(tmp);
		}
		for (int i = 0; i < points.size(); i++)
		{
			for (int j = i+1; j < points.size();j++) 
			{
				slopes.push_back(findSlope(points[i],points[j]));
			}
		}
		vector<int> slopesNo(slopes.size(),0);
		for (int i = 0; i < slopes.size(); i++)
		{
			for(int j = 0;j < slopes.size();j++)
			{
			
				if (slopes[i].first == slopes[j].first && slopes[i].second == slopes[j].second
					||  slopes[i].first == (-1)*slopes[j].first && slopes[i].second == (-1)*slopes[j].second)
					{
					slopesNo[i]++;
				}
				
			}
		}
		int maxAppearNo = 0;
		for (int i = 0; i < slopesNo.size();i++) {
			if (slopesNo[i] > maxAppearNo) {
				maxAppearNo = slopesNo[i];
			}
		}
		printf("%d",maxAppearNo);
	}
	return 0;
}

