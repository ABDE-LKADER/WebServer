#ifndef CONNECTION_HPP
# define CONNECTION_HPP

# include "core.hpp"
# include "Buffer.hpp"

enum state_e { READING_HEADERS, READING_BODY,
				READY_TO_WRITE, WRITING, CLOSING };

class Connection
{
	public:
		Connection( int );
		~Connection( void );

		int			getCode( void );
		state_e		getState( void );

		void		setCode( int );
		void		setState( state_e );

	private:
		int			soc;
		int			code;
		state_e		state;
		Buffer		sending;
		Buffer		receiving;
		size_t		write_pos;
		bool		peer_half_closed;
		bool		want_close;
};

#endif
