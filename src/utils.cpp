#include <string>

namespace Utility {

	std::string to_string( const std::string& str )
	{
		/* this may look dumb, but it actually has a use involving macros
		and blind calls of to_string() on everything */
		return str;
	}

	std::string to_string( const void *ptr )
	{
		char buff[20] = { 0 };

		if ( ptr )
			std::snprintf( buff, 20, "0x%p", ptr );
		else
			std::snprintf( buff, 20, "nullptr" );

		return std::string( buff );
	}

};


