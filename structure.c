#include"structure.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdbool.h>

struct ticket{
	int numberTicket , numberPersonsWaiting, priority, time;
	char service[100], status[100];
	struct tm *dateCreation;
	struct ticket *next;
};

struct enqueueTicket{
	Ticket *begin;
	Ticket *end;
	int TotalTicket;
	int TotalTicketEnqueue;
};

struct serviceDesk{
	int numberServiceDesk, totalTicketsSucess;
	time_t serviceTime;
	bool status;
	Ticket *ticket;
	struct serviceDesk *next;
};

struct listServiceDesk{
	ServiceDesk *begin;
	ServiceDesk *end;
	int totalServiceDesks;
};


//Função para criar o sistema de senhas
EnqueueTicket *createEnqueueTicket(){
	EnqueueTicket *enqueueTicket = (EnqueueTicket*) calloc(1, sizeof(EnqueueTicket));
	
	if(!enqueueTicket){
		printf("Erro na alocação de memória\n");
		exit(1);
	}
	
	enqueueTicket->begin = enqueueTicket->end = NULL;	
	return enqueueTicket;
}

ListServiceDesk *createListServiceDesk(){
	ListServiceDesk *listServiceDesk = (ListServiceDesk*) calloc(1, sizeof(ListServiceDesk));
	
	if(!listServiceDesk){
		printf("Erro na alocação de memória\n");
		exit(1);
	}
	listServiceDesk->begin = NULL;
	listServiceDesk->totalServiceDesks = 0;
	
	return listServiceDesk;
}

void generateTicket(EnqueueTicket *enqueueTicket, char *service, int priority){
	Ticket *ticket = (Ticket*) malloc(sizeof(Ticket));
	if(!ticket){
		printf("Erro na alocação de memória\n");
		exit(1);	
	}
	
	time_t seconds;
	seconds = time(NULL);
	struct tm *dateOfCreation = localtime(&seconds);
	
	
	strcpy(ticket->service, service);
	strcpy(ticket->status, "Aguardando");
	ticket->priority = priority;
	ticket->numberPersonsWaiting = enqueueTicket->TotalTicketEnqueue;
	ticket->numberTicket = enqueueTicket->TotalTicket + 1;
	ticket->dateCreation = dateOfCreation;
	ticket->next = NULL;

	
	
	if(enqueueTicket->begin == NULL){
		enqueueTicket->begin = enqueueTicket->end = ticket;
	}else{
		if(ticket->priority){
			if(enqueueTicket->begin->priority){
				Ticket *aux = enqueueTicket->begin;
				while(aux != NULL && aux->next->priority  == 1){
					aux = aux->next;
				}
				if(aux != NULL){
					ticket->next = aux->next;
					aux->next = ticket;
				}
			}else{
				ticket->next = enqueueTicket->begin;
				enqueueTicket->begin = ticket;
			}
		}else{
			enqueueTicket->end->next = ticket;
			enqueueTicket->end = ticket;
		}
	}
	enqueueTicket->TotalTicket++;
	enqueueTicket->TotalTicketEnqueue++;
	ticket->numberPersonsWaiting = enqueueTicket->TotalTicketEnqueue - 1;
	
}

void newServiceDesk(ListServiceDesk *serviceDesks){
	ServiceDesk *service = (ServiceDesk*) calloc(1, sizeof(ServiceDesk));
	
	if(!service){
		printf("Erro na alocação de memória\n");
		exit(1);
	}
	service->numberServiceDesk = serviceDesks->totalServiceDesks + 1;
	service->totalTicketsSucess = 0;
	service->serviceTime = 0;
	service->status = true;
	service->ticket = NULL;
	service->next = NULL;
	
	if(serviceDesks->begin == NULL){
		serviceDesks->begin = service;
		serviceDesks->end = service;
	}else{
		serviceDesks->end->next = service;
	}
	serviceDesks->totalServiceDesks++;
	
}

void callTicket(ListServiceDesk *serviceDesks, EnqueueTicket *enqueueTicket){
	if(enqueueTicket->begin == NULL){
		printf("Sem senhas na fila");
		exit(1);
	}
	
	time_t  seconds, now;
	now = time(&seconds);
	
	ServiceDesk *serviceDesk = serviceDesks->begin;
	ServiceDesk *serviceDeskChose = NULL;
	Ticket *ticket = enqueueTicket->begin;
	while(serviceDesk != NULL){
		if(serviceDesk->status){
			serviceDeskChose = serviceDesk;
			break;
		}
		serviceDesk = serviceDesk->next;
	}
	
	if(serviceDeskChose != NULL){
		time_t now;
		time(&now);

		if(now >= serviceDeskChose->serviceTime + 10){
			printf("Balcão disponível: %d\n", serviceDeskChose->numberServiceDesk);
			serviceDeskChose->status = false;
			time(&serviceDeskChose->serviceTime);
		}
		//serviceDeskChose->status = true;
	}else{
		printf("Nenhum balcão disponível no momento...\n");
	}
	
}

void showTickets(EnqueueTicket *enqueueTicket){
	if(enqueueTicket->begin == NULL){
		printf("Sem senhas na fila\n");
	}else{
		Ticket *aux = enqueueTicket->begin;
		while(aux != NULL){
			printf("__________________________\n");
			printf("Senha nº %d\n", aux->numberTicket);
			printf("__________________________|\n");
			printf("Serviço: %s\n", aux->service);
			printf("Estado: %s\n", aux->status);
			if(aux->numberPersonsWaiting){
				if(aux->numberPersonsWaiting > 1)
					printf("%d pessoas na frente\n", aux->numberPersonsWaiting);
				else
					printf("%d pessoa na frente\n", aux->numberPersonsWaiting);
			}
			if(aux->priority){
				printf("Senha prioritária\n");
			}
			printf("Data: %d/%d/%d - %d:%d:%d\n", aux->dateCreation->tm_mday, aux->dateCreation->tm_mon + 1, 
												aux->dateCreation->tm_year + 1900, aux->dateCreation->tm_hour, 
												aux->dateCreation->tm_min, aux->dateCreation->tm_sec);
			printf("__________________________|\n\n\n");
			//printf("%d\n\n", aux->numberTicket);
			aux = aux->next;
		}
	}
}

void showListServiceDesk(ListServiceDesk *listServiceDesk){
	if(listServiceDesk->begin == NULL){
		printf("Balcões inexistentes\n");
	}else{
		ServiceDesk *aux = listServiceDesk->begin;
		while(aux != NULL){
			printf("_____________________________\n");
			printf("Balcão nº %d\n", aux->numberServiceDesk);
			printf("_____________________________|\n");
			if(aux->status){
				printf("Status: Disponível\n");
			}else{
				printf("Status: Ocupado\n");
			}
			printf("Atendimentos realizados: %d\n", aux->totalTicketsSucess);
			printf("_____________________________|\n\n\n");
			aux = aux->next;
		}	
	}
}
