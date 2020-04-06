#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>
#include <stack>
#include <cctype>
using namespace std;

class Input
{
public:
    std::vector<char> c;

    void Init(const char *_fileName)
    {
        FILE *input = fopen(_fileName, "r");
        char tmp;
        while (EOF != fscanf(input, "%c", &tmp))
        {
            c.push_back(tmp);
        }
        fclose(input);
    }
};

std::vector<char> Post(std::vector<char> c)
{
    std::stack<char> s;
    std::vector<char> postfix;
    for (int i = 0; i < c.size(); i++)
    {
        if (isdigit(c[i]))
        {
            postfix.push_back(c[i]);
        }
        else if (c[i] == '(')
        {
            s.push(c[i]);
        }
        else if (c[i] == '*' || c[i] == '/')
        {
            if (!s.empty())
            {
                if (s.top() == '+' || s.top() == '-' || s.top() == '(')
                {
                    s.push(c[i]);
                }
                else if (s.top() == '*' || s.top() == '/')
                {
                    char x = s.top();
                    s.pop();
                    postfix.push_back(x);
                    s.push(c[i]);
                }
            }
            else
            {
                s.push(c[i]);
            }
        }
        else if (c[i] == '+' || c[i] == '-')
        {
            if (!s.empty())
            {
                if (s.top() == '(' || s.empty())
                {
                    s.push(c[i]);
                }
                else if (s.top() == '+' || s.top() == '-' || s.top() == '*' || s.top() == '/')
                {
                    char x = s.top();
                    s.pop();
                    postfix.push_back(x);
                    s.push(c[i]);
                }
            }
            else
            {
                s.push(c[i]);
            }
        }
        else if (c[i] == ')')
        {
            while (true)
            {
                if (s.top() == '(')
                {
                    s.pop();
                    break;
                }
                else
                {
                    char x = s.top();
                    s.pop();
                    postfix.push_back(x);
                }
            }
        }
    }
    while (!s.empty())
    {
        char x = s.top();
        s.pop();
        postfix.push_back(x);
    }
    return postfix;
}

void cal(std::vector<char> c, FILE *fp)
{
    std::stack<string> s;
    for (int i = 0; i < c.size(); i++)
    {
        if (isdigit(c[i]))
        {
            string str(1, c[i]);
            s.push(str);
        }
        else if (c[i] == '+')
        {
            float a = stof(s.top());
            s.pop();
            float b = stof(s.top());
            s.pop();
            float result = round((a + b) * 100) / 100.0;
            s.push(to_string(result));
        }
        else if (c[i] == '-')
        {
            float a = stof(s.top());
            s.pop();
            float b = stof(s.top());
            s.pop();
            float result = round((b - a) * 100) / 100.0;
            s.push(to_string(result));
        }
        else if (c[i] == '*')
        {
            float a = stof(s.top());
            s.pop();
            float b = stof(s.top());
            s.pop();
            float result = round((a * b) * 100) / 100.0;
            s.push(to_string(result));
        }
        else if (c[i] == '/')
        {
            float a = stof(s.top());
            s.pop();
            float b = stof(s.top());
            s.pop();
            float result = round((b / a) * 100) / 100.0;
            s.push(to_string(result));
        }
        // printf("%d %s\n", i, s.top().c_str());
    }
    float result = stof(s.top());
    fprintf(fp, "%.2f", result);
}

int main(int argc, char **argv)
{
    FILE *fp;
    fp = fopen(argv[2], "w");
    Input x;
    x.Init(argv[1]);
    cal(Post(x.c), fp);
    fclose(fp);
}