#pragma once
#include <string>

namespace ECS
{
	

	class IFatalErrorHandler
	{

	private:


	public:

		virtual void requestFatalTermination(const std::string& message) = 0;

	};

}