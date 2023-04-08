#include "../Headers/Models/shader.h"

using namespace std;

const static string INCLUDE_DIRECTIVE = "#include \"";

string WorkingDirectory(string filePath)
{
    int len = filePath.length();
    for (int i = len - 1; i > -1; i--)
    {
        char c = filePath[i];
        if (c == '\\' || c == '/')
            return filePath.substr(0, i + 1);
    }

    return "";
}

string ParseShader(string shaderPath)
{
    ifstream shader(shaderPath);
    string output = "", line;

    if (!shader.is_open())
        return output;

    string workingDirectory = WorkingDirectory(shaderPath);
    while (getline(shader, line))
    {
        if (line.empty())
            continue;

        if (line.rfind(INCLUDE_DIRECTIVE, 0) == 0)
        {
            line = line.substr(INCLUDE_DIRECTIVE.length());
            line.pop_back();

            output += ParseShader(workingDirectory + line);
        }
        else
            output += line + '\n';
    }

    shader.close();
    return output;
}