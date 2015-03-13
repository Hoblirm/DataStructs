e#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <shared_array>

int main(int argc, char** argv) {

	//Print immediatly.
	setbuf(stdout,NULL);

	shared_array<int> sh_ary;

        switch(argc)
        {
        case 0:
        {
	printf("Creating shared array of size 3...");
	sh_ary.create("/tmp/sh_ary.bin",3);
	printf("Done!\n");
	
	for (int i=0;i<3;i++)
	{
		printf("  Sleeping 3 seconds...");
		usleep(3000000);
		printf("Done!\n");

		printf("Locking mutex...");
		sh_ary.lock();
		printf("Done!\n");

		printf("  Writing value %d...",i+1);
		sh_ary[i] = i+1;
		printf("Done!\n");

		printf("  Unlocking mutex...");
		sh_ary.unlock();
		printf("Done!\n");
    
	}
        break;
        }
        default:
        {
printf("Openning shared arry...");
	sh_ary.open("/tmp/sh_ary.bin",3);
	printf("Done!\n");

    for (int i=0; i<10; i++)
	{
	  printf("Locking shared array...");
	  sh_ary.lock();
	  printf("Done!\n");

	  for (int j=0; j<3; j++)
	  {
		  printf("  ary[%d] = %d\n",j,sh_ary[j]);
	  }

	  printf("  Unlocking shared array...");
	  sh_ary.unlock();
	  printf("Done!\n");

	  printf("  Sleeping one second...");
	  usleep(1000000);
	  printf("Done!\n\n");
    }
          break;
        }
        }
	return 0;
}

