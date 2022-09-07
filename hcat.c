#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];
int line_count = 0;

void
cat(int fd, int line_limit)
{
	int n;
	int j;
	while(((n = read(fd, buf, sizeof(buf))) > 0) && (line_count < line_limit)){ 
		for(j = 0; j < sizeof(buf); j++){
			if ((buf[j] == '\n') || (buf[j] == '\r')){
				line_count++;
			}
			if(line_count >= line_limit){
				break;
			}
		}
		if(write(1, buf, j) != j){
          	printf(1, "cat: write error\n");
			exit();
		} 
	
		if(n < 0){
			printf(1, "cat: read error\n");
			exit();
		}
	}
}

int
main(int argc, char *argv[])
{
  int fd, i;
  if(argc <= 1){
    cat(0, 0);
    exit();
  }
  int line_limit = atoi(argv[argc - 1]); 
  for(i = 1; i < argc - 1; i++){
    if((fd = open(argv[i], 0)) < 0){
      printf(1, "cat: cannot open %s\n", argv[i]);
      exit();
    }
    cat(fd, line_limit);
    close(fd);
  }
  exit();
}
