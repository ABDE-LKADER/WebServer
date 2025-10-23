#ifndef MIMERESOLVER_HPP
# define MIMERESOLVER_HPP

# include "Core.hpp"

# define INSERT_MAPPING(ext, mime) extToMime[ext] = mime; \
	if (mimeToExt.find(mime) == mimeToExt.end()) mimeToExt[mime] = "." ext;

class MimeResolver {
	public:
		MimeResolver( void );
		~MimeResolver( void );

		const std::string		&getMimeType( const std::string & ) const;
		const std::string		&getExtension( const std::string & ) const;

	private:
		std::string				to_lower( const std::string & ) const;
		void					initializeMaps( void );

		map_s					extToMime;
		map_s					mimeToExt;
};

#endif
