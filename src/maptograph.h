#include <iostream>
#include <string>
#include <vector>
#include "routingfunctions.h"


struct turning{
	int x,y;
};
struct vertex
{
	turning point;
	int weight;
};
struct row{
	int x,y;
	vector<vertex> nodes;
};
bool operator<(const vertex &a,const vertex &b)
{
	return a.weight<b.weight;
}

//Converts map to Graph
class maptograph{
	vector <row> G;
	vector<string> path;
	vector<string> temp;
	vector<turning> route;
	int ix,iy;
public:

	maptograph()
	{
		filereader t;
		path = t.returnvector();
		temp = path;
		ix = 13;
		iy = 7;
		convert2();
	}

	
	int checksides(int x,int y)
	{
		int count = 0;
		int arr[4] = {0,0,0,0};
		if(temp[x-1][y]==' '||temp[x-1][y]=='*')
		{
			arr[0]++;
			count++;
		}
		if(temp[x+1][y]==' '||temp[x+1][y]=='*'){
			arr[1]++;
			count++;
		}
		if(temp[x][y-1]==' '||temp[x][y-1]=='*'){
			arr[2]++;
			count++;
		}
		if(temp[x][y+1]==' '||temp[x][y+1]=='*'){
			arr[3]++;
			count++;
		}

		if(count>2)
			return 1;
		else if(count==2)
		{
			if(arr[0] && arr[2])
				return 1;
			if(arr[0] && arr[3])
				return 1;
			if(arr[1] && arr[2])
				return 1;
			if(arr[1] && arr[3])
				return 1;
			else return 0;
		}
		else if(count==1)
			return 1;
		else return 0;

	}
	void reset()
	{
		filereader x;
		//vector<string> out = x.soutarmap();
		x.reset();
	}

	void convert2()
	{
		vector<turning> points;
		for(int i=0;i<temp.size();i++)
		{
			for(int j=0;j<temp[i].size();j++)
			{
				if(temp[i][j] == ' ' || temp[i][j] == '*'){
					if(checksides(i,j))
					{
						//it is worth to create a node
						turning t = {i,j};
						points.push_back(t);
					}
				}
			}
		}

		for(int i=0;i<points.size();i++)
		{
			row t;
			t.x = points[i].x;
			t.y = points[i].y;
			G.push_back(t);
		}
		//Creating Graph points
		for(int i=0;i<G.size();i++)
		{
			int x = G[i].x;
			int y = G[i].y;
			//upward
			for(int k = x-1;k>=0;k--)
			{
				if(temp[k][y]=='0')
					break;
				else if(checksides(k,y))
					{
						vertex g;
						g.point.x = k;
						g.point.y = y;
						g.weight = abs(x-k);
						G[i].nodes.push_back(g);
						break;
					}
			}
			
			for(int k = x+1;k<temp.size();k++)
			{
				if(temp[k][y]=='0')
					break;
				else if(checksides(k,y))
				{
					vertex g;
					g.point.x = k;
					g.point.y = y;
					g.weight = abs(x-k);
					G[i].nodes.push_back(g);
					break;
				}
			}
			for(int k = y-1;k>=0;k--)
			{
				if(temp[x][k]=='0')
					break;
				else if(checksides(x,k))
				{
					vertex g;
					g.point.x = x;
					g.point.y = k;
					g.weight = abs(y-k);
					G[i].nodes.push_back(g);
					break;
				}
			}
			for(int k= y+1;k<temp[x].size();k++)
			{
				if(temp[x][k]=='0')
					break;
				else if(checksides(x,k))
				{
					vertex g;
					g.point.x = x;
					g.point.y = k;
					g.weight = abs(y-k);
					G[i].nodes.push_back(g);
					break;
				}
			}
		}

	}
	
	void printGraph()
	{
		for(int i=0;i<G.size();i++)
		{
			cout<<G[i].x+1<<" "<<G[i].y+1;
			for(int k=0;k<G[i].nodes.size();k++)
			{
				cout<<"->"<<G[i].nodes[k].point.x+1<<" "<<G[i].nodes[k].point.y+1<<" | "<<G[i].nodes[k].weight<<" ";
			}
			cout<<endl;
		}
	}
	int Find()
	{
		filereader t;
		vector<int> out = t.soutar();
		if(out.size()!=4){
			cout<<"Select source and destination";
			return 1;
		}
		int sx,sy,tx,ty;
		sx = out[0];
		sy = out[1];
		tx = out[2];
		ty = out[3];
		//cout<<checksides(sx,sy)<< checksides(tx,ty)<<endl;
		if(checksides(sx,sy) && checksides(tx,ty))
		{
			Findpath( sx,sy,tx,ty);
		}

		return 0;

	}
	void Findpath(int ax,int ay,int bx,int by)
	{
	
		Dijkstra(bx,by,ax,ay);
	}
	
	
	int gotvisited(int vis[][3],int x,int y)
	{
		for(int i=0;i<G.size();i++)
			if(vis[i][0]==x && vis[i][1]==y){
				if(vis[i][2]==1)
					return 1;
				break;
			}
		return 0;

	}
	void swap(int &a,int &b)
	{
		int t = a;
		a = b;
		b = t;
	}
	void Dijkstra(int ax,int ay,int bx,int by)
	{
		
		int visited[G.size()][3];
		int dist[G.size()][3];
		int prev[G.size()][4];
		for(int i=0;i<G.size();i++)
		{
			visited[i][2] = 0;visited[i][0] = G[i].x;visited[i][1] = G[i].y;
			dist[i][2] = 10000000;dist[i][0] = G[i].x;dist[i][1] = G[i].y;
			prev[i][0] = G[i].x;
			prev[i][1] = G[i].y;
			prev[i][2] = -1;
			prev[i][3] = -1;
			if(dist[i][0] == ax && dist[i][1]==ay){
				dist[i][2] = 0;
				prev[i][2] = prev[i][3] = 0;
			}
		}

		vertex e;
		e.point.x = ax;
		e.point.y = ay;
		e.weight = 0;
		vector <vertex> Q;
		Q.push_back(e);
		int couunt = 0;

		while(!Q.empty())
		{
			/*for(int aw = 0;aw<Q.size();aw++)
			{
				cout<<Q[aw].point.x<<" "<<Q[aw].point.y<<" ";
			}
			cout<<endl;*/

			couunt++;

			sort(Q.begin(),Q.end());

			e.point.x = Q[0].point.x;
			e.point.y = Q[0].point.y;

//			cout<<"Q first point"<<e.point.x<<" "<<e.point.y<<endl;
			int visit=0;
			int i;
			for(i=0;i<G.size();i++)
			{
				if(visited[i][0]==e.point.x && visited[i][1]==e.point.y){
					visit = visited[i][2]?1:0;
					break;
				}

			}
			//if(couunt==19){
			//	cout<<"viited"<<visit;
				//break;
			//}
				
			if(visit==1){
				Q.erase(Q.begin());
				continue;
			}
			

			visited[i][2] = 1;
			int k;
			int gotbreak=0;
				
			for(k=0;k<G.size();k++)
			{
				if(G[k].x==visited[i][0] && G[k].y == visited[i][1])
				{
					for(int h=0;h<G[k].nodes.size();h++)
					{

			
						if(gotvisited(visited,G[k].nodes[h].point.x,G[k].nodes[h].point.x)==0)
						{
							int indd = 0,ac;
							int ua=G[k].nodes[h].point.x ,ub = G[k].nodes[h].point.y;
							for(ac = 0;ac<G.size();ac++)
							{
								if(dist[ac][0]==ua && dist[ac][1]==ub){
									break;
								}
							}

							if(dist[i][2] + G[k].nodes[h].weight < dist[ac][2])
							{
								dist[ac][2] = dist[i][2] + G[k].nodes[h].weight;
							
								e.point.x = G[k].nodes[h].point.x;
								e.point.y = G[k].nodes[h].point.y;

								prev[ac][2] = visited[i][0];
								prev[ac][3] = visited[i][1];
								Q.push_back(e);
									
				
								//cout<<e.point.x<<" "<<e.point.y;

							}
						}

						
					}
					Q.erase(Q.begin());
					
				}	
			}
			
		}
		
		
		calculateroute(prev,bx,by);
		

	}
	void checkmap()
	{
		for(int i=0;i<path.size();i++)
			for(int j=0;j<path[i].size();j++)
				if(path[i][j]!='0' && path[i][j]!='*' && path[i][j]!=' '){
					cout<<"error";break;
				}

	}
	void calculateroute(int prev[][4],int x,int y)
	{	
		int tx,ty;
		turning t;
					t.x = x;
					t.y = y;
					route.push_back(t);
		for(int i=0;i<G.size();i++)
			if(prev[i][0]==x && prev[i][1]==y)
			{
				if(prev[i][2]!=0 && prev[i][3]!=0){
					
				//	cout<<prev[i][2]+1<<" "<<prev[i][3]+1<<"->";
					calculateroute(prev,prev[i][2],prev[i][3]);
				}

				
				break;
			}
	}
	void routeprinter()
	{
		for(int i=0;i<route.size();i++)
			cout<<route[i].x+1<<" "<<route[i].y+1<<endl;
	}
	void printstoredroute()
	{
		vector<string>just;
		just = path;
		for(int i=1;i<route.size();i++)
		{
			if(route[i-1].x>route[i].x)
				just[route[i-1].x][route[i-1].y] = '^';
			else if(route[i-1].x<route[i].x)
				just[route[i-1].x][route[i-1].y] = 'v';
			else if(route[i-1].y>route[i].y)
				just[route[i-1].x][route[i-1].y] = '<';
			else
				just[route[i-1].x][route[i-1].y] = '>';
		}
		for(int i=0;i<just.size();i++)
			cout<<just[i]<<endl;
	}
	void testvicinity()
	{
		int currx = ix,curry = iy;
		vector<string>o =  vicinity(path,ix,iy);
		cout<<"drawing vicinity"<<endl;

		for(int i=0;i<o.size();i++)
		{
			for(int j=0;j<o[i].size();j++)
			{
				cout<<o[i][j];
			}
			cout<<endl;
		}
	}

};