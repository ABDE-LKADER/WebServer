#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <string>
# include <vector>

typedef std::vector< std::pair<std::string, std::string> > vector_pairs;

class Request
{
	public:
		Request( void );
		~Request( void );

	private:
		std::string			method;
		std::string			target;
		std::string			version;

		vector_pairs		headers;

		bool				has_content_length;
		size_t				content_length;
};

#endif
