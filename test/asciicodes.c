//Prints ASCII-numbers and characters from 0 to 127

#include <stdio.h>

int main(){
	for(int i = 0; i<=127;i++){
		printf("#%3d %c\n",i,i);
	}
}