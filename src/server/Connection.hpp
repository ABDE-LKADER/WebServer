#ifndef CONNECTION_HPP
# define CONNECTION_HPP

# include "core.hpp"
# include "Request.hpp"

enum state_e { READING_HEADERS, READING_BODY,
				READY_TO_WRITE, WRITING, CLOSING };

class Connection
{
	public:
		Connection( void );
		~Connection( void );

		Connection( int );

		int				getSoc( void );
		int				getCode( void );
		state_e			getState( void );

		void			setCode( int );
		void			setState( state_e );

		void			requestProssessing( void );
		void			buildResponseMinimal( void );		// for test response

	private:
		int				soc;
		int				code;
		state_e			state;

		std::string		recv;
		std::string		send;

		Request			request;
};

#endif
