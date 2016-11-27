// Hello filesystem class definition

#ifndef __HELLOFS_H_
#define __HELLOFS_H_

#include "Fuse.h"

#include "Fuse-impl.h"

class HelloFS : public Fusepp::Fuse<HelloFS>
{
public:
  HelloFS() {}

  ~HelloFS() {}

  static int getattr (const char *, struct stat *);

  static int readdir(const char *path, void *buf,
                     fuse_fill_dir_t filler,
                     off_t offset, struct fuse_file_info *fi);
  
  static int open(const char *path, struct fuse_file_info *fi);

  static int read(const char *path, char *buf, size_t size, off_t offset,
                  struct fuse_file_info *fi);
  static int write(const char *path,const char *buf, size_t size, off_t offset,
                  struct fuse_file_info *fi);
  //static int statfs(const char *path, struct statvfs *buf);
  //static int mknod(const char *pathname, mode_t mode, dev_t dev);
  static int create(const char *path, mode_t mode, struct fuse_file_info *fi);
  //static int fgetattr(const char *path, struct stat *buf,
   //                         struct fuse_file_info *fi);
  static int utime (const char *path, struct utimbuf * s);
  static int unlink (const char *path);
  static int mkdir (const char *path, mode_t mode);
  static int rmdir (const char *path);
};

#endif
