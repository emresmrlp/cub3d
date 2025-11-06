#ifndef RAYCAST_H
# define RAYCAST_H

# include "game.h"
# include <math.h>
# include "../external/mlx/mlx.h"

typedef struct s_ray
{
    double  camera_x;    // Kameradaki x koordinatı(-1 ile 1 arası)
    double  ray_dir_x;   // Ray yön vektörü x
    double  ray_dir_y;
    int     map_x;       // Hangi map karesinde
    int     map_y;
    double  first_dist_x; // Ray'in bir sonraki x veya y tarafına uzaklığı
    double  first_dist_y;
    double  routine_dist_x;// Bir x veya y boyunca ray'in kat ettiği mesafe
    double  routine_dist_y;
    double  perp_wall_dist; // Ray'in duvara olan dik mesafesi
    int     step_x;      // X yönünde adım(+1 veya -1)
    int     step_y;
    int     hit;         // Duvar vuruldu mu?
    int     side;        // hangi çizgi üzerine çarptı (0: EW, 1: NS)
	
    double  wall_x;      // Duvarın tam olarak nerede vurulduğu
    int     tex_x;       // Texture'da x koordinatı
}   t_ray;

void	raycast(t_game *game);
void	init_ray(t_game *game, t_ray *ray, int x);
void	dda(t_game *game, t_ray *ray);
void	calculate_wall_distance(t_ray *ray);
void	draw_vertical_line(t_game *game, t_ray *ray, int x);

#endif