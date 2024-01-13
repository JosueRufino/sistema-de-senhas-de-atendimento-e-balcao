#include"structure.h"
#include<stdio.h>
#include<time.h>
#include<locale.h>

main(){
	setlocale(LC_ALL, "portuguese");
	
	EnqueueTicket *enqueueTicket = createEnqueueTicket();
	generateTicket(enqueueTicket, "josue", 0);
	generateTicket(enqueueTicket, "rufino", 0);
	generateTicket(enqueueTicket, "Wildbrand", 0);
	generateTicket(enqueueTicket, "Quintas", 1);
	generateTicket(enqueueTicket, "Wildbrand", 1);
	generateTicket(enqueueTicket, "Wildbrand", 0);
	generateTicket(enqueueTicket, "Wildbrand", 0);
	//generateTicket(enqueueTicket, "Wildbrand", 1);
	//generateTicket(enqueueTicket, "Wildbrand", 1);
	showTickets(enqueueTicket);
	
	ListServiceDesk *listServiceDesk = createListServiceDesk();
	newServiceDesk(listServiceDesk);
	newServiceDesk(listServiceDesk);
	int n = 1;
	do{
		scanf("%d", &n);	
		switch(n){
			case 1:
				callTicket(listServiceDesk, enqueueTicket);
				break;
			case 2:
				showListServiceDesk(listServiceDesk);
				break;	
		}
	
	}while(n != 0);
	
	
}
