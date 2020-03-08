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

int main(void){
	Room r;
	CreateRoom(&r);
	Customer arr[] = {{1,2,"Mahesh","9962243082",r},{2,0,"Niel","9898787898",r},
					  {3,0,"Sai Charan","8898970234",r}};
	FILE * f = fopen("Customer.dat","wb");
	for(int i = 0 ; i < 3 ; i++)
		fwrite(&(arr[i]),1,sizeof(Customer),f);

	fclose(f);	
}