#include "cgi.hpp"

typedef struct
{
    std::string path;
    std::ifstream *file_stream;
} php_script;

std::string execute_php(std::string file)
{
    std::vector<char *> php_args;
    php_script src;
    src.path = file;
    src.file_stream = new std::ifstream(src.path);
    if (!src.file_stream->is_open())
    {
        std::cerr << "Error opening the file: " << src.path << std::endl;
        delete src.file_stream;
        return "";
    }
    php_args.push_back(const_cast<char *>("php"));
    php_args.push_back(const_cast<char *>(src.path.c_str()));
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
        char *php_env[] = {NULL};
        if (execve("/usr/bin/php", &php_args[0], php_env) == -1)
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
