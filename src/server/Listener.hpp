#ifndef LISTENER_HPP
# define LISTENER_HPP

# include "core.hpp"

typedef struct addrinfo addrinfo_t;

class Listener
{
	public:
		Listener( const std::string & , const std::string & );
		~Listener( void );

		void					addrinfo_init( void );
		void					open_listener( void );

		int						getFd( void );

	protected:
		static void				socket_init(void);

	private:
		std::string				ip;
		std::string				port;
		int						listen_soc;

		addrinfo_t				*res;
		static addrinfo_t		hints;
};

#endif
