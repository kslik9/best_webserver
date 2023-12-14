#include "webserv.hpp"

bool fileStartsWithLine(std::string buffer, std::string line)
{
    size_t startPos = 0;
    while (startPos < buffer.length() && (std::isspace(buffer[startPos])))
    {
        ++startPos;
    }
    return buffer.substr(startPos, line.length()) == line;
}

void appendToPhpFile(std::string const phpFile)
{
    std::string line = "<?php $rawData = file_get_contents('php://input'); $postData = []; parse_str($rawData, $postData); foreach ($postData as $key => $value) { $_POST[trim($key)] = $value; } ?>\n";
    std::fstream file(phpFile.c_str());
    std::string allStr;
    if (file.is_open())
    {
        std::stringstream buffer;
        buffer << file.rdbuf();
        if (fileStartsWithLine(buffer.str(), line))
            return;
        file.close();
        std::cout << buffer.str() << std::endl;

        allStr.append(line);
        allStr.append(buffer.str());

        std::cout << "allstr: [" << allStr << "]\n";
        file.close();
    }

    std::fstream file2(phpFile.c_str(), std::ofstream::out | std::ofstream::trunc);
    if (file2.is_open())
    {
        file2 << allStr;
        file2.close();
    }
}
