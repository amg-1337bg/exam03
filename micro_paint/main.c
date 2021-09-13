#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define file_error "Error: Operation file corrupted\n"
#define argumen_error "Error: argument\n"


typedef struct s_back
{
	int w;
	int h;
	char c;
}	t_back;

typedef struct s_shape
{
	char c;
	float x;
	float y;
	float w;
	float h;
	char d;
}	t_shape;

int ft_strlen(char *s)
{
	int i;

	i = 0;
	while(s[i] != 0)
		i++;
	return (i);
}

char **fill(t_back back)
{
	char **ret;
	int x, y;

	ret = malloc((back.h + 1) * sizeof(char *));
	ret[back.h] = 0;
	y = -1;
	while (++y < back.h)
	{
		x = -1;
		ret[y] = malloc((back.w + 1));
		ret[y][back.w] = 0;
		while (++x < back.w)
			ret[y][x] = back.c;
	}
	return (ret);
}

void draw(char **background, t_back back, t_shape rect)
{
	int x, y;

	y = -1;
	while (++y < back.h)
	{
		x = -1;
		while (++x < back.w)
		{
			if ((rect.x <= x && x <= (rect.x + rect.w)) && (rect.y <= y && y <= (rect.y + rect.h)))
			{
				if (rect.c == 'C')
					background[y][x] = rect.d;
				else
				{
					if (x - rect.x < 1.00000 || (rect.x + rect.w) - x < 1.0000
						|| y - rect.y < 1.0000 || (rect.y + rect.h) - y < 1.0000)
						background[y][x] = rect.d;
				}				
			}
		}
	}
}

int execute(FILE *file)
{
	int scan;
	t_back back;
	t_shape rect;
	char **background;
	int d;

	if (fscanf(file, "%d %d %c\n", &back.w, &back.h, &back.c) != 3)
		return (1);
	if (back.w <= 0 || back.w > 300 || back.h <= 0 || back.h > 300)
		return (1);
	background = fill(back);
	while ((scan = fscanf(file, "%c %f %f %f %f %c\n", &rect.c, &rect.x, &rect.y, &rect.w, &rect.h, &rect.d)) == 6)
	{
		if ((rect.w <= 0 || rect.h <= 0) || (rect.c != 'c' && rect.c != 'C'))
			return (1);
		draw(background, back, rect);
	}
	d = -1;
	while (++d < back.h)
	{
		write(1, background[d], ft_strlen(background[d]));
		write (1, "\n", 1);
	}
	return (0);
}

int main(int ac, char **av)
{
	FILE *file;

	if(ac != 2)
	{
		write(1, argumen_error, ft_strlen(argumen_error));
		return (1);
	}
	file = fopen(av[1], "r");
	if (file == NULL)
	{
		write(1, file_error , ft_strlen(file_error));
		return (1);
	}
	if (execute(file) == 1)
	{
		write(1, file_error , ft_strlen(file_error));
		return (1);
	}
	return (0);
}