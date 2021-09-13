#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

typedef struct shape{
	char c;
	float x;
	float y;
	float r;
	char d;
}			circle;

typedef struct back{
	size_t	w;
	size_t	h;
	char	d;
}				back;

char **fill_back(back back)
{
	char **ret;
	size_t x, y;

	ret = calloc(back.h + 1, sizeof(char *));
	y = 0;
	while (y < back.h)
	{
		x = 0;
		ret[y] = calloc(back.w + 1, sizeof(char));
		while (x < back.w)
		{
			ret[y][x] = back.d;
			x++;
		}
		y++;
	}
	return(ret);
}
void normlize(circle shape, int *x, int *y, int *r)
{
	*x = shape.x;
	if ((float)(*x) != shape.x)
		(*x)++;
	*y = shape.y;
	if ((float)(*y) != shape.y)
		(*y)++;
	*r = shape.r;
	if ((float)(*r) != shape.r)
		(*r)++;
}

void draw(char **table, circle shape)
{
	int w,h;
	float distance_sqrt;
	float distance;

	if (shape.c == 'c')
	{
		h = -1;
		while (table[++h] != 0)
		{
			w = -1;
			while (table[h][++w] != 0)
			{
				distance_sqrt = sqrt(pow(w - shape.x, 2) + pow(h - shape.y, 2));
				distance = distance_sqrt - shape.r;
				if (distance <= 0)
				{
					if (distance > -1.000)
						table[h][w] = shape.d;
				}
			}
		}
	}
	else if (shape.c == 'C')
	{
		h = -1;
		while (table[++h] != 0)
		{
			w = -1;
			while (table[h][++w] != 0)
			{
				distance_sqrt = sqrt(pow(w - shape.x, 2) + pow(h - shape.y, 2));
				if (distance_sqrt <= shape.r)
					table[h][w] = shape.d;
			}
		}
	}
}

int ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

int execute(FILE *file)
{
	int fprin;
	back back;
	circle shape;
	char **table;
	size_t h;

	fprin = fscanf(file, "%zd %zd %c\n", &back.w, &back.h, &back.d);
	if (fprin == 3)
	{
		if (back.w <= 0 || back.w > 300 || back.h <= 0 || back.h > 300)
			return (1);
		table = fill_back(back);
		while((fprin = fscanf(file, "%c %f %f %f %c\n", &shape.c, &shape.x, &shape.y, &shape.r, &shape.d)) == 5)
		{
			if ((shape.c == 'c' || shape.c == 'C') && shape.r > 0)
				draw(table, shape);
			else
				return (1);
		}
	}
	if (fprin != -1)
		return (1);
	h = 0;
	while (h < back.h)
	{
		write(1, table[h], back.w);
		write(1, "\n", 1);
		h++;
	}
	return (0);
}


int main(int ac, char **av)
{
	 FILE *file;
	 int ret;

	 if (ac != 2)
	 {
		write(1, "Error: argument\n", 17);
		return (1);
	 }
	 file = fopen(av[1], "r");
	 if (file == NULL)
	 {
		 write(1, "Error: Operation file corrupted\n", 33);
		 return	(1);
	 }
	 ret = execute(file);
	 if (ret == 1)
	 {
		write(1, "Error: Operation file corrupted\n", 32);
		return	(1);
	 }
	 return (ret);
}