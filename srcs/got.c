#include "got.h"

void printMap(t_gmap *gmap)
{
	int j, i;

	j = 0;
	while (j < gmap->height)
	{
		i = 0;
		while (i < gmap->width)
		{
			if (gmap->mapbufs[0][j][i])
				write(1, &gmap->alive, 1);
			else
				write(1, &gmap->dead, 1);
			i++;
		}
		write(1, "\n", 1);
		j++;
	}
}
void	free_mapbuf(t_ushort ***mapbuf, int h)
{
	int i;
	if (mapbuf && *mapbuf)
	{
		i = 0;
		while (i < h && (*mapbuf)[i])
		{
			fprintf(stderr, "\tfree line %d/%d\n",i,h);
			free((*mapbuf)[i]);
			(*mapbuf)[i] = NULL;
			i++;
		}
		free(*mapbuf);
		*mapbuf = NULL;
	}
}
void	free_gmap(t_gmap **gmap)
{
	int i;
	if (gmap && *gmap)
	{
		i = 0;
		while (i < (*gmap)->bufsize && (*gmap)->mapbufs[i])
		{
			fprintf(stderr, "free buffer %d/%d\n",i, (*gmap)->bufsize);
			free_mapbuf(&((*gmap)->mapbufs[i]), (*gmap)->height);
			i++;
		}
		free((*gmap)->mapbufs);
		free(*gmap);
		*gmap = NULL;
	}
}

void init_rule_game(t_gmap *gmap, int death_rule[8], int live_rule[8])
{
	int i;

	i=0;
	while (i < 8)
	{
		gmap->rule[0][i] = death_rule[i];
		gmap->rule[1][i] = live_rule[i];
		i++;
	}
}

void randomMapFill(t_gmap *gmap, int prop)
{
	int i, j;

	j = 0;
	while (j < gmap->height)
	{
		i = 0;
		while (i < gmap->width)
		{
			gmap->mapbufs[0][j][i] = (rand()%100) < prop;
			i++;
		}
		j++;
	}
}

t_ushort **init_mapbuf(int width, int height)
{
	t_ushort **map;
	int i;

	map = malloc(sizeof(t_ushort *) * height);
	if (map == NULL) return NULL;
	i = 0;
	while (i < height && map)
	{
		map[i] = malloc(sizeof(t_ushort *) * width);
		if(map[i] == NULL) free_mapbuf(&map, height);
		i++;
	}
	return map;
}

t_gmap *generateBasicGame(int width, int height, int prop)
{
	t_gmap *gmap;
	int i;
	int bufsize = 2;

	gmap = malloc(sizeof(t_gmap));
	if (gmap == NULL) return NULL;
	gmap->height = height;
	gmap->width = width;
	gmap->bufsize = bufsize;
	gmap->mapbufs = (t_ushort ***) malloc(sizeof(t_ushort **) * bufsize);
	i = 0;
	while (gmap && i < bufsize)
	{
		gmap->mapbufs[i] = init_mapbuf(width, height);
		if (gmap->mapbufs[i] == NULL) free_gmap(&gmap);
		i++;
	}
	if (gmap == NULL) return NULL;
	gmap->dead = '.';
	gmap->alive = '#';
	init_rule_game(gmap, (int [8]){0,0,1,1,0,0,0,0}, (int [8]){0,0,0,1,0,0,0,0});
	gmap->wall=0;
	randomMapFill(gmap, prop);
	return gmap;
}
int count_adj(t_gmap *gmap, int x, int y)
{
	int count;
	int i, j;

	count = 0;
	j = y-1;
	while (j <= y+1)
	{
		//fprintf(stderr, "\t");
		i = x-1;
		while (i <= x+1)
		{
			if (!(i == x && j == y))
			{
				if (((i < 0  || j < 0) && gmap->wall)
					|| ((i >= gmap->width || j >= gmap->height) && gmap->wall)
					|| ((i >= 0 && j >= 0 && i < gmap->width 
							&& j < gmap->height) && gmap->mapbufs[0][j][i]))
				{
					count++;
					//fprintf(stderr, "#");
				} else {
					
					//fprintf(stderr, "%d", (j - y + 1) * 3 + (i - x + 1));
				}
			} else {
				//fprintf(stderr, "X");
			}
			i++;
		}
		//fprintf(stderr, "\n");
		j++;
	}

	return count;
}

void swap_mapbuf(t_gmap *gmap, int i, int j)
{
	t_ushort **tmp;

	tmp = gmap->mapbufs[i];
	gmap->mapbufs[i] = gmap->mapbufs[j];
	gmap->mapbufs[j] = tmp;
}

int updateMap(t_gmap *gmap)
{
	int i, j;
	int count;
	j = 0;
	while (j < gmap->height)
	{
		i = 0;
		while (i < gmap->width)
		{
			count = count_adj(gmap, i, j);
			//fprintf(stderr, "adj count for %d|%d : %d\n", i, j, count);
			if (gmap->mapbufs[0][j][i])
			{
				if (!gmap->rule[0][count])
					gmap->mapbufs[1][j][i] = 0;
				else
					gmap->mapbufs[1][j][i] = gmap->mapbufs[0][j][i];
			} else {
				if (gmap->rule[1][count])
					gmap->mapbufs[1][j][i] = 1;
				else
					gmap->mapbufs[1][j][i] = gmap->mapbufs[0][j][i];
			}
			i++;
		}
		j++;
	}
	return 1;
}
