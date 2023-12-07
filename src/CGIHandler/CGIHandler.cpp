#include "CGIHandler.hpp"

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

char **mapToArr(std::map<std::string, std::string> mp)
{
	int i = 0;
	char **arr = new char *[mp.size() + 1];
	std::map<std::string, std::string>::iterator it = mp.begin();

	while (it != mp.end())
	{
		std::string line = it->first + "=" + it->second;
		arr[i] = new char[line.length() + 1];
		strcpy(arr[i], line.c_str());
		++i;
		++it;
	}

	arr[i] = nullptr;
	return arr;
}

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
		char **envs = mapToArr(this->keyValue);
		for (size_t i = 0; envs[i]; i++)
			std::cout << i << ":" << envs[i] << "\n";
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		if (execve(CGI_BIN, (char *const *)(&php_args[0]), envs) == -1)
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
	// URI: /blog/post/index.php
	std::cout << "\n-----------------------------------------------------\n";
	std::string targetFile, folder, root_folderStr(ROOT_FOLDER);
	size_t lastSlashPos = request.getUri().rfind('/');
	if (lastSlashPos != std::string::npos)
	{
		folder = request.getUri().substr(0, lastSlashPos);
		targetFile = request.getUri().substr(lastSlashPos + 1);
	}
	std::cout << "target: " << targetFile << "\n";
	std::cout << "folder: " << folder << "\n";
	std::cout << "\n\n\n-----------------------------------------------------\n";
	this->keyValue["DOCUMENT_URI"] = folder;
	this->keyValue["SCRIPT_NAME"] = "/" + targetFile;
	this->keyValue["SCRIPT_FILENAME"] = root_folderStr + "/" + request.getUri();
	this->keyValue["REQUEST_METHOD"] = request.getMethod();
	this->keyValue["DOCUMENT_ROOT"] = root_folderStr;
	this->keyValue["PATH"] = PATH;
	this->keyValue["SERVER_NAME"] = "0.0.0.0";
	this->keyValue["SERVER_PORT"] = "8081";
	this->keyValue["GETAWAY_INTERFACE"] = "CGI/1.1";
	this->keyValue["SERVER_PROTOCOL"] = "HTTP/1.1";
	this->keyValue["REDIRECT_STATUS"] = "200";
	this->keyValue["FCGI_ROLE"] = "RESPONDER";
	this->keyValue["REQUEST_SCHEME"] = "http";
	this->keyValue["SERVER_SOFTWARE"] = "webserv/1.1";
	this->keyValue["REMOTE_ADDR"] = "0.0.0.0";
	this->keyValue["REMOTE_PORT"] = "0";
	this->keyValue["PATH_TRANSLATED"] = "";
	this->keyValue["QUERY_STRING"] = "";
	//
	/*
		// DOCUMENT_ROOT=/Users/ylabrahm/Desktop/webserv/var/www/html
		// REMOTE_ADDR=127.0.0.1
		// REMOTE_PORT=52440
		// SERVER_SOFTWARE=PHP 7.3.11 Development Server
		// SERVER_PROTOCOL=HTTP/1.1
		// SERVER_NAME=0.0.0.0
		// SERVER_PORT=8082
		// REQUEST_URI=/blog/post/index.php
		// REQUEST_METHOD=GET
		// SCRIPT_NAME=/blog/post/index.php
		// SCRIPT_FILENAME=/Users/ylabrahm/Desktop/webserv/var/www/html/blog/post/index.php
		// PHP_SELF=/blog/post/index.php
		// HTTP_HOST=0.0.0.0:8082
		// HTTP_CONNECTION=keep-alive
		// HTTP_UPGRADE_INSECURE_REQUESTS=1
		// HTTP_USER_AGENT=Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/115.0.0.0 Safari/537.36
		// HTTP_ACCEPT=text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*//*;q=0.8,application/signed-exchange;v=b3;q=0.7
		// HTTP_ACCEPT_ENCODING=gzip, deflate
		// HTTP_ACCEPT_LANGUAGE=en-US,en;q=0.9
		// REQUEST_TIME_FLOAT=1701713800.4257
		// REQUEST_TIME=1701713800
		//
	*/
	//
	// ------------------ http://localhost/blog/post?id=123 ------------------ //
	//
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