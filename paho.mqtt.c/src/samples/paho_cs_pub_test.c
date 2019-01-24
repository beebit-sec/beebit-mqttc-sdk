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

volatile int toStop = 0;
void usage(void)
{
	printf("  --size 1KB \n");
	exit(EXIT_FAILURE);
}
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
	char* delimiter;
	int maxdatalen;
	int qos;
	int retained;
	char* username;
	char* password;
	char* host;
	char* port;
  int verbose;
} opts =
{
	"publisher", "\n", 10241, 0, 0, NULL, NULL, "iot.eclipse.org", "1883", 0
};
char* buffer = NULL;
int data_len=0;

int messageArrived(void* context, char* topicName, int topicLen, MQTTClient_message* m)
{
	/* not expecting any messages */
	return 1;
}
void getopts(int argc, char** argv);
int main(int argc, char** argv)
{
  MQTTClient client;
  MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
  MQTTClient_SSLOptions ssl_opts = MQTTClient_SSLOptions_initializer;
  BeebitOptions beebitOpts = BeebitOptions_initializer;
  BeebitCPABEOptions cpabeOpts = BeebitCPABEOptions_initializer;
  buffer = malloc(opts.maxdatalen);
	char* topic ="abc1234";
  
  int rc = 0;
	int subrc=0;
  char url[100];
if(argc<2){
 usage();
}

getopts(argc, argv);
	sprintf(url, "%s:%s", opts.host, opts.port);

	if (opts.verbose){printf("URL is %s\n", url);}

	printf("Using topic %s\n", topic);
  rc = MQTTClient_create(&client, url, opts.clientid, MQTTCLIENT_PERSISTENCE_NONE, NULL);

  signal(SIGINT, cfinish);
  signal(SIGTERM, cfinish);
  //pub setting
  rc = MQTTClient_setCallbacks(client, NULL, NULL, messageArrived, NULL);
  conn_opts.keepAliveInterval = 10;
  conn_opts.reliable = 0;
  conn_opts.cleansession = 1;
  conn_opts.username = opts.username;
  conn_opts.password = opts.password;
  ssl_opts.enableServerCertAuth = 0;
  beebitOpts.security = AC_CPABE;
  cpabeOpts.pk = "/home/jackie/Desktop/pubKey";
  cpabeOpts.ap = "role <= 2";
  //beebit.secKey="~/Desktop/secKey_ok";
  conn_opts.ssl = &ssl_opts;
  beebitOpts.opts = &cpabeOpts;
  conn_opts.beebit = &beebitOpts;
  //enc pub setting
  myconnect(&client, &conn_opts,"pub"); 
	
  struct timeval tv; 
  gettimeofday(&tv,NULL);
  printf("millisecond %ld \n",tv.tv_sec*1000 + tv.tv_usec/1000);
  	
  for(int i=0;i<=1;i++){
  rc = MQTTClient_publish(client, topic, data_len, buffer, opts.qos, opts.retained, NULL);
       
  if (rc != 0)
    {
      	myconnect(&client, &conn_opts,"pub");
      	rc = MQTTClient_publish(client, topic, data_len, buffer, opts.qos, opts.retained, NULL);
    }
}
  free(buffer);

  MQTTClient_disconnect(client, 0);
  MQTTClient_destroy(&client);
  return EXIT_SUCCESS;
}

void getopts(int argc,char** argv){
int count=1;
while (count<argc) {
	printf("%d\n",argc);
	if(strcmp(argv[count],"--size")==0){
		if (++count < argc){
			if (strcmp(argv[count], "1KB") == 0)
			for(int i=0;i<=10240;i++){
			buffer[data_len++]='A';
			}
			
			else
				{
				usage();}
		}
	}else
		{
		
		usage();}
count++;
}
	
}
