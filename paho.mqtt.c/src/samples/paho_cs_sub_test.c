#include "MQTTClient.h"
#include "MQTTClientPersistence.h"

#include <stdio.h>
#include <signal.h>
#include <memory.h>
#include <stdlib.h>

#if defined(WIN32)
#define sleep Sleep
#else
#include <sys/time.h>
#endif

//bee
#include "../beebit.h"
#include "../beebit_cpabe.h"

volatile int toStop = 0;

void myconnect(MQTTClient* client, MQTTClient_connectOptions* opts,char* mod)
{
	printf("Connecting\n");

	if (MQTTClient_connect(*client, opts) != 0)
	{
		printf("Failed to connect\n");
		exit(EXIT_FAILURE);
	}
	printf("%s Connected\n", mod);
}

void cfinish(int sig)
{
	signal(SIGINT, NULL);
	toStop = 1;
}



struct 
{
	char* clientid;
	int nodelimiter;
	char* delimiter;
	int qos;
	char* username;
	char* password;
	char* host;
	char* port;
	int showtopics;
	int keepalive;
} subopts =

{
	"stdout-subscriber123", 0, "\n", 2, NULL, NULL, "iot.eclipse.org", "1883", 0, 15
};





int main(int argc, char** argv)
{

  MQTTClient subclient;
  MQTTClient_connectOptions subconn_opts = MQTTClient_connectOptions_initializer;
  BeebitOptions beebitOpts = BeebitOptions_initializer;
  BeebitCPABEOptions cpabeOpts = BeebitCPABEOptions_initializer;
	char* topic ="abc1234";
  char* buffer = NULL;

	int subrc=0;
  char url[100];


	sprintf(url, "%s:%s", subopts.host, subopts.port);
	

	printf("Using topic %s\n", topic);
	  subrc= MQTTClient_create(&subclient, url, subopts.clientid, MQTTCLIENT_PERSISTENCE_NONE, NULL);

  signal(SIGINT, cfinish);
  signal(SIGTERM, cfinish);
	//pub settin
  subconn_opts.keepAliveInterval = subopts.keepalive;
	subconn_opts.reliable = 0;
	subconn_opts.cleansession = 1;
	subconn_opts.username = subopts.username;
	subconn_opts.password = subopts.password;
	beebitOpts.security = AC_CPABE;
 	cpabeOpts.pk = "/home/jackie/Desktop/pubKey";
	cpabeOpts.ap = "role <= 2";
 	cpabeOpts.sk = "/home/jackie/Desktop/secKey_ok";
	beebitOpts.opts = &cpabeOpts;
 	subconn_opts.beebit = &beebitOpts;
  myconnect(&subclient, &subconn_opts,"sub");
  
  subrc= MQTTClient_subscribe(subclient, topic, subopts.qos);
	
	
 while(!toStop)
 {
	char* topicName = NULL;
	int topicLen;
	MQTTClient_message* message = NULL;
	subrc  = MQTTClient_receive(subclient, &topicName, &topicLen, &message, 1000);
 
	if (message)
	 {
	
		 if (subopts.showtopics)
			 printf("%s\t", topicName);
		 if (subopts.nodelimiter)
			 printf("%.*s", message->payloadlen, (char*)message->payload);
		 else
			 printf("%.*s%s", message->payloadlen, (char*)message->payload, subopts.delimiter);
		 fflush(stdout);
		 MQTTClient_freeMessage(&message);
		 MQTTClient_free(topicName);
	 }
 
 if(subrc!=0)
 {
	 myconnect(&subclient, &subconn_opts,"sub");
 }

 }
  free(buffer);


  MQTTClient_disconnect(subclient, 0);

  MQTTClient_destroy(&subclient);
  return EXIT_SUCCESS;
}
