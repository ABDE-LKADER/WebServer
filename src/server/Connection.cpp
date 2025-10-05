# include "Connection.hpp"

Connection::Connection( int conn_sock )
		: soc(conn_sock), state(READING_HEADERS) { }

Connection::~Connection( void ) { }

int	Connection::getCode( void ) { return code; }

state_e	Connection::getState( void ) { return state; }

void	Connection::setCode( int code ) { this->code = code; }

void	Connection::setState( state_e state ) { this->state = state; }
