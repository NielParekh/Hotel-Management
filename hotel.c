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

void Pause(){
	printf("\nPress any key to continue.........\n");
	getchar();
}

void main(void){
    AVLTree t;
    //inorder(t);

    FILE * f_rooms;
	struct login x = {"","",0};
	int choice;
	FILE *id;
	char user[10],password[25];
	PQueue q = createPQueue();

	do{

		t  = readFile();
    
		//system("cls");
		system("clear");
		printf("\n 1. Administrator\n 2. Customer\n 3. Exit\n Enter your choice: ");
		scanf("%d",&choice);
		getchar();

		if(choice==1){

			if(!x.verified){
				printf(" Enter the username : ");
				scanf("%s",user);
				getchar();

				strcpy(password,getpass(" Enter the password: "));

				id=fopen("id.bin","rb");
				fread(&x,1,sizeof(x),id);
				fclose(id);

				if(strcmp(x.username,user)==0 && strcmp(x.pass,password)==0){
					printf("\n Access Granted\n");
					x.verified = 1;
					Pause();
				}
				else{
					printf("\n Wrong password or username\n");
					Pause();
					continue;
				}
			}

			do{
				//system("cls");
				system("clear");
				printf("\n 1. List of available rooms\n 2. Bill generator\n");
				printf(" 3. History of a room\n 4. Rooms to vacate today\n");
				printf(" 5. Date wise History\n 6. Reservations\n 7. Logout\n Enter your choice: ");
				scanf("%d",&choice);
				getchar();

				
				//system("cls");
				system("clear");
				float amount;
				switch(choice){
					case 1 : DisplayAvailableRooms(getRoomNo(t));   Pause(); break;
					case 2 : amount = CheckOut(t);
					         if(amount != -1){
					         	printf("\n Amount to be paid: %.2f\n",amount);
					         	f_rooms = fopen("Rooms.dat","wb");
								writeFile(t,f_rooms);
								fclose(f_rooms);
							}
					         	                                    Pause(); break;
					case 3 : Room_History();						Pause(); break;
					case 4 : getCheckOut();							Pause(); break;
					case 5 : Date_History();						Pause(); break;
					case 6 : handleReservations(q,t);	
							 f_rooms = fopen("Rooms.dat","wb");
							 writeFile(t,f_rooms);
					     	 fclose(f_rooms);

																	Pause(); break;
					case 7 : printf("\n Logged out successfully!\n");
							 x.verified = 0;						Pause(); break;

					default: printf("\n Invalid Input!Try again!\n");Pause(); break;
				}

			}while(choice!=7);
			choice  = -1;
		}



		else if(choice==2){

			
			//system("cls");
			system("clear");printf("WELCOME TO HOTEL CALIFORNIA \n");
			printf("\n 1. Check in\n 2. Check out\n 3. Check availabile rooms\n Enter your choice: ");
			scanf("%d",&choice);
			getchar();

			
			//system("cls");
			system("clear");
			switch(choice){
				case 1 : CheckIn(q,t);	
						 f_rooms = fopen("Rooms.dat","wb");
						 writeFile(t,f_rooms);
						 fclose(f_rooms);
															     Pause();  break;
				case 2 : printf(" Contact Admin!\n");  	  	     Pause();  break;
				case 3 : DisplayAvailableRooms(getRoomNo(t));    Pause();  break;
				default: printf("\n Invalid Input!Try again!\n");Pause();  break;
			}
			choice = -1;
		}

		else if(choice==3){
			printf("\n Exiting............................................\n");
		}
		else{
			printf("\n Please enter a valid option\nPress any key to continue\n");
			getchar();
		}
		/*
		f_rooms = fopen("Rooms.dat","wb");
		writeFile(t,f_rooms);
		fclose(f_rooms);
		*/

	}while(choice!=3);

}

