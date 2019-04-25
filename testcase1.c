// #include "types.h"
// #include "stat.h"
// #include "user.h"
// #include "fcntl.h"

// // #define MSGSIZE 8

// int main(void)
// {	
// 	create_container(1);
// 	create_container(2);
// 	create_container(3);

// 	int cid = fork();
// 	if(cid==0){
// 		join_container(1);
// 		open("a.txt", O_CREATE);
// 		// ls();
// 		leave_container();
// 		exit();
// 	}
// 	else{
// 		join_container(2);
// 		int fd = open("b.txt", O_CREATE|O_WRONLY);
// 		char *buff = "hello";
// 		write(fd, buff, sizeof(char)*5 );
// 		// close(i);
// 		// open("b.txt", O_WRONLY);
// 		// printf(1, "jd\n");
// 		leave_container();
// 		exit();
// 	}	
	



	
// 	// while(1){
		
// 	// }
// }
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

// #define MSGSIZE 8

int main(void)
{	
	create_container(1);
	create_container(2);
	create_container(3);
	// scheduler_log_on();
	// join_container(1);
	
	// printf(1,"%s\n","IPC Test case");
	// int cid = fork()
	// for(int j = 0; j<3; j++){
	// int i1 = -1;
	// int i2 = -1;
	// int i3 = -1;
	int cid = fork();
	if(cid==0){
		// This is child
		join_container(1);

		int cid2 = fork();
		if (cid2 == 0) {
			join_container(1);
			// i2 = 1;
			printf(1,"2 joined\n");
			// while(1) {}

			int cid3 = fork();
			if (cid3 == 0) {
				printf(1,"3 joined\n");
				join_container(1);
				// i3 = 1;
				// while( (i1+i2+i3) != 3 ) { }
				// printf(1, "SAT");
				ps();

			}
		}
		
	}
	else{
		int cid_c2 = fork();
		if (cid_c2 == 0) {
			join_container(2);
			ps();
		}
		else {
			int cid_c3 = fork();
			if (cid_c3 == 0) {
				join_container(3);
				ps();
			}
			else {
				// printf(1,"parent pid is %d\n",getpid() );
				// ps();
				// scheduler_log_on();
				// sleep(2);
				// scheduler_log_off();	
				// ls()








			}

		}
	
	}	
	







	// }
	// int a = 0;
	// // int b;
	// if(cid!=0){
	// 	for(int i = 0; i<10000000; i++){
	// 		a = a+1;
	// 	}		
	// }
	// ps();
	// printf(1,"here\n");

	// // leave_container();
	// // join_container(3);

	// if(cid==0){
	// 	exit();
	// }

	// // destroy_container(1);
	// // destroy_container(2);
	// // destroy_container(3);
	
	while(1){
		
	}
}
