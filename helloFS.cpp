// Hello filesystem class implementation

#include "helloFS.h"

#include <iostream>
#include "structures.h"
#include <stdio.h>
#include <string>
// include in one .cpp file
#include "Fuse-impl.h"

static const char *hello_str = "Hello World!\n";
static const char *hello_path = "/hello";

int HelloFS::getattr(const char *path, struct stat *stbuf)
{
	
	int res = 0;

	memset(stbuf, 0, sizeof(struct stat));
	if (strcmp(path, "/") == 0) {
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;
	} else if (strcmp(path, hello_path) == 0) {
		stbuf->st_mode = S_IFREG | 0444;
		stbuf->st_nlink = 1;
		stbuf->st_size = strlen(hello_str);
	} 
	else if (strcmp(path, "a") == 0) {
		stbuf->st_mode = S_IFREG | 0444;
		stbuf->st_nlink = 1;
		stbuf->st_size = strlen("lol");
	} 
	
	return 0;
}

int HelloFS::readdir(const char *path, void *buf, fuse_fill_dir_t filler,
			               off_t, struct fuse_file_info *)
{
	if (strcmp(path, "/") != 0)
		return -ENOENT;

	filler(buf, ".", NULL, 0);
	filler(buf, "..", NULL, 0);
	
	return 0;
}


int HelloFS::open(const char *path, struct fuse_file_info *fi)
{
	//if (strcmp(path, hello_path) != 0)
	//	return -ENOENT;
	if ((fi->flags & 256) == O_CREAT)
	{
		//add to table
		string s(path);
		addTable(s);
	}
	
	return 0;

}


int HelloFS::read(const char *path, char *buf, size_t size, off_t offset,
		              struct fuse_file_info *fi)
{
	size_t len;
	(void) fi;
	if(strcmp(path, hello_path) != 0)
		return -ENOENT;

	len = strlen(hello_str);
	if ((size_t)offset < len) {
		if (offset + size > len)
			size = len - offset;
		memcpy(buf, hello_str + offset, size);
	} else
		size = 0;

	return size;
}

int HelloFS::mknod(const char *pathname, mode_t mode, dev_t dev)
{
	return 0;
}
int HelloFS::statfs(const char *path, struct statvfs *buf)
{
	return 0;
}
int HelloFS::create(const char *path, mode_t mode, struct fuse_file_info *fi)
{
	return 0;
}
int HelloFS::fgetattr(const char *path, struct stat *buf,
                            struct fuse_file_info *fi)
{
	return 0;
}