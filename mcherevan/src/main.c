
#include "../inc/race02.h"


int rowNum[] = {-1, 0, 0, 1};
int colNum[] = {0, -1, 1, 0};

void mx_printchar(char c) {
    write(1, &c, 1);
}

void mx_printint(int n) {
    if (n == -2147483648) {
        write(1, "-2147483648", 11);
        return;
    }
    if (n < 0) {
        mx_printchar('-');
        n = -n;
    }
    if (n / 10 != 0) {
        mx_printint(n / 10);
    }
    mx_printchar(n % 10 + '0');
}

void mx_memset(void *ptr, int value, size_t num) {
    char *temp = (char *)ptr;
    for (size_t i = 0; i < num; i++) {
        *(temp + i) = value;
    }
}

void mx_init_queue(mx_queue *q, int capacity) {
    q->capacity = capacity;
    q->front = q->size = 0;
    q->rear = capacity - 1;
    q->nodes = (QueueNode *)malloc(capacity * sizeof(QueueNode));
}

bool mx_is_full(mx_queue *q) {
    return (q->size == q->capacity);
}

bool mx_is_empty(mx_queue *q) {
    return (q->size == 0);
}

void mx_enqueue(mx_queue *q, QueueNode item) {
    if (!mx_is_full(q)) {
        q->rear = (q->rear + 1) % q->capacity;
        q->nodes[q->rear] = item;
        q->size++;
    }
}

QueueNode mx_dequeue(mx_queue *q) {
    QueueNode item = { .pt = {-1, -1}, .dist = -1, .pred = {-1, -1} };
    if (!mx_is_empty(q)) {
        item = q->nodes[q->front];
        q->front = (q->front + 1) % q->capacity;
        q->size--;
    }
    return item;
}

void print_error(const char *message) {
    write(STDERR_FILENO, message, mx_strlen(message));
}

void printGrid(char grid[][MAX], int ROW, int COL) {
    char buffer[3];
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            buffer[0] = grid[i][j];
            buffer[1] = ' ';
            buffer[2] = '\0';
            write(STDOUT_FILENO, buffer, 2);
        }
        write(STDOUT_FILENO, "\n", 1);
    }
}

bool isEqualPoint(Point a, Point b) {
    return a.x == b.x && a.y == b.y;
}

void markPath(char grid[][MAX], Point pred[][MAX], Point start, Point end, char mark) {
    while (!isEqualPoint(end, start)) {
        grid[end.x][end.y] = mark;
        end = pred[end.x][end.y];
    }
}

bool BFS(char grid[][MAX], int ROW, int COL, Point start, Point destination) {
    bool visited[MAX][MAX] = {{false}};
    Point pred[MAX][MAX], farthestPoints[MAX * MAX];
    mx_memset(pred, -1, sizeof(pred));
    int farthestDist = 0, farthestCount = 0;
    int stepsToDestination = -1;

    mx_queue q;
    mx_init_queue(&q, MAX * MAX);
    mx_enqueue(&q, (QueueNode){start, 0, {start.x, start.y}});
    visited[start.x][start.y] = true;

    while (!mx_is_empty(&q)) {
        QueueNode node = mx_dequeue(&q);
        Point pt = node.pt;
        int dist = node.dist;

        if (dist > farthestDist) {
            farthestDist = dist;
            farthestCount = 0;
        }

        if (dist == farthestDist) {
            farthestPoints[farthestCount++] = pt;
        }

        for (int i = 0; i < 4; ++i) {
            int nx = pt.x + rowNum[i], ny = pt.y + colNum[i];

            if (nx >= 0 && nx < ROW && ny >= 0 && ny < COL && grid[nx][ny] == '.' && !visited[nx][ny]) {
                visited[nx][ny] = true;
                pred[nx][ny] = pt;
                mx_enqueue(&q, (QueueNode){{nx, ny}, dist + 1, pt});
            }
        }
    }

    bool destinationReached = visited[destination.x][destination.y];
    if (destinationReached) {
        Point current = destination;
        while (!isEqualPoint(current, start)) {
            current = pred[current.x][current.y];
            stepsToDestination++;
        }
        markPath(grid, pred, start, destination, '*');
        grid[start.x][start.y] = '*';
    }

    for (int i = 0; i < farthestCount; ++i) {
        Point fp = farthestPoints[i];
        if (!isEqualPoint(fp, destination)) {
            grid[fp.x][fp.y] = 'D';
        }
        else
            grid[fp.x][fp.y] = 'X';
    }


    if (destinationReached)
    {
    write(1, "Dist=", 5);
    mx_printint(farthestDist);
    mx_printchar('\n');
    if (stepsToDestination != -1) {
        write(1, "Exit=", 5);
        mx_printint(++stepsToDestination);
        mx_printchar('\n');
    }
    }

    return destinationReached;
}

int main(int argc, char *argv[])
{
    int ROW = 0, COL = 0;
    char grid[MAX][MAX];
    
	if (argc != 6)
	{
        	print_error("Usage: %s [file_name] [x1] [y1] [x2] [y2]\n");
        	return 1;
    	}
    	char *file_name = argv[1];
    	int x1 = mx_atoi(argv[2]);
   	int y1 = mx_atoi(argv[3]);
	int x2 = mx_atoi(argv[4]);
  	int y2 = mx_atoi(argv[5]);
  	Point start = {x1, y1}, destination = {y2, x2};
  	
    int fd = open(file_name, 'r');
    if(fd == -1)
    {
    	print_error("map does not exist\n");
	return 2;
    }
	char c;
	int cnt = 0;
	while(read(fd,&c,1) > 0)
	{
		if (c != '#' && c != '.' && c != ',' && c != '\n')
		{
			print_error("map error\n");
			return 2;
		}
		if (c == '\n')
		{
			ROW++;
			COL = cnt;
			cnt =0;
		}
		else if (c == '#' || c == '.')
		{
			grid[ROW][cnt++] = c;
		}
	}
	if(ROW < 2)
        {
        	print_error("map does not exist\n");
        	close(fd);
		return 2;
        }
      close(fd);
        
    if (start.x < 0 || start.y < 0 || destination.x < 0 || destination.y < 0 || start.x >= ROW || start.y >= COL || destination.x >= ROW  || destination.y >= COL)
    {
    	print_error("points are out of map range\n");	
    	return 1;
    }
    	
    if (grid[start.x][start.y] != '.')
    {
    	print_error("entry point cannot be an obstacle\n");
    	return 1;
    }
    else if (grid[destination.x][destination.y] != '.')
    {
    	print_error("exit point cannot be an obstacle\n");
    	return 1;
    }
    
    bool isRoadFound = BFS(grid, ROW, COL, start, destination);
    if (!isRoadFound) {
        print_error("route not found\n");
        return 1;
    }


    int pt = open("path.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (pt == -1)
        {
        	print_error("error\n");
        	return 2;
        	close(pt);
        }
	for (int y = 0; y < ROW; y++)
        {
      	  	for (int x = 0; x < COL; x++)
      	  	{
      		  	char ch = grid[y][x];
            		write(pt, &ch, 1);
        	}
        	write(pt, "\n", 1);
        }
        close(pt);
    return 0;
}

