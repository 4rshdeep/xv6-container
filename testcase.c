#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}
char*
fmtname2(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p) -2, ' ', DIRSIZ-strlen(p));
  return buf;
}

void
ls(char *path)
{ 
  // join_container(0);

  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    printf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    printf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }
  int cid;
  cid = get_cid();

  switch(st.type){
  case T_FILE:
    if ( accessibility(cid, st.ino)==1 ) {

      printf(1, "%s %d %d %d\n", fmtname(path), st.type, st.ino, st.size);
    }
    else {
      printf(1, "File not found\n");
    }
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf(1, "ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        // printf(1, "ls: cannot stat %s\n", buf);
        continue;
      }
      //   printf(1, "%s %d %d %d CID : %d\n", fmtname(buf), st.type, st.ino, st.size, cid);

      // if (st.cid == cid || st.cid == 0) {
      if ( accessibility(cid, st.ino)==1 ) {
        // printf(1, " i num of file %d\n", st.ino);
        if(find_source(cid, st.ino) == 1){
          //1 means mere write se bani
          printf(1, "%s %d %d %d CID : %d\n", fmtname2(buf), st.type, st.ino, st.size, cid);
        }
        else{
          printf(1, "%s %d %d %d CID : %d\n", fmtname(buf), st.type, st.ino, st.size, cid);
        }
        
      }
      else {
        printf(1, "Hiding %s %d %d %d CID : %d\n", fmtname(buf), st.type, st.ino, st.size, cid);
      }
    }
    break;
  }
  close(fd);
}

char buf[512];

void
cat(int fd)
{
  int n;

  while((n = read(fd, buf, sizeof(buf))) > 0) {
    if (write(1, buf, n) != n) {
      printf(1, "cat: write error\n");
      exit();
    }
  }
  if(n < 0){
    printf(1, "cat: read error\n");
    exit();
  }
}

int main(void)
{	
	create_container(1);
	create_container(2);
	create_container(3);

	int cid = fork();
	if(cid==0){
		join_container(1);
		open("a.txt", O_CREATE);
		// ls(".");
		leave_container();
		exit();
	}
	else{
		join_container(2);
		int fd = open("b.txt", O_CREATE|O_WRONLY);
		// ls(".");
		// cat(fd);
		char *buff = "hello";
		write(fd, buff, sizeof(char)*5 );
		// ls(".");
		leave_container();
		exit();
	}	
	
	while(1){
		
	}
}
