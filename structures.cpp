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
	log_msg("Adding new path to table:"+path+"\n");
	int found=path.find_last_of("/");
	string parent;
	if(found!=0)
		parent=path.substr(0,found);
	else
		parent="/";
	dir_node child;
	child.isFolder=isFolder;
	child.name=path.substr(found+1);
	log_msg("Parent name:"+parent);
	log_msg(", Child name:"+child.name+"\n");
	table[path]=child;
	table[parent].child_list.push_back(child);

}
void rmTable(string path){
	log_msg("Erasing path "+path+"\n");
	table.erase(path);
	int found=path.find_last_of("/");
	string parent;
	if(found!=0)
		parent=path.substr(0,found);
	else
		parent="/";
	string child=path.substr(found+1);
	list<dir_node>::iterator it;
	printtable();
	log_msg("Parent name:"+parent);
	log_msg(", Child name:"+child+"\n");
	
	for (it = table[string(parent)].child_list.begin(); it != table[string(parent)].child_list.end(); ++it) {
		if(child.compare((*it).name)==0)
   		{	it=table[string(parent)].child_list.erase(it);}
	}
	printtable(); 
	log_msg("Finished erasing path "+path+"\n");
}
void rmfTable(string path){
	
	log_msg("Erasing path "+path+"\n");
	int found=path.find_last_of("/");
	string parent;
	if(found!=0)
		parent=path.substr(0,found);
	else
		parent="/";
	string child=path.substr(found+1);
	
   	list<dir_node>::iterator it2;
   	printtable();
   	
	for(it2=table[path].child_list.begin();it2!=table[path].child_list.end();it2=table[path].child_list.begin()){
		log_msg("Deleting sub "+path+"/"+(*it2).name+"\n");
		if((*it2).isFolder==1)
			rmfTable(path+"/"+(*it2).name);
		else
			rmTable(path+"/"+(*it2).name);
		
	}
	table.erase(path);
	printtable();
	list<dir_node>::iterator it;
	for (it = table[string(parent)].child_list.begin(); it != table[string(parent)].child_list.end(); ++it) {
		if(child.compare((*it).name)==0)
   		{	

   			it=table[string(parent)].child_list.erase(it);break;
   		}
	} 
	printtable();
}
void printtable(){
	map<string,dir_node>::iterator it;
	log_msg("Printing out the MAP\n");
	for(it=table.begin();it!=table.end();it++)
	{	log_msg(it->first+":"+(it->second).name+":");
		list<dir_node>::iterator it2;
		for(it2=(it->second).child_list.begin();it2!=(it->second).child_list.end();it2++)
			log_msg(it2->name+" ");
		log_msg("\n");
	}
}
