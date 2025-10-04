// core.cpp - main entry point

# include "core.hpp"

int	main( int argc, char **argv ) {
	try {
		if (argc != 2) {
			std::cerr << "Usage: " << *argv << " <config_file>" << std::endl;
			return EXIT_FAILURE;
		}

		std::string config_file(argv[1]);

		ConfigParser parser(config_file);
		std::vector<ServerConfig> servers = parser.parseConfig();

		/*********************************TESTS BLOCK********************************/
		/************************* print servers after parse ************************/
		printServers(servers);
		/****************************************************************************/
		
		Server	server(servers);
		server.run();

		return EXIT_SUCCESS;

	} catch ( const std::exception &e ) {
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	} catch ( ... ) {
		std::cerr << "Error: all" << std::endl;
	}
}
