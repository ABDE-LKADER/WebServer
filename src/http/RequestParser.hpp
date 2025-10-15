#ifndef REQUESTPARSER_HPP
# define REQUESTPARSER_HPP

# include <sstream>
# include <iostream>
# include <algorithm>
# include "Request.hpp"

class Request;

enum state_e { REQUEST_LINE, READING_HEADERS, READING_BODY,
				READY_TO_WRITE, WRITING, CLOSING, BAD };

class State {
	public:
		State( short co , state_e st )
				{ code = co; state = st; }

		short			code;
		state_e			state;
};

class RequestParser
{
	public:
		static State		requestLineParser( Request & );
		static State		headersParser( Request & );
		static State		bodyParser( Request & );

		static bool			isCTL( unsigned char c );
		static bool			isTspecials( unsigned char c );
		static bool			isValidMethod( const std::string & );
		
		static char			hexToChar( const std::string & );
		static bool			decodeValidator( std::string & , bool );
		
		static std::string	strToUpper( std::string );
		static std::string	removeDotSegment( std::string  );

		static bool			containsChar( char , const std::string & );
		static bool			containsAny( const std::string & , const std::string & );
		static bool			containsOnly( const std::string & , const std::string & );

		static bool			methodParser( std::string & , int & );
		static bool			targetParser( std::string & , std::string & );
		static bool			versionParser( const std::string & , int & );
};

#endif
