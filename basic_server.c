#include "pipe_networking.h"
#include "signal.h"

void sighandler(int signo){
    switch(signo){
        case SIGINT:
            remove("Gandalf");        
            break;        
    }
}

int main() {

    int to_client;
    int from_client;
    signal(SIGINT,sighandler);
    mkfifo("Gandalf",0644);
shandhake:
    from_client = server_handshake( &to_client );
    char buf[256];
lup:
    read(from_client,buf,256);
    char ducducgoo = 0;
    char spacel = 0;
    char duck[] = "duck";
    char goose[] = "goose";
    for(int i = 0;buf[i];i++){
        if(buf[i]==' '){
            spacel = 0, ducducgoo = (ducducgoo+1)%3;
        }
        else{
            spacel++;
            if(ducducgoo!=2) buf[i]=duck[spacel%4];
            else buf[i]=goose[spacel%5];
        }
    }
    int status = write(to_client,buf,256);
    if(status) goto lup;
    if(access("Gandalf", F_OK ) != -1 ) goto shandhake;
}
