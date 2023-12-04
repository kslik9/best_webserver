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
		return "";
	}
	php_args.push_back(CGI_BIN);
	php_args.push_back(src.path.c_str());
	php_args.push_back(NULL);
	int pipe_fd[2];
	if (pipe(pipe_fd) == -1)
	{
		std::cerr << "Error creating pipe" << std::endl;
		delete src.file_stream;
		return "";
	}
	pid_t child_pid = fork();
	if (child_pid == -1)
	{
		std::cerr << "Error forking the process" << std::endl;
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		delete src.file_stream;
		return "";
	}
	if (child_pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		if (execve(CGI_BIN, (char* const*)(&php_args[0]), (char* const*)(this->env_vec.data())) == -1)
		{
			std::cerr << "Error executing php command" << std::endl;
			_exit(EXIT_FAILURE);
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
		if (WIFEXITED(status))
			std::cout << "Child process exited with status: " << WEXITSTATUS(status) << std::endl;
		else
			std::cerr << "Child process did not exit normally" << std::endl;
		delete src.file_stream;
		return output.str();
	}
	return "NULL"; // Provisoire
}

void CGIHandler::init_env(RequestData request)
{
	std::cout << "req: [" << request << "]\n";
	// exit(1);
	this->env_vec.push_back(("REQUEST_URI=" + request.getUri()).c_str());	 // + request.getPath().substr(0, request.getPath().find_last_of("/")));
	this->env_vec.push_back("DOCUMENT_URI=");	 // + request.getPath() + request.getQueryString());
	this->env_vec.push_back("SCRIPT_NAME=/index.php");	 // +  request.getPath());
	this->env_vec.push_back("SCRIPT_FILENAME=/Users/aessaoud/Desktop/webserv/php/index.php"); // + response.get_full_path());
	this->env_vec.push_back("PATH_TRANSLATED="); // + response.get_full_path());
	this->env_vec.push_back("QUERY_STRING=");	 // + request.getQueryString());
	this->env_vec.push_back("SERVER_NAME=0.0.0.0");
	this->env_vec.push_back("SERVER_PORT=8081");	// + std::to_string(request.getPort()));
	this->env_vec.push_back(("REQUEST_METHOD=" + request.getMethod()).c_str()); // + request.getMethod());
	this->env_vec.push_back("DOCUMENT_ROOT=/Users/aessaoud/Desktop/webserv/php");	// + response.get_root());
	this->env_vec.push_back("GETAWAY_INTERFACE=CGI/1.1");
	this->env_vec.push_back("SERVER_PROTOCOL=HTTP/1.1");
	this->env_vec.push_back("REDIRECT_STATUS=200");
	this->env_vec.push_back("FCGI_ROLE=RESPONDER");
	this->env_vec.push_back("REQUEST_SCHEME=http");
	this->env_vec.push_back("SERVER_SOFTWARE=webserv/1.1");
	this->env_vec.push_back(("PATH=" + std::string(std::getenv("PATH"))).c_str());
	this->env_vec.push_back("REMOTE_ADDR=0.0.0.0");
	this->env_vec.push_back("REMOTE_PORT=0");
	this->env_vec.push_back(NULL);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */