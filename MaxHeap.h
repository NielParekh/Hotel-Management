#define MAX_LENGTH 20

typedef Customer Data;

typedef struct PriorityQueue{
	int capacity;
	int size;
	Data* arr;
}PriorityQueue;

typedef PriorityQueue* PQueue;

int isFull(PQueue Q){
	return Q -> size == Q -> capacity;
}

int isEmpty(PQueue Q){
	return Q -> size == 0;
}


PQueue createPQueue(){
	PQueue tmp = (PQueue)malloc(sizeof(PriorityQueue));

	tmp -> capacity = MAX_LENGTH;
	tmp -> size = 0;
	tmp -> arr = (Data*)malloc(sizeof(Data) * MAX_LENGTH);

	tmp -> arr[0].visit_no  = 999999;
	return tmp;
}

void enqueue(PQueue q,const Data d){
	if(isFull(q)){
		printf("Queue Full!\n");
		return;
	}

	int i = ++q -> size;
	for(; q -> arr[i/2].visit_no < d.visit_no ; i /= 2)
		q -> arr[i] = q -> arr[i/2];

	q -> arr[i] = d;

}

Data dequeue(PQueue q){
	if(isEmpty(q)){
		printf("Queue Empty!\n");
		return q -> arr[0];
	}
	int i,child;
	Data min,last;

	min = q -> arr[1];
	last = q -> arr[q -> size--];

	for(i = 1; i * 2 <= q -> size ; i = child){
		child = i * 2;

		if(child != q -> size && q -> arr[child + 1].visit_no > q -> arr[child].visit_no)
			child ++;
		if(last.visit_no < q -> arr[child].visit_no)
			q -> arr[i] = q -> arr[child];
		else
			break;
	}

	q -> arr[i] = last;
	return min;
}

void display(PQueue Q){
	for(int i = 1 ; i <= Q -> size ; i++)
		putCustomer(Q -> arr[i]);
}

//void handleReservations(PQueue Q){
void handleReservations(PQueue Q,AVLTree t){
	int opt;
	if(isEmpty(Q)){
		printf("No Reservations!\n");
		return;
	}

	printf("Customers in queue: \n");
	display(Q);
	Customer c;
	int * arr = getRoomNo(t);

	if(arr == NULL){
		printf("No Rooms Vacant!\n");
		return;
	}
	FILE * f2,* f1 = fopen("Customer.dat","rb+");


	printf("Do you want to allocate rooms to all possible customers? 1/0 ");
	scanf("%d",&opt);
	getchar();

	//Room tmp;
	Room * tmp = 0;
	if(opt == 1){
		for(int i = 0 ; arr[i] && !isEmpty(Q) ; i++){
			c = dequeue(Q);
			c.r = * ((Room*)(Book_Room(t)));

			//c.r = Book_Room();

			c.r.cust_id = c.id;
			//f2 = fopen("Rooms.dat","wb");
			//fseek(f2,(c.r.rno - 1) * sizeof(Room),0);
			//fwrite(&(c.r),1,sizeof(Room),f2);
			//fclose(f2);

			fseek(f1,(c.id - 1) * sizeof(Customer),0);
			fwrite(&c,1,sizeof(Customer),f1);
		}
		if(!isEmpty(Q)){
			printf("Customers left:\n");
			display(Q);
		}
		else
			printf("All customers alloted rooms!\n");
	}

	fclose(f1);
}


void CheckIn(PQueue q,AVLTree t){

	int opt;
	int cust_id;
	Customer *Cptr = (Customer*)malloc(sizeof(Customer));
	CreateCustomer(Cptr);
	FILE * fp = fopen("Customer.dat","rb");


	if(!getRoomNo(t)){
		printf("No rooms available!!\n");
		printf("Do you want to reserve a room? 1/0 ");
		scanf("%d",&opt);
		getchar();

		if(opt == 1){
			do{
				printf("Existing customer? 1/0 ");
				scanf("%d",&opt);
				getchar();

				if(opt != 1 && opt != 0)
					printf("Invalid Input!\n");

			}while(opt != 0 && opt != 1);

			if(opt == 1){
				printf("Enter the customer ID: ");
				scanf("%d",&cust_id);
				getchar();

				fseek(fp,(cust_id - 1)*sizeof(Customer),0);
				fread(Cptr,1,sizeof(Customer),fp);
				if(feof(fp)){
					printf("Invalid Input!\n");
					fclose(fp);
					return;
				}
				fclose(fp);

				putCustomer(*Cptr);
				CreateRoom(&(Cptr->r));
				do{
					printf("Confirm details 1/0");
					scanf("%d",&opt);
					getchar();

					if(opt != 0 && opt != 1)
						printf("Invalid Input!\n");

				}while(opt != 0 && opt != 1);

				if(opt == 1){
					enqueue(q,(*Cptr));
					printf("Added to Queue!\n");
				}
			}
			else{
				fseek(fp,0,2);
				const int last_id = ftell(fp)/sizeof(Customer);
				fclose(fp);
				Cptr -> id = last_id + 1;
				Cptr -> visit_no = 0;
				printf("Your unique customer id is: %d\n",Cptr -> id);

				printf("Enter your name: ");
				scanf("%[^\n]*c",Cptr->name);
				getchar();

				do{
					printf("Enter contact number: ");
					scanf("%s",Cptr->ph);
					getchar();

					if(strlen(Cptr->ph) != 10)
						printf("Invalid Contact Number!Try again!");

				}while(strlen(Cptr->ph) != 10);

				CreateRoom(&(Cptr -> r));
				fp = fopen("Customer.dat","ab");
				fwrite(Cptr,1,sizeof(Customer),fp);
				fclose(fp);
				enqueue(q,(*Cptr));
			}
		}
		return;
	}

















	do{
		printf("Existing customer? 1/0 ");
		scanf("%d",&opt);
		getchar();

		if(opt != 1 && opt != 0)
			printf("Invalid Input!\n");

	}while(opt != 0 && opt != 1);

	if(opt == 1){
		printf("Enter the customer ID: ");
		scanf("%d",&cust_id);
		getchar();

		fseek(fp,(cust_id - 1)*sizeof(Customer),0);
		fread(Cptr,1,sizeof(Customer),fp);

		if(feof(fp)){
			printf("Invalid Input!\n");
			fclose(fp);
			return;
		}

		fclose(fp);
		putCustomer(*Cptr);

		do{
			printf("Confirm details 1/0 ");
			scanf("%d",&opt);
			getchar();

			if(opt != 0 && opt != 1)
				printf("Invalid Input!\n");

		}while(opt != 0 && opt != 1);


        Room * tmp = Book_Room(t);
        tmp -> cust_id = cust_id;
        Cptr -> r = (*tmp);

		fp = fopen("Customer.dat","rb+");
		fseek(fp,(cust_id - 1) * sizeof(Customer),0);
		fwrite(Cptr,1,sizeof(Customer),fp);
		fclose(fp);
		}

	else{
		fseek(fp,0,2);
		const int last_id = ftell(fp)/sizeof(Customer);
		fclose(fp);
		Cptr -> id = last_id + 1;
		Cptr -> visit_no = 1;
		printf("Your unique customer id is: %d\n",Cptr -> id);

		printf("Enter your name: ");
		scanf("%[^\n]*c",Cptr->name);
		getchar();

		do{
			printf("Enter contact number: ");
			scanf("%s",Cptr->ph);
			getchar();

			if(strlen(Cptr->ph) != 10)
				printf("Invalid Contact Number!Try again!");

		}while(strlen(Cptr->ph) != 10);

		Room * tmp = Book_Room(t);
		tmp -> cust_id = Cptr -> id;
		Cptr -> r = *tmp;

		//Cptr -> r.cust_id = Cptr -> id;

		fp = fopen("Customer.dat","ab");
		fwrite(Cptr,1,sizeof(Customer),fp);
		fclose(fp);

	}

    /*
	fp = fopen("Rooms.dat","rb+");
	fseek(fp,((Cptr->r).rno - 1)*sizeof(Room),0);
	fwrite(&(Cptr->r),1,sizeof(Room),fp);
	fclose(fp);
    */

	free(Cptr);
	printf("Successfully booked room!\n");

}
