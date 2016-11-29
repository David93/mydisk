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
	if(current_size+bytes>size && x!=0)
		return 0;
	if(current_size-old_length+bytes>size && x==0)
		return 0;
	if(x==0)
		current_size-=old_length;
	current_size+=bytes;
	//if(current_size>1048500)
	//log_msg("Current size:"+to_string(current_size)+", added size:"+to_string(bytes)+"\n");
	return 1;
}
void initFS(string disk_size, string filename){
	dir_node root;
	root.isFolder=1;
	root.name="ROOT";
	root.path="/";
	table["/"]=root;
	int k=0;
	imagename=filename;
	size=atoi(disk_size.c_str())*1024*1024;
	//size=10;
	if(filename.compare("none")!=0){
		if(ifstream(filename))
		{

			restoreimage();
			k=1;
		}
	}
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
void saveimage(){
	map<string,dir_node>::iterator it;
	ofstream image;
	image.open (imagename);
	for(it=table.begin();it!=table.end();it++)
	{	//log_msg(it->first+":"+(it->second).name+":");
		image << (it->second).name<<endl;
		image << (it->second).path<<endl;
		image << to_string((it->second).isFolder)<<endl;
		image << (it->second).data <<"|"<<endl;
	}
}
void restoreimage(){
	ifstream image;
	image.open (imagename);
	string name, path, data, line;
	int isFolder;
	int k=0;
	while (std::getline(image, line))
	{	//log_msg(it->first+":"+(it->second).name+":");
		
		if(k==0)
		{	
			name=line;
		}
		if(k==1)
		{	
			path=line;
		}
		if(k==2)
		{	
			isFolder=atoi(line.c_str());
			
		}
		if(k==3){
			
			string temp("");
			temp=line;
			int found=temp.find("|");
			if(found==-1)
			{	
				k--;
				data+=temp;
			}
			else
			{
				if(found!=0)
					data+=temp.substr(0,found-1);
				
			}
		}
		k++;
		
		if(k==4){
			k=0;
			dir_node file;
			file.path=path;
			file.isFolder=isFolder;
			file.name=name;
			file.data=data;
			table.insert({path,file});
		}
		
		
	}
	printtable();
	
}