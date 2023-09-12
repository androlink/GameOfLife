#ifndef GOT_H
# define GOT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef unsigned short t_ushort;

typedef struct s_gmap
{
	t_ushort ***mapbufs;
	int bufsize;
	int height;
	int width;
	char dead;
	char alive;
	int rule[2][8];
	t_ushort wall;
}	t_gmap;

t_gmap *generateBasicGame(int width, int height, int prop);
int updateMap(t_gmap *gmap);
void    free_gmap(t_gmap **gmap);
void init_rule_game(t_gmap *gmap, int death_rule[8], int live_rule[8]);
void randomMapFill(t_gmap *gmap, int prop);
int count_adj(t_gmap *gmap, int x, int y);
void printMap(t_gmap *gmap);
void swap_mapbuf(t_gmap *gmap, int i, int j);

#endif
