//#include "filereader.h"
//#include "routingfunctions.h"
#include "src/maptograph.h"
using namespace std;
/*int main()
{
	vector <string> t;
	filereader a;

	t = a.returnvector();
	vector <entities> q = a.returnentities();
	cout<<t.size();
	cout<<t[9][76]<<endl;
	cout<<q.size();

	for(int i=0;i<q.size();i++)
	{
		cout<<q[i].x<<" "<<q[i].y<<" "<<q[i].name<<endl;
		
	}
	
}
*/
/*
int main()
{
	vector <string> t;
	filereader a;
	t = a.returnvector();
	
	int x,y,arr[2];
	x =26;y = 19;

	findroad(t,x,y,arr);
	cout<<arr[0]+1<<" "<<arr[1]+1<<endl;
	cout<<"symbol at ="<<t[arr[0]][arr[1]]<<endl;
	vicinity(t,arr[0],arr[1]);

}*/
int main()
{
	maptograph k;
	
	//k.printGraph();
	
	//k.convert2();
	//k.checkmap();
	//k.Find();
	k.reset();
	//k.printGraph();
	//k.Findpath(13,7,41,79);
	//k.Findpath(51,13,13,24);
	
	//k.routeprinter();
	//k.printstoredroute();




}