#ifndef SERVER_HPP
# define SERVER_HPP

# include "core.hpp"
# include "Listener.hpp"

typedef struct epoll_event event_t;

class ServerConfig;

class Server
{
	public:
		Server( std::vector<ServerConfig> &servers );
		~Server( void );
		
		void				run( void );

	private:
		void				create_epoll( void );
		void				socket_control( int , int , int );

		void				response( int );	// for test response

		int					epollfd;				// Epoll file descriptor
		std::vector<int>	listeners;
};

#endif
