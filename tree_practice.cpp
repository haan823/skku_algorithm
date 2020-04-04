#include <cstdio>
#include <vector>
#include <stack>
#include <queue>

class Tree
{
public:
    int n;
    std::vector<int> *c;

    void Init(const char *_fileName)
    {
        FILE *input = fopen(_fileName, "r");
        fscanf(input, "%d", &n);
        c = new std::vector<int>[n];
        for (int i = 0; i < n; i++)
        {
            int tmp;
            while (true)
            {
                fscanf(input, "%d", &tmp);
                if (tmp == -1)
                    break;
                c[i].push_back(tmp);
            }
        }
        fclose(input);
    }
};

void DFS(Tree &_t)
{
    std::stack<int> s;
    s.push(0);
    while (!s.empty())
    {
        int x = s.top();
        printf("%d ", x);
        s.pop();
        for (int i = 0; i < (_t.c[x]).size(); i++)
        {
            s.push(_t.c[x][i]);
        }
    }
}

int main(int argc, char **argv)
{
    Tree t;
    t.Init(argv[1]);
    DFS(t);
    return 1;
}