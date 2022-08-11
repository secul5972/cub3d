#include "cub3d.h"

void fix_map_find_pos(t_cub3d_data *cub)
{
    char **map;

    int i;
    int j;

    map = (char **)malloc(sizeof(char *) * cub->m_height);

    i = 1;
    while (i < cub->m_height + 1)
    {
        j = 1;
        map[i - 1] = (char *)malloc(sizeof(char ) * cub->m_width);
        while (j < cub->m_width + 1)
        {
            map[i - 1][j - 1] = cub->map[i][j];
            if (cub->map[i][j] == '1' || cub->map[i][j] == '0' || cub->map[i][j] == ' ')
            {
                j++;
                continue;
            }
            make_vec(&cub->cpos, j - 1, i - 1);
            if (cub->map[i][j] == 'N')
                make_vec(&cub->cdir, 0, -1);
            if (cub->map[i][j] == 'S')
                make_vec(&cub->cdir, 0, 1);
            if (cub->map[i][j] == 'W')
                make_vec(&cub->cdir, -1, 0);
            if (cub->map[i][j] == 'E')
                make_vec(&cub->cdir, 1, 0);
            j++;
        }
        free(cub->map[i]);
        i++;
    }
    free(cub->map);
    cub->map = map;
}