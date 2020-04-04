#include <cstdio>
#include <queue>
#include <string>
using namespace std;

typedef struct
{
    int x;
    int y;
    int d;
} Node;

class Chess
{
public:
    int n;
    int **c;
    int dst_x, dst_y;
    int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    Node root;

    void Init(const char *_fileName)
    {
        FILE *input = fopen(_fileName, "r");
        fscanf(input, "%d", &n);
        fscanf(input, "%d", &root.x);
        fscanf(input, "%d", &root.y);
        fscanf(input, "%d", &dst_x);
        fscanf(input, "%d", &dst_y);
        root.d = 0;

        c = new int *[n];
        for (int i = 0; i < n; i++)
        {
            c[i] = new int[n];
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                c[i][j] = 0;
            }
        }

        fclose(input);
    }
};

void BFS(Chess &_c, FILE *fp)
{
    std::queue<Node> q;
    q.push(_c.root);
    _c.c[_c.root.x][_c.root.y] = 1;

    if (!(_c.dst_x >= 0 and _c.dst_x < _c.n and _c.dst_y >= 0 and _c.dst_y < _c.n))
    {
        fputs("-1", fp);
        return;
    }

    while (true)
    {
        Node now = q.front();
        q.pop();
        if (now.x == _c.dst_x and now.y == _c.dst_y)
        {
            fputs(std::to_string(now.d).c_str(), fp);
            break;
        }
        for (int i = 0; i < 8; i++)
        {
            Node next;
            next.x = now.x - _c.dx[i];
            next.y = now.y - _c.dy[i];
            next.d = now.d + 1;

            if (next.x >= 0 and next.x < _c.n and next.y >= 0 and next.y < _c.n and _c.c[next.x][next.y] == 0)
            {
                q.push(next);
                _c.c[next.x][next.y] = 1;
            }
        }
    }
}

int main(int argc, char **argv)
{
    FILE *fp;
    fp = fopen(argv[2], "w");
    Chess ch;
    ch.Init(argv[1]);
    BFS(ch, fp);
    fclose(fp);
}