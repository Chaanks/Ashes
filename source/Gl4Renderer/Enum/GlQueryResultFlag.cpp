#include "GlRendererPrerequisites.hpp"

namespace ashes::gl4
{
	std::string getName( GlQueryResultFlag value )
	{
		switch ( value )
		{
		case 0u:
			return "0";

		case GL_QUERY_RESULT:
			return "GL_QUERY_RESULT";

		case GL_QUERY_RESULT_NO_WAIT:
			return "GL_QUERY_RESULT_NO_WAIT";

		default:
			assert( false && "Unsupported GlQueryResultFlag" );
			return "GL_QUERY_RESULT_UNKNOWN";
		}
	}

	std::string getName( GlQueryResultFlags value )
	{
		std::string result;
		std::string sep;

		if ( checkFlag( value, GL_QUERY_RESULT ) )
		{
			result += sep + getName( GL_QUERY_RESULT );
			sep = "|";
		}

		if ( checkFlag( value, GL_QUERY_RESULT_NO_WAIT ) )
		{
			result += sep + getName( GL_QUERY_RESULT_NO_WAIT );
			sep = "|";
		}

		if ( !value )
		{
			result = "0";
		}

		return result;
	}

	GlQueryResultFlags convertQueryResultFlags( VkQueryResultFlags const & flags )
	{
		GlQueryResultFlags result{ 0 };

		if ( ashes::checkFlag( flags, VK_QUERY_RESULT_WAIT_BIT ) )
		{
			return GL_QUERY_RESULT;
		}

		if ( ashes::checkFlag( flags, VK_QUERY_RESULT_WITH_AVAILABILITY_BIT ) )
		{
			return GL_QUERY_RESULT_NO_WAIT;
		}

		return result;
	}
}
