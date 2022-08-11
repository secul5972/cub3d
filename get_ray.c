#include "cub3d.h"
#include <stdio.h>

void get_ray(t_cub3d_data *cub)
{
	t_vec ray;
	int	x;
	double	plane;

	/*cub->cdir.x = -1;
	cub->cdir.y = 0;*/
	//plane vector
	plane = 0.66;
	if (cub->cdir.x < 0)
	{
		cub->plane.x = 0;
		cub->plane.y = plane;
	}
	else if (cub->cdir.x > 0)
	{
		cub->plane.x = 0;
		cub->plane.y = -plane;
	}
	else if (cub->cdir.y < 0)
	{
		cub->plane.x = plane;
		cub->plane.y = 0;
	}
	else if (cub->cdir.y > 0)
	{
		cub->plane.x = -plane;
		cub->plane.y = 0;
	}

	x = 0;
	while (x < cub->w_width)
	{
		// ray vector
		//배수
		double multiple = 2 * x / (double)cub->w_width - 1; // -1 <= 2 * x / w < 1
		ray.x = cub->cdir.x + cub->plane.x * multiple;
		ray.y = cub->cdir.y + cub->plane.y * multiple;
		//printf("rayX: %f, rayY: %f\n", ray.x, ray.y);

		//Before DDA
		

		//DDA
		x++;
	}

}