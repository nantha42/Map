#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
struct entities{
	int x,y;
	string name;
};
class locationsearch{
	string name;
	locationsearch()
	{
		name = "entities.txt";
	}

};
class filereader{
	string name;
	string name2;
	string name3;
	ifstream file;
public:
	filereader()
	{
		name = "roadmap1.txt";
		name2 = "entities.txt";
		name3 = "userhand.txt";
	}
	vector<int> soutar()
	{
		vector<int> out;
		file.open(name3);
		vector<string> data;
		string line;
			while(getline(file,line))
		{
			data.push_back(line);
		}
		file.close();
		int sx,sy,tx,ty;
		for(int i=0;i<data.size();i++)
			for(int j=0;j<data[i].size();j++){
				if(data[i][j]=='s'){
					sx = i;
					sy = j;
					
					break;
				}
				if(data[i][j]=='t')
				{
					tx = i;
					ty = j;
					break;
				}
			}
		out.push_back(sx);
		out.push_back(sy);
		out.push_back(tx);
		out.push_back(ty);
		return out;

	}
	vector<string> soutarmap()
	{
		
		file.open(name3);
		vector<string> data;
		string line;
		while(getline(file,line))
		{
			data.push_back(line);
		}
		file.close();
		cout<<data.size();
		return data;	

	}
	void reset()
	{
		ofstream r(name3,ios::out);
		vector<string> out = returnvector();

		for(int i=0;i<out.size();i++){

			for(int j=0;j<out[i].size();j++)
				r<<out[i][j];
			r<<endl;
		}
		r.close();

	}

	vector<string> returnvector()
	{
		file.open(name);
		vector <string> data;
		string line;
		while(getline(file,line))
		{
			data.push_back(line);
		}
		file.close();
		return data;
	}
	vector<entities> returnentities()
	{
		vector <entities> records;
		entities a;
		file.open(name2);
		
		while(true)
		{
			if(file.eof())break;
			
			file>>a.x>>a.y>>a.name;
			records.push_back(a);

		}
		
		return records;
	}
	string findlocation(int x,int y)
	{
		entities a;
		file.open(name2);

		while(true)
		{
			if(file.eof()) break;

			file>>a.x>>a.y>>a.name;
			if(a.x == x && a.y == y){
				file.close();
				return a.name;
			}
		}
		return "Not Found";
	}
	~filereader()
	{
		file.close();
	}
};
