#define RATE 3000.0

void putCustomer(const Customer C){
	printf("ID             : %d\n",C.id);
	printf("Name           : %s\n",C.name);
	printf("Phone Number   : %s\n",C.ph);
	printf("Visit Number   : %d\n",C.visit_no);

	if(C.r.rno != 0){
		printf("\nRoom Number   : %d\n",C.r.rno);
		putDate("Check In date ",C.r.Check_In);
		putDate("Check Out date",C.r.Check_Out);
		printf("\nCUST_ID: %d\n",C.r.cust_id);
	}

	printf("\n-------------------------------\n\n");

}

void CreateCustomer(Customer * const Cptr){//Constructor equivalent
	(*Cptr).name[0] = '\0';
	(*Cptr).ph[0] = '\0';
	Cptr -> id = 0;
	Cptr -> visit_no = 0;
	CreateRoom( &(Cptr->r) );
}
//float CheckOut(){

float CheckOut(AVLTree t){
	const Date CurrentDate = getCurrentDate();
	//FILE * fp = fopen("Rooms.dat","rb+");
	//Room *tmp = (Room*)malloc(sizeof(Room));
	Room * tmp;
	Customer *temp = (Customer*)malloc(sizeof(Customer));
	int rno,opt;

	do{
		do{
			printf("Enter the room number to vacate: ");
			scanf("%d",&rno);
			getchar();

			if(rno < 1 || rno > MAX_ROOMS)
				printf("Invalid Input!Try again!\n");

		}while(rno<1||rno>MAX_ROOMS);

		//fseek(fp,(rno-1)*sizeof(Room),0);
		//fread(tmp,1,sizeof(Room),fp);
        tmp = search(t,rno);

		if( (!tmp -> isOccupied) || (!tmp))
			printf("Invalid Room Number!Try again!\n");

	}while(!tmp -> isOccupied);
	//}while(!tmp -> isOccupied && !feof(fp));

	const int cust_id = tmp -> cust_id;

	do{
		printf("Are you sure you want to check out 1/0?: ");
		scanf("%d",&opt);
		getchar();

		if(!(opt == 1 || opt == 0))
			printf("Invalid Input!Try again\n");

	}while(!(opt==1||opt==0));

	if (opt == 0)
		return -1;

	CreateRoom(tmp);
	tmp->rno = rno;

	//fseek(fp,(rno - 1)*sizeof(Room),0);
	//fwrite(tmp,1,sizeof(Room),fp);
	//free(tmp);
	//fclose(fp);

	FILE * fp = fopen("Customer.dat","rb+");
	fseek(fp,(cust_id-1)*sizeof(Customer),0);
	fread(temp,1,sizeof(Customer),fp);
	temp -> visit_no++;
	putCustomer(*temp);
	Room r = temp -> r;
	CreateRoom(&(temp -> r));
	fseek(fp,(cust_id-1)*sizeof(Customer),0);
	//printf("%d\n",temp -> r.rno);
	fwrite(temp,1,sizeof(Customer),fp);
	fclose(fp);

	fp = fopen("RoomHistory.dat","ab");
	int date_diff1 = date_diff(r.Check_Out,r.Check_In);
	int date_diff2 = date_diff(CurrentDate,r.Check_In);

	if(date_diff2 < date_diff1)
		r.Check_Out = CurrentDate;

	fwrite(&r,1,sizeof(Room),fp);
	//printf("%d\n",r.rno);

	fclose(fp);

	int date_diff = (date_diff1>date_diff2)? date_diff2 : date_diff1;
	date_diff++;

	free(temp);
	printf("Successfully Checked out!");
	return date_diff * RATE;
}



void Room_History(){
	int rno;
	int cust_id;

	do{
		printf("Enter a room number: ");
		scanf("%d",&rno);
		getchar();

		if(rno<1||rno>MAX_ROOMS)
			printf("Invalid Input!Try again!\n");

	}while(rno<1||rno>100);

	FILE *f1 = fopen("RoomHistory.dat","rb"),
		 *f2 = fopen("Customer.dat","rb");

	Customer *tmp = (Customer*)malloc(sizeof(Customer));
	Room * r = (Room*)malloc(sizeof(Room));


	fread(r,1,sizeof(Room),f1);
	while(!feof(f1)){
		if(r -> rno == rno){
			cust_id = r -> cust_id;
			fseek(f2,(cust_id-1)*sizeof(Customer),0);
			fread(tmp,1,sizeof(Customer),f2);
			putCustomer( (*tmp) );
			putDate("Check In date ",r -> Check_In);
			putDate("Check Out date",r -> Check_Out);
			printf("\n\n----------------------------\n\n");
		}
		fread(r,1,sizeof(Room),f1);
	}

	fclose(f1);
	fclose(f2);
	free(r);
	free(tmp);
}

void Date_History(){
	Date tmp,d;
	int cust_id;

	CreateDate(&tmp);
	CreateDate(&d);
	getDate("required",&d,tmp);

	FILE * f1 = fopen("Customer.dat","rb"),
		 * f2 = fopen("RoomHistory.dat","rb");

	Customer *c = (Customer*)malloc(sizeof(Customer));
	Room *r = (Room*)malloc(sizeof(Room));

	fread(r,1,sizeof(Room),f2);
	while(!feof(f2)){
		if( (date_diff(r -> Check_In,d) <= 0) && (date_diff(r -> Check_Out,d) >= 0) ){
			cust_id = r -> cust_id;
			fseek(f1,(cust_id-1)*sizeof(Customer),0);
			fread(c,1,sizeof(Customer),f1);
			putCustomer( (*c) );
			putDate("Check In date ",r -> Check_In);
			putDate("Check Out date",r -> Check_Out);
			printf("\n\n----------------------------\n\n");
		}
		fread(r,1,sizeof(Room),f2);
	}

	fclose(f1);
	fclose(f2);
	free(r);
	free(c);
}
