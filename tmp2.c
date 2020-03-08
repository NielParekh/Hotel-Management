#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "class_date.h"
#include "class_room.h"
#include "class_customer.h"
#include "class_login.h"

int main(){
	FILE * f = fopen("Customer.dat","rb");
	Customer c;
	fread(&c,1,sizeof(Customer),f);
	while(!feof(f)){
		putCustomer(c);
		fread(&c,1,sizeof(Customer),f);
	}
}