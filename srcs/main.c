#include "got.h"

int	main(void)
{
	t_gmap *gmap;

	gmap = generateBasicGame(4,5,0);
	if (gmap == NULL) return -1;
	gmap->mapbufs[0][0][0] = 1;
	gmap->mapbufs[0][0][2] = 1;
	gmap->mapbufs[0][0][3] = 1;
	gmap->mapbufs[0][1][0] = 1;
	gmap->mapbufs[0][1][1] = 1;
	gmap->mapbufs[0][2][0] = 1;
	gmap->mapbufs[0][2][1] = 1;
	gmap->mapbufs[0][2][3] = 1;
	gmap->mapbufs[0][3][1] = 1;
	gmap->mapbufs[0][3][2] = 1;
	printMap(gmap);
	for (int i = 0; i < 2; i++)
	{
		write(1, "_____\n", 6);
		updateMap(gmap);
		swap_mapbuf(gmap, 0, 1);
		printMap(gmap);
	}
	free_gmap(&gmap);
	return 0;
}
