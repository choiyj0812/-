#include <stdio.h>

unsigned char block_l[4][4] = {
  {0,0,0,0},
  {0,1,0,0},
  {0,1,1,1},
  {0,0,0,0},
};

void main(){
  int i = 0, j = 0;
  for(i=0;i<4;i++){
	for(j=0;j<4;j++){
	  if(block_l[i][j]){
		printf("*");
	  }
	  else{
		printf("-");
	  }
	}
	printf("\n");
  }
}
