#include "Session.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Session::Session()
{
}

Session::Session(const Session &src)
{
}

Session::Session(Server &server, Config &config)

{
	std::cout << "port: " << config.getPort() << std::endl;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Session::~Session()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Session &Session::operator=(Session const &rhs)
{
	// if ( this != &rhs )
	//{
	// this->_value = rhs.getValue();
	//}
	return *this;
}

std::ostream &operator<<(std::ostream &o, Session const &i)
{
	// o << "Value = " << i.getValue();
	return o;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */