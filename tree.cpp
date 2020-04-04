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
        s.pop();
        printf("%d ", x);
        // for (int i = 0; i < (_t.c[x]).size(); i++)
        for (int i = (_t.c[x]).size() - 1; i >= 0; i--)
        {
            s.push(_t.c[x][i]);
        }
    }
}

void BFS(Tree &_t)
{
    std::queue<int> q;
    q.push(0);
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        printf("%d ", x);
        for (int i = 0; i < (_t.c[x]).size(); i++)
        {
            q.push(_t.c[x][i]);
        }
    }
}

int main(int argc, char **argv)
{
    Tree t;
    t.Init(argv[1]);
    printf("DFS Order:\n");
    DFS(t);
    printf("BFS Order:\n");
    BFS(t);
    return 1;
}