//Address
struct sockaddr_in sin;
memset(&sin, 0, sizeof(sin));
sin.sin_family = AF_INET;
sin.sin_addr.s_addr = htons(INADDR_ANY);
sin.sin_port = htons(PORT);

//Create UDP socket
socketDescriptor = socket(PF_INET, SOCK_DGRAM,0);
bind(socketDescriptor, (struct sockaddr*) &sin, sizeof(sin));

while(1){
	//get data (blocking)
	//change address sent to client

	struct sockaddr_in sinRemote;
	unsigned int sin_len = sizeof(sinRemote);
	char messageRx[MSG_MAX_LEN];
	recvfrom(socketDescriptor, messageRx, MSG_MAX_LEN, 0, (struct sockaddr*)&sinRemote, &sin_len);

	//do something with the message
	printf("MESSAGE RECEIEVED! %s\n", messageRx);
}

printf("Done rx thread!");
return NULL;