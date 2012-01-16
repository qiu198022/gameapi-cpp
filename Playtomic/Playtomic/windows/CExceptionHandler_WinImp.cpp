#include "../CExceptionHandler.h"
#include "StackWalker.h"

namespace Playtomic
{
	void CExceptionHandler::GetStackTrace(std::string& dest)
	{
		StackWalker stack;
		stack.GetCallStackString(dest);
	}
}