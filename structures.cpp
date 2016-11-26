#include <string>
#include <map>
#include <iostream>
#include <list>
using namespace std;

class dir_node
{
	public:
	int isFolder;
	string data;
	list<dir_node> child_list;
};

map<string,dir_node> table;

void initFS(){
	dir_node root;
	root.isFolder=1;
	table["/"]=root;
	cout<<"FS Initialized"<<endl;
}

void addTable(string path){
	int found=path.find_last_of("/");
	string parent=path.substr(0,found);

}