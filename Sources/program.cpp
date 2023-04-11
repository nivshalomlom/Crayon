#include "../Headers/Graphics/program.h"

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

        // If include directive found, inject target file from current line
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

void PrintShaderErrors(GLuint* shader, GLint length, std::string str_source)
{
    // Load shader error information
    glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &length);
    GLchar* strInfoLog = new GLchar[length + 1];

    glGetShaderInfoLog(*shader, length, &length, strInfoLog);
    fprintf(stderr, "Compliation error in shader:\n\n", strInfoLog);

    stringstream ss(str_source);
    string line;
    int num = 1;

    // Appeand shader errors to string
    while (!ss.eof())
    {
        getline(ss, line, '\n');
        fprintf(stderr, "%d %s\n", num++, line.c_str());
    }

    // Display shader source code with line errors
    fprintf(stderr, "\n%s\n\nPress any key to exit....", strInfoLog);
    cin.get();

    delete[] strInfoLog;
    throw new runtime_error("Error in shader compilation!");
}

void Program::AttachShader(GLuint* shader, string filePath, GLenum shaderType) const
{
    // Load and compile shader
    string str_source = ParseShader(filePath);
    const char* code = str_source.c_str();
    int length = str_source.length();

    if (length == 0)
        throw new runtime_error("Error in loading shader from file!");

    *shader = glCreateShader(shaderType);
    
    // Attach shader to program
    glShaderSource(*shader, 1, &code, &length);
    glCompileShader(*shader);
    glAttachShader(this->progID, *shader);

    // Check shader attached properly
    GLint result;
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
        PrintShaderErrors(shader, length, str_source);
}