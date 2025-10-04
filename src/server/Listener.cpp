# include "Listener.hpp"

addrinfo_t	Listener::hints;

Listener::Listener( const std::string& ip, const std::string& port )
		: ip(ip), port(port), res(NULL) { }

int	Listener::getFd( void ) { return listen_soc; }

void	Listener::socket_init( void) {
	bzero(&hints, sizeof(addrinfo_t));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
}

void	Listener::addrinfo_init( void ) {
	int		er;
	if ((er = getaddrinfo(ip.c_str(), port.c_str(), &hints, &res)) != 0)
		throw std::runtime_error(std::string("getaddrinfo: ") + gai_strerror(er));
}

void	Listener::open_listener( void ) {
	int	enable  = 1;
	int	listen_sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	if (listen_sock == -1)
		throw std::runtime_error("<socket> " + std::string(strerror(errno)));

	setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
	fcntl(listen_sock, F_SETFL, O_NONBLOCK);

	if (bind(listen_sock, res->ai_addr, res->ai_addrlen) == -1)
		throw std::runtime_error("<bind> " + std::string(strerror(errno)));

	if (listen(listen_sock, SOMAXCONN) == -1)
		throw std::runtime_error("<Listen> " + std::string(strerror(errno)));
}

Listener::~Listener( void ) {
	if (res != NULL)
		freeaddrinfo(res);
}
