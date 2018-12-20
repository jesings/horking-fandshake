#include "pipe_networking.h"


int main() {

    int to_server;
    int from_server;

    from_server = client_handshake( &to_server );
    char buf[256];
loop:
    printf("Please pass your client input: ");
    fflush(stdout);
    fgets(buf,256,stdin);
    write(to_server,buf,256);
    read(from_server,buf,256);
    printf("%d\n",retstat);
    puts(buf);
    goto loop;//ha I use goto statements because people hate them don't @ me I do this for my own amusement

}
