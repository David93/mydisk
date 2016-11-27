#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <list>
#include "structures.h"
#include <stdio.h>
using namespace std;
int run=0;
map<string,dir_node> table;
void log_msg(string s){
  ofstream myfile;
  if(run==1)
  	myfile.open ("/home/dmjoshy/mydisk/log.txt",ios::out | ios::app );
  else
  	myfile.open ("/home/dmjoshy/mydisk/log.txt");
  run =1;
  myfile << s;
  myfile.close();

}
void initFS(){
	dir_node root;
	root.isFolder=1;
	root.name="ROOT";
	table["/"]=root;
	log_msg("FS Initialized\n");
}

void addTable(string path, int isFolder){
	log_msg("Adding new entry to table\n");
	int found=path.find_last_of("/");
	string parent=path.substr(0,found+1);
	dir_node child;
	child.isFolder=isFolder;
	child.name=path.substr(found+1);
	log_msg("Parent name:"+parent);
	log_msg(", Child name:"+child.name+"\n");
	table[path]=child;
	table[parent].child_list.push_back(child);

}
void rmTable(string path){
	table.erase(path);
	int found=path.find_last_of("/");
	string parent=path.substr(0,found+1);
	string child=path.substr(found+1);
	list<dir_node>::iterator it;
	for (it = table[string(parent)].child_list.begin(); it != table[string(parent)].child_list.end(); ++it) {
		if(child.compare((*it).name)==0)
   		{	it=table[string(parent)].child_list.erase(it);break;}
	} 
	
}
void rmfTable(string path){
	table.erase(path);
	int found=path.find_last_of("/");
	string parent=path.substr(0,found+1);
	string child=path.substr(found+1);
	list<dir_node>::iterator it;
	for (it = table[string(parent)].child_list.begin(); it != table[string(parent)].child_list.end(); ++it) {
		if(child.compare((*it).name)==0)
   		{	//if((*it).isFolder==1)
   			//	rmfTable
   			it=table[string(parent)].child_list.erase(it);break;}
	} 
	
}
