#pragma once
#include <string>
#include "i_fatal_error_handler.h"



namespace ECS
{


	class NullFatalErrorHandler : public IFatalErrorHandler
	{

	private:


	public:

		virtual void requestFatalTermination(const std::string& message) override;

	};

}