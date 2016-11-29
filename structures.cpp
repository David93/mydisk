#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <list>
#include "structures.h"
#include <stdio.h>
using namespace std;
int run=0;
long size;
long current_size=0;
string imagename;
map<string,dir_node> table;
void log_msg(string s){

  	
  ofstream myfile;
  if(run==1)
  	myfile.open ("/afs/unity.ncsu.edu/users/d/dmjoshy/501p4/mydisk/log.txt",ios::out | ios::app );
  else
  	myfile.open ("/afs/unity.ncsu.edu/users/d/dmjoshy/501p4/mydisk/log.txt");
  run =1;
  myfile << s;
  myfile.close();
	
}
int checksize(int bytes, int x, int old_length){
	//log_msg("Current size:"+to_string(current_size)+", added size:"+to_string(bytes)+"\n");
	//log_msg("Current size:"+to_string(current_size)+", added size:"+to_string(bytes)+" append "+to_string(x)+"\n");
	
	if(current_size+bytes>size && x!=0)
		return 1;
	if(current_size-old_length+bytes>size && x==0)
		return 1;
	if(x==0)
		current_size-=old_length;
	current_size+=bytes;
	
	return 0;
}
void initFS(string disk_size, string filename){
	dir_node root;
	root.isFolder=1;
	root.name="ROOT";
	root.path="/";
	table["/"]=root;
	
	imagename=filename;
	size=atoi(disk_size.c_str())*1024*1024;
	//size=10;
	//log_msg("FS Initialized with size " + to_string(size) +" from image at "+to_string(k)+"\n");
}

void addTable(string path, int isFolder){
	//log_msg("Adding new path to table:"+path+"\n");
	int found=path.find_last_of("/");
	string parent;
	if(found!=0)
		parent=path.substr(0,found);
	else
		parent="/";
	dir_node child;
	child.path=path;
	child.isFolder=isFolder;
	child.name=path.substr(found+1);
	//log_msg("Parent name:"+parent);
	//log_msg(", Child name:"+child.name+"\n");
	table.insert({path,child});
	table[parent].child_list.push_back(child);

}
void rmTable(string path){
	//log_msg("Erasing path "+path+"\n");
	//Calling delete on child list
	int x=(table[path].data).length();
	current_size-=x;
	//printtable();
	//log_msg("Current size:"+to_string(current_size)+", removed size:"+to_string(x)+"\n");
	
	table.erase(path);
	int found=path.find_last_of("/");
	string parent;
	if(found!=0)
		parent=path.substr(0,found);
	else
		parent="/";
	string child=path.substr(found+1);

	list<dir_node>::iterator it;
	//log_msg("Parent name:"+parent);
	//log_msg(", Child name:"+child+"\n");
	//Deleting myself from parent's list
	for (it = table[string(parent)].child_list.begin(); it != table[string(parent)].child_list.end(); ++it) {
		if(child.compare((*it).name)==0)
   		{	it=table[string(parent)].child_list.erase(it);}
	}
	//log_msg("Finished erasing path "+path+"\n");
}
void rmfTable(string path){
	
	//log_msg("Erasing path "+path+"\n");
	int found=path.find_last_of("/");
	string parent;
	if(found!=0)
		parent=path.substr(0,found);
	else
		parent="/";
	string child=path.substr(found+1);
	
   	list<dir_node>::iterator it2;
   	//Calling delete on child list
   	for(it2=table[path].child_list.begin();it2!=table[path].child_list.end();it2=table[path].child_list.begin()){
		//log_msg("Deleting sub "+path+"/"+(*it2).name+"\n");
		if((*it2).isFolder==1)
			rmfTable(path+"/"+(*it2).name);
		else
			rmTable(path+"/"+(*it2).name);
		
	}
	//Deleting myself from table
	table.erase(path);
	//Deleting myself from parent's list
	list<dir_node>::iterator it;
	for (it = table[string(parent)].child_list.begin(); it != table[string(parent)].child_list.end(); ++it) {
		if(child.compare((*it).name)==0)
   		{	

   			it=table[string(parent)].child_list.erase(it);break;
   		}
	} 
	
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