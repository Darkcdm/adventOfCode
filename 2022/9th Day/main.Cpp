// Your First C++ Program

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

struct Knot
{
    int x;
    int y;
    int oldX;
    int oldY;
    char symbol;
    struct Knot *next;
};

struct Rope
{
    int length;
    struct Knot *head;
    struct Knot *tail;
};

struct Cell
{
    int x;
    int y;
    bool visited;
    bool isStart;
};

struct Board
{
    int width;
    int height;
    struct Rope *rope;
    struct Cell **cells;
};

struct Order
{
    int amount;
    char direction;
};

void printSpacer(int count)
{
    cout << "- - " << count << " - -" << endl;
}

void printBoard(struct Board board)
{
    int startX = board.rope->head->x - 2;
    int startY = board.rope->head->y - 2;

    int headX = board.rope->head->x;
    int headY = board.rope->head->y;

    int tailX = board.rope->tail->x;
    int tailY = board.rope->tail->y;

    for (int y = startY; y < startY + 5; y++)
    {
        for (int x = startX; x < startX + 5; x++)
        {
            if (board.cells[y][x].isStart)
            {
                cout << 's';
            }
            else if (y == headY && x == headX)
            {
                cout << 'H';
            }
            else if (y == tailY && x == tailX)
            {
                cout << 'T';
            }
            else if (board.cells[x][y].visited)
            {
                cout << '#';
            }
            else
            {
                cout << '*';
            }

            cout << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

void printStaticBoard(struct Board board)
{

    int startX = board.width / 2;
    int startY = board.height / 2 - 5;

    int headX = board.rope->head->x;
    int headY = board.rope->head->y;

    int tailX = board.rope->tail->x;
    int tailY = board.rope->tail->y;

    for (int y = startY; y < startY + 6; y++)
    {
        for (int x = startX; x < startX + 5; x++)
        {
            if (board.cells[y][x].isStart)
            {
                cout << 's';
            }
            else if (y == headY && x == headX)
            {
                cout << 'H';
            }
            else if (y == tailY && x == tailX)
            {
                cout << 'T';
            }
            else if (board.cells[x][y].visited)
            {
                cout << '#';
            }
            else
            {
                cout << '*';
            }

            cout << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

void loadOrders(struct Order **orders)
{
    ifstream input("input.txt");
    string line;
    int index = 0;

    while (getline(input, line))
    {
        orders[0][index].direction = line[0];
        orders[0][index].amount = std::stoi(line.substr(2, line.length()));
        index++;
    }

    orders[0][index + 1].direction = 0;
    orders[0][index + 1].amount = 0;

    input.close();
}

int getOrdersLength()
{
    ifstream input("input.txt");
    string line;
    int count = 0;
    while (getline(input, line))
    {
        count++;
    }
    return count;

    input.close();
}

void moveHead(char direction, struct Knot *head)
{
    head->oldX = head->x;
    head->oldY = head->y;

    switch (direction)
    {
    case 'U':
        head->y = head->y - 1;
        break;
    case 'D':
        head->y = head->y + 1;
        break;
    case 'R':
        head->x = head->x + 1;
        break;
    case 'L':
        head->x = head->x - 1;
        break;
    default:
        cout << "Invalid direction " << direction;
        break;
    }
}

void moveTail(struct Knot head, struct Knot *tail)
{
    int distance = sqrt(pow(tail->x - head.x, 2) + pow(tail->y - head.y, 2));

    if (distance > 1)
    {
        if (head.x == tail->x)
        {
            if (tail->y < head.y)
            {
                tail->y++;
            }
            else
            {
                tail->y--;
            }
        }

        else if (head.y == tail->y)
        {
            if (tail->x < head.x)
            {
                tail->x++;
            }
            else
            {
                tail->x--;
            }
        }
        else
        {

            tail->y = head.oldY;
            tail->x = head.oldX;
        }
    }
}

void saveHeadPos(struct Knot head, struct Knot *old)
{
    old->x = head.x;
    old->y = head.y;
}

void markVisited(struct Board *board, struct Knot tail)
{
    board->cells[tail.x][tail.y].visited = true;
}

int countVisited(struct Board board)
{
    int count = 0;

    for (int y = 0; y < board.height; y++)
    {
        for (int x = 0; x < board.width; x++)
        {
            if (board.cells[y][x].visited)
            {
                count++;
            }
        }
    }

    return count;
}

struct Knot *createRope(int staticLength, int length, int x, int y)
{
    Knot knot;

    knot.x = x;
    knot.oldX = x;
    knot.y = y;
    knot.oldY = y;
    knot.symbol = 48 + staticLength - length;

    if (length > 0)
    {
        knot.next = createRope(staticLength, length - 1, x, y);
    }
    else
    {
        knot.next = NULL;
    }

    return &knot;
}

struct Knot *findKnot(struct Knot *knot, int length)
{
    if (length == 0)
    {
        return knot;
    }
    else
    {
        findKnot(knot->next, length - 1);
    }
}

int main()
{
    std::cout << "Starting the Program \n";
    std::cout << "Initializing all required variables \n";

    struct Board board;

    board.height = 501;
    board.width = 501;

    board.cells = (struct Cell **)calloc(board.height, sizeof(struct Cell));

    for (int i = 0; i < board.width; i++)
    {
        board.cells[i] = (struct Cell *)calloc(board.width, sizeof(struct Cell));
    }

    struct Rope rope;
    rope.length = 10;

    rope.head = createRope(rope.length, rope.length, board.width / 2, board.height / 2);
    rope.tail = findKnot(rope.head, rope.length - 1);

    struct Knot *head = rope.head;
    head->symbol = 'H';

    struct Knot *tail = rope.tail;
    tail->symbol = 'T';

    board.rope = &rope;

    for (int y = 0; y < board.height; y++)
    {
        for (int x = 0; x < board.width; x++)
        {
            struct Cell *cell = &board.cells[y][x];

            if (x == head->x && y == head->y)
            {
                cell->isStart = true;
                cell->visited = true;
            }

            cell->x = x;
            cell->y = y;
        }
    }

    struct Order *orders;
    orders = (struct Order *)calloc(getOrdersLength() + 1, sizeof(struct Order));

    loadOrders(&orders);

    cout << "Starting the Simulation\n";

    int index = 0;
    while (orders[index].amount != 0)
    {
        // printSpacer(index);

        for (int orderCount = 0; orderCount < orders[index].amount; orderCount++)
        {
            markVisited(&board, *tail);

            moveHead(orders[index].direction, head);
            moveTail(*head, tail);

            markVisited(&board, *tail);

            // printStaticBoard(board);
            // printBoard(board);
        }

        // printBoard(board);
        index++;
    }

    cout << endl
         << "Tail has visited: " << countVisited(board) << endl;

    cout << "DeAllocing all variables" << endl;

    free(board.cells);

    std::cout << "Ending the Program \n";
    return 0;
}
