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
    char buf[256];
shandhake:
    from_client = server_handshake( &to_client );
lup:
    read(from_client,buf,256);
    puts("read input");`
    char ducducgoo = 0, spacel = 0, duck[] = "duck", goose[] = "goose";
    for(int i = 0;buf[i];i++){
        if(buf[i]==' ')
            spacel = 0, ducducgoo = (++ducducgoo)%3;
        else{
            if(ducducgoo!=2) buf[i]=duck[spacel%4];
            else buf[i]=goose[spacel%5];
            spacel++;
        }
    }
    int status = write(to_client,buf,256);
    if(status) goto lup;
    close(to_client);
    close(from_client);
    if(access("Gandalf", F_OK ) != -1 ) goto shandhake;
}
