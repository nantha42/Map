#include <iostream>
#include <vector>
#include <math.h>
#include <map>
#include <string>
#include "filereader.h"
using namespace std;

class RouteFinder{
	string mapfile;
	vector <string> path;
	string outputfile;
public:
	RouteFinder()
	{
		filereader t;
		path = t.returnvector();
		outputfile = "result.txt";

	}
	void findroute(int sx,int sy,int tx,int ty)
	{
		if((path[sx][sy]!=' ' || path[sx][sy]!='*') && (path[tx][ty]!=' ' || path[tx][ty]!='*'))
			return;

				
	}
};

float distance(int x,int y,int a,int b)
{
	return sqrt((x-a)*(x-a)+(y-b)*(y-b));
}

vector<string> vicinity(std::vector<std::string> map,int posx,int posy)
{
	
	int s = 1;
	vector<string> a;
	
	for(int i=posx-s;i<=posx+s;i++)
	{
		string u;

		for(int j=posy-s;j<=posy+s;j++)
		{
			if(i>=0 && j>=0 && i<map.size() && j<map[i].size())
			{
			//	cout<<map[i][j];
				u= u + map[i][j];
			}
		}
		a.push_back(u);
		
	}
	return a;
}
/*
void vicinity(std::vector<std::string> map,int posx,int posy)
{
	cout<<endl;
	int s = 1;
	
	for(int i=posx-s;i<=posx+s;i++)
	{
		for(int j=posy-s;j<=posy+s;j++)
		{
			if(i>=0 && j>=0 && i<map.size() && j<map[i].size())
			{
				cout<<map[i][j];
			}
		}
		cout<<endl;
	}
}
*/
void findroad(std::vector<std::string> map,int posx,int posy,int arr[])
{
	int x= posx,y = posy;
	bool found = false;
	float dist = 1000000;
	//box search
	int size = 1;//increases in odd number
	int fx,fy;
	
	int i,j;
	while(not found)
	{
		
		dist = 1000000;
			for(int j=posy-size;j<=posy+size;j++)
			{
				//top row
				if(posx-size>=0 && j>=0 && j<map[posx-size].size())
				{
					if(map[posx-size][j]==' '||map[posx-size][j] == '*'){

						float adist = distance(posx-size,j,posx,posy);
						if(dist>adist)
						{
							fx = posx-size;
							fy = j;
							//cout<<fx<<" "<<fy<<endl;
							vicinity(map,fx,fy);
							dist = adist;
						}
						found = true;
					}
				}

				//bottom row
				//possible to error in if condition
				if(posx+size<map.size() && j>=0 && j<map[posx+size].size())
				{
					if(map[posx+size][j]==' '||map[posx+size][j]=='*')
					{
						float adist = distance(posx+size,j,posx,posy);
						if(dist>adist)
						{
							fx = posx+size;
							fy = j;
							//cout<<fx<<" "<<fy<<endl;
							vicinity(map,fx,fy);
							dist = adist;

						}
						found = true;

					}
				}
			}
		
		//right column
			for(int i = posx-size;i<=posx+size;i++)
			{
				if(i>=0 && posy+size <map[i].size() && i<map.size() )
				{
					if(map[i][posy+size]==' '||map[i][posy+size]=='*'){
						float adist = distance(i,posy+size,posx,posy);
						if(dist>adist)
						{
							fx = i;
							fy = posy+size;
						//	cout<<fx<<" "<<fy<<endl;
							vicinity(map,fx,fy);
							dist = adist;
						}
						found = true;	
					}
				}
				if(i>=0 && posy-size >=0 && i<map.size())
				{
					if(map[i][posy-size]==' ' || map[i][posy+size] == '*' ){
						float adist = distance(i,posy-size,posx,posy);
						if(dist>adist)
						{
							fx = i;
							fy = posy-size;
						//	cout<<fx<<" "<<fy<<endl;
							vicinity(map,fx,fy);
							dist = adist;
						}
						found = true;	
					}
				}
			}
		size+=1;
	
	}
	arr[0]=fx;
	arr[1]=fy;
	
}
