typedef struct ticket Ticket;
typedef struct enqueueTicket EnqueueTicket;
typedef struct serviceDesk ServiceDesk;
typedef struct listServiceDesk ListServiceDesk;

EnqueueTicket *createEnqueueTicket();
void generateTicket(EnqueueTicket *enqueueTicket, char *service, int priority);
void showTickets(EnqueueTicket *enqueueTicket);

ListServiceDesk *createListServiceDesk();
void newServiceDesk(ListServiceDesk *serviceDesks);
void showListServiceDesk(ListServiceDesk *serviceDesk);

void callTicket(ListServiceDesk *serviceDesks, EnqueueTicket *enqueueTicket);
