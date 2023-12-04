#include "CGIHandler.hpp"

// _extention(""),
// _cgi_path(""),
// _methods(std::vector<std::string>()),
// _envp(NULL),
// _argv(NULL),
// _cgi_response_file(""),
// _status(""),
// _header(""),
// _FILEINLINE("") {}

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

CGIHandler::CGIHandler()
{
}

CGIHandler::CGIHandler(RequestData request)
{
	this->init_env(request);
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

CGIHandler::~CGIHandler()
{
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

/*
** --------------------------------- METHODS ----------------------------------
*/

std::string CGIHandler::process()
{
	std::vector<const char *> php_args;
	php_script src;
	src.path = "php/index.php";
	src.file_stream = new std::ifstream(src.path);
	if (!src.file_stream->is_open())
	{
		std::cerr << "Error opening the file: " << src.path << std::endl;
		delete src.file_stream;
		return "delete";
	}
	php_args.push_back(CGI_BIN);
	php_args.push_back(src.path.c_str());
	php_args.push_back(NULL);
	int pipe_fd[2];
	if (pipe(pipe_fd) == -1)
	{
		std::cerr << "Error creating pipe" << std::endl;
		delete src.file_stream;
		return "delete";
	}
	pid_t child_pid = fork();
	if (child_pid == -1)
	{
		std::cerr << "Error forking the process" << std::endl;
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		delete src.file_stream;
		return "delete";
	}
	if (child_pid == 0)
	{
		std::cout << "78: " << this->env_vec.data()[5] << std::endl;
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		if (execve(CGI_BIN, (char *const *)(&php_args[0]), (char *const *)(this->env_vec.data())) == -1)
		{
			std::cerr << "Error executing php command" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		close(pipe_fd[1]);
		std::stringstream output;
		char buffer[4096];
		ssize_t bytes_read;
		while ((bytes_read = read(pipe_fd[0], buffer, sizeof(buffer))) > 0)
			output.write(buffer, bytes_read);
		close(pipe_fd[0]);
		int status;
		waitpid(child_pid, &status, 0);
		delete src.file_stream;
		return output.str();
	}
	return "NULL"; // Provisoire
}

void CGIHandler::init_env(RequestData request)
{
	this->env_vec.push_back("DOCUMENT_URI=/blog/post");
	this->env_vec.push_back("SCRIPT_NAME=/index.php");
	this->env_vec.push_back("SCRIPT_FILENAME=/Users/ylabrahm/Desktop/webserv/var/www/html/blog/post/index.php");
	this->env_vec.push_back("SERVER_NAME=0.0.0.0");
	this->env_vec.push_back("SERVER_PORT=8081");
	this->env_vec.push_back("REQUEST_METHOD= + request.getMethod()).c_str()");
	this->env_vec.push_back("DOCUMENT_ROOT=GET");
	this->env_vec.push_back("GETAWAY_INTERFACE=CGI/1.1");
	this->env_vec.push_back("SERVER_PROTOCOL=HTTP/1.1");
	this->env_vec.push_back("REDIRECT_STATUS=200");
	this->env_vec.push_back("FCGI_ROLE=RESPONDER");
	this->env_vec.push_back("REQUEST_SCHEME=http");
	this->env_vec.push_back("SERVER_SOFTWARE=webserv/1.1");
	this->env_vec.push_back("PATH=/Users/ylabrahm/goinfre/homebrew/bin:/Users/ylabrahm/goinfre/homebrew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki");
	this->env_vec.push_back("REMOTE_ADDR=0.0.0.0");
	this->env_vec.push_back("REMOTE_PORT=0");
	this->env_vec.push_back("PATH_TRANSLATED=");
	this->env_vec.push_back("QUERY_STRING=");
	this->env_vec.push_back(NULL);
	// ------------------ http://localhost/blog/post?id=123 ------------------ //
	// REQUEST_URI=/blog/post?id=123
	// DOCUMENT_URI=/blog/post
	// SCRIPT_NAME=/index.php
	// SCRIPT_FILENAME=/var/www/html/index.php
	// PATH_TRANSLATED=/var/www/html/index.php
	// QUERY_STRING=id=123
	// SERVER_NAME=example.com
	// SERVER_PORT=80
	// REQUEST_METHOD=GET
	// DOCUMENT_ROOT=/var/www/html
	// GATEWAY_INTERFACE=CGI/1.1
	// SERVER_PROTOCOL=HTTP/1.1
	// REDIRECT_STATUS=200
	// FCGI_ROLE=RESPONDER
	// REQUEST_SCHEME=http
	// SERVER_SOFTWARE=Apache/2.4.29
	// PATH=/usr/local/bin:/usr/bin:/bin
	// REMOTE_ADDR=192.168.1.100
	// REMOTE_PORT=12345
	// ----------------------------------------------------------------------- //
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */