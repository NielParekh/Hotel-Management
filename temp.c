
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "Structures.h"
#include "class_date.h"
#include "class_room.h"
#include "class_customer.h"
#include "class_login.h"
#include "AVLTree.h"
#include "MaxHeap.h"


#define MAX_ROOMS 3
int main(){
	
	Room tmp;
	CreateRoom(&tmp);
	CreateDate(&(tmp.Check_In));
	CreateDate(&(tmp.Check_Out));
		
	FILE * f = fopen("Rooms.dat","wb");
	for(int i = 0 ; i < MAX_ROOMS ; i++){
		tmp.rno = i + 1;
		fwrite(&tmp,1,sizeof(Room),f);
	}
	fclose(f);
	
	AVLTree t = readFile();
	DisplayAvailableRooms(getRoomNo(t));
	printf("\n");
	
}
