// Hello filesystem class implementation

#include "helloFS.h"

#include <iostream>
#include "structures.h"
#include <stdio.h>
#include <string>
#include <list>
// include in one .cpp file
#include "Fuse-impl.h"


int HelloFS::getattr(const char *path, struct stat *stbuf)
{
	
	//int res = 0;
	//log_msg("Running getattr on "+string(path)+"\n");
	memset(stbuf, 0, sizeof(struct stat));
	if(table.count(string(path))==0)
		return -ENOENT;
	
	if(table[string(path)].isFolder==0){
		stbuf->st_mode = S_IFREG | 0444;
		stbuf->st_nlink = 1;
		stbuf->st_size = 20;
	}
	else
	{
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;
	}
	return 0;
}

int HelloFS::readdir(const char *path, void *buf, fuse_fill_dir_t filler,
			               off_t, struct fuse_file_info *)
{
	//log_msg("Running readdir\n");
	filler(buf, ".", NULL, 0);
	filler(buf, "..", NULL, 0);
	list<dir_node>::iterator it;
	//log_msg("Helloo");
	//filler(buf, "a", NULL, 0);
	list<dir_node> files;
	files=table[string(path)].child_list;
	//filler(buf,path+1,NULL,0);
	//log_msg("ls at path "+string(path)+"\n");
	
	for (it = files.begin(); it != files.end(); ++it) {
   		filler(buf, (*it).name.c_str(), NULL, 0);
	} 
	return 0;
}


int HelloFS::open(const char *path, struct fuse_file_info *fi)
{
	//log_msg("Running open\n");
	//log_msg("Flags="+to_string(fi->flags));
	
	return 0;

}

int HelloFS::opendir (const char *path, struct fuse_file_info *fi)
{
	//log_msg("Running opendir\n");
	return 0;
}
int HelloFS::read(const char *path, char *buf, size_t size, off_t offset,
		              struct fuse_file_info *fi)
{
	//log_msg("Running read on "+string(path)+"\n");
	size_t len;
	(void) fi;
	if(table.count(string(path))==0)
		return -ENOENT;
	string data=table[string(path)].data;
	len = strlen(data.c_str());
	if ((size_t)offset < len) {
		if (offset + size > len)
			size = len - offset;
		memcpy(buf, data.c_str() + offset, size);
	} else
		size = 0;

	return size;
}
int HelloFS::write(const char *path,const char *buf, size_t size, off_t offset,
		              struct fuse_file_info *fi)
{
	log_msg("Running write\n");
	//log_msg("Flags="+to_string(fi->flags ));	
	//log_msg("Flags="+to_string(fi->flags & 33792));

	if(table.count(string(path))==1)
	{
		if ((fi->flags & O_APPEND)==O_APPEND)
			table[string(path)].data+=string(buf);
		else
			table[string(path)].data=string(buf);
		log_msg("Writing "+string(buf)+"to "+string(path)+"\n");	
	}
	return size;

}

int HelloFS::create(const char *path, mode_t mode, struct fuse_file_info *fi)
{
	//log_msg("Running create\n");
	//string s(path);
	//addTable(s);
	string s(path);
	addTable(s,0);
	return 0;
}
int HelloFS::unlink (const char *path){
	//log_msg("Running unlink\n");
	rmTable(string(path));
	return 0;
}
int HelloFS::mkdir (const char *path, mode_t mode){
	//log_msg("Running mkdir\n");
	string s(path);
	addTable(s,1);
	return 0;
}
int HelloFS::rmdir (const char *path){
	//log_msg("Running rmdir\n");
	rmfTable(string(path));
	return 0;
}