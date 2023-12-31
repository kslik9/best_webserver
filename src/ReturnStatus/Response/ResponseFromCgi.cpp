#include "ResponseFromCgi.hpp"

void ResponseFromCgi::init_env(RequestData request, std::string const &root)
{
	this->inBody = request.getBody();
	std::string targetFile, folder, root_folderStr(root);
	size_t lastSlashPos = request.getUri().rfind('/');
	if (lastSlashPos != std::string::npos)
	{
		folder = request.getUri().substr(0, lastSlashPos);
		targetFile = request.getUri().substr(lastSlashPos + 1);
	}
	this->keyValue["DOCUMENT_URI"] = folder;
	this->keyValue["SCRIPT_NAME"] = "/" + targetFile;
	this->keyValue["SCRIPT_FILENAME"] = root_folderStr + "/" + request.getUri();
	this->keyValue["REQUEST_METHOD"] = request.getMethod();
	this->keyValue["DOCUMENT_ROOT"] = root_folderStr;
	this->keyValue["GETAWAY_INTERFACE"] = "CGI/1.1";
	this->keyValue["SERVER_PROTOCOL"] = "HTTP/1.1";
	this->keyValue["REDIRECT_STATUS"] = "200";
	this->keyValue["FCGI_ROLE"] = "RESPONDER";
	this->keyValue["REQUEST_SCHEME"] = "http";
	this->keyValue["SERVER_SOFTWARE"] = "webserv/1.1";
	this->keyValue["QUERY_STRING"] = request.getQueryString();
	this->keyValue["CONTENT_LENGTH"] = std::to_string(this->inBody.length());
	// 
}

ResponseFromCgi::ResponseFromCgi(RequestData &rq, std::string const &root)
{
	this->init_env(rq, root);
	this->headers["Content-Type"] = get_mime_type(root);
	this->headers["Date"] = getCurrentTime();
	this->statusCode = "200";
	this->statusMessage = "OK";
}

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

std::string ResponseFromCgi::process(bool &error)
{
	std::vector<const char *> php_args;
	php_script src;
	appendToPhpFile(this->keyValue["SCRIPT_FILENAME"]);
	src.path = this->keyValue["SCRIPT_FILENAME"];
	src.file_stream = new std::ifstream(src.path);
	if (!src.file_stream->is_open())
	{
		std::cerr << "Error opening the file: " << src.path << std::endl;
		delete src.file_stream;
		error = true;
		return "-1";
	}
	php_args.push_back(CGI_BIN);
	php_args.push_back(src.path.c_str());
	php_args.push_back(NULL);
	int pipe_fd[2];
	if (pipe(pipe_fd) == -1)
	{
		std::cerr << "Error creating pipe" << std::endl;
		delete src.file_stream;
		error = true;
		return "-1";
	}
	pid_t child_pid = fork();
	if (child_pid == -1)
	{
		std::cerr << "Error forking the process" << std::endl;
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		delete src.file_stream;
		error = true;
		return "-1";
	}
	if (child_pid == 0)
	{
		char **envs = mapToArr(this->keyValue);
		dup2(pipe_fd[1], STDOUT_FILENO);
		std::string postData = this->inBody;
    	write(pipe_fd[1], postData.c_str(), postData.length());
		dup2(pipe_fd[0], STDIN_FILENO);
		if (execve(CGI_BIN, (char *const *)(&php_args[0]), envs) == -1)
		{
			std::cerr << "Error executing php command" << std::endl;
			error = true;
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		int status;
		waitpid(child_pid, &status, 0);
		close(pipe_fd[1]);
		std::stringstream output;
		char buffer[4096];
		ssize_t bytes_read;
		while ((bytes_read = read(pipe_fd[0], buffer, sizeof(buffer))) > 0)
		{
			output.write(buffer, bytes_read);
		}
		close(pipe_fd[0]);
		delete src.file_stream;
		return output.str();
	}
	error = true;
	return "-1";
}

std::string ResponseFromCgi::createResponse()
{
	startLine = "HTTP/1.1 " + this->statusCode + " " + this->statusMessage + "\r\n";

	std::map<std::string, std::string>::iterator it;
	response << startLine;
	bool error = false;

	std::string php_resp = this->process(error);
	if (error) {
		InternalServerError500 internalServerError(this->errorPath);
		return internalServerError.createResponse();
	}
	response << php_resp;
	return response.str();
}
