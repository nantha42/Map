#include "src/maptograph.h"
using namespace std;

int main()
{
	int k=1,a;
	cout<<"1.Findroute"<<endl
		<<"2.resetmap"<<endl;

	cout<<"0.quit"<<endl;

	while(k){
		cout<<">>>";
		cin>>k;
		maptograph t;
		switch(k)
		{
			case 1:
				cout<<"Enter the source and target"<<endl;
				
				a = t.Find();
				if(a==0)
					t.printstoredroute();
				break;
			case 2:
				
				t.reset();
				break;
			
		}
		
	}
}