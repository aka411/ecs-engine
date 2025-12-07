#pragma once
#include <string>

namespace TheEngine::ECS
{
	

	class IFatalErrorHandler
	{

	private:


	public:

		virtual void requestFatalTermination(const std::string& message) = 0;

	};

}