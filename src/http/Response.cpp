// Response.cpp

# include "core.hpp"

void	Server::response( int live_sock ) {
		std::cout << "Client Socket: " << live_sock << std::endl;

	const char body[] =
	"<!DOCTYPE html>"
	"<html><head><title>HELLO WORLD</title></head>"
	"<body><h1>HELLO WORLD</h1>"
	"<p>Port 80.</p></body></html>";
	
	char response[512];
	snprintf(response, sizeof(response),
	"HTTP/1.0 200 OK\r\n"
	"Server: Webserv\r\n"
	"Content-Type: text/html\r\n"
	"Content-Length: %zu\r\n"
	"Connection: close\r\n"
	"\r\n"
	"%s",
	sizeof(body), body);
	
	int		len = sizeof(response);
	while ( len > 0 )
		len -= send(live_sock, response, sizeof(response), MSG_NOSIGNAL);

	epoll_ctl(epollfd, EPOLL_CTL_DEL, live_sock, NULL);
	close(live_sock);
}
