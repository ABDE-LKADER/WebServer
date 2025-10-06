# include "Connection.hpp"

Connection::Connection( void ) : soc(-1), code(0),
		state(READING_HEADERS) { }

Connection::Connection( int conn_sock ) : soc(conn_sock), code(0),
		state(READING_HEADERS) { }

Connection::~Connection( void ) { }

int	Connection::getSoc( void ) { return soc; }

int	Connection::getCode( void ) { return code; }

state_e	Connection::getState( void ) { return state; }

void	Connection::setCode( int code ) { this->code = code; }

void	Connection::setState( state_e state ) { this->state = state; }

void			Connection::requestProssessing( void ) {
	;
}
