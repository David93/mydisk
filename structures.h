#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <list>

using namespace std;
class dir_node
{
	public:
	int isFolder;
	string path;
	string name;
	string data;
	list<dir_node> child_list;
};

extern map<string,dir_node> table;

void initFS(string disk_size, string filename);
int checksize(int bytes, int x, int old_length);
void addTable(string path, int isFolder);
void rmTable(string path);
void rmfTable(string path);
void log_msg(string path);
void printtable();
void saveimage();
void restoreimage();