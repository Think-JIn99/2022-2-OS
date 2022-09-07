#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char user_id[16][32];
char pass[16][32];
char *argv[] = { "sh", 0 };


void get_user_list(int fd){
	char info[64];
	int read_bytes; 
	int i = 0;
	int letter_loc = 0;
	int is_pass = 0;
	while ((read_bytes = read(fd, info, 64)) > 0){
        for(int j = 0; j < read_bytes; j++){
            if (info[j] == ' '){
				letter_loc = 0;
				is_pass = 1; 
                continue;
            }
		
			if (info[j] == '\n'){
				i++;
				is_pass = 0;
				letter_loc = 0;
				continue;
			}
			
			if (is_pass) pass[i][letter_loc++] = info[j];
			else user_id[i][letter_loc++] =  info[j];
		}
	}
}


int login(char *u, char *p){
	int is_login = 0;
	for (int i = 0; i < 16; i++){
		if (!strcmp(u, user_id[i]) && !strcmp(p, pass[i])){
			is_login = 1;
			break;
		}
	} 
	return is_login;
}


int main(){
	int count = 0;
	int fd = open("list.txt", O_RDONLY);
	get_user_list(fd);
	printf(1, "Username: ");
    char *user = (char *)malloc(32);
    user = gets(user, 32);
	switch(user[strlen(user) - 1]) {
		case '\n': case '\r':
			user[strlen(user) - 1] = 0;
		}
        
	printf(1, "Password :  ");
	char *pass = (char *)malloc(32);
	pass = gets(pass , 32);
	switch(pass[strlen(pass) - 1]) {
		case '\n': case '\r':
			pass[strlen(pass) - 1] = 0;
        }

	int is_login = login(user, pass);
	if (is_login) {
		printf(1, "Logged in %s \n", user);
		exec("sh", argv);
		exit();
	}
	else {
		  printf(1, "Not correct id or pass\n");
		  count++;
	}
	close(fd);
	exit();
}
