#include "kernel/types.h"
#include "kernel/sockets.h"

socket* create_socket();
void close_socket(socket* s);
void connect(socket *s, uint32_t destination, uint16_t port);
bool isconnected(socket* s);
void resolveDNS(char* host);
uint32_t atoip(char* addr);
void iptoa(uint32_t addr, char* buf);
