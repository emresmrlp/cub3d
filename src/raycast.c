/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysumeral <ysumeral@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 07:52:03 by zulfiye           #+#    #+#             */
/*   Updated: 2025/11/21 19:42:57 by ysumeral         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// DDA algoritması

#include "../include/raycast.h"

//Örnek ray hesaplaması
//Ekranın Solu (camera_x = -1): ray = (1, 0) + (0, 0.5) * -1 = (1, -0.5)
//Ekranın Sağı (camera_x = +1): ray = (1, 0) + (0, 0.5) * +1 = (1, 0.5)
void init_ray(t_game *game, t_ray *ray, int x)
{
    // Kamera x koordinatını hesapla (-1 sol, 1 sağ)
    ray->camera_x = 2 * x / (double)SIZE_X - 1;
    
    // Ray yönü formülü / hangi yöne bakacağı
	// karakterin baktığı yön + Kameranın sağ-sol genişliği * -1 ile +1 arasındaki oran (x)
    ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
    ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
    
    // Hangi map karesinde olduğumuzu belirle
    ray->map_x = (int)game->player.pos_x;
    ray->map_y = (int)game->player.pos_y;
    if (ray->ray_dir_x == 0)
        ray->routine_dist_x = INFINITY;
    else
        ray->routine_dist_x = fabs(1 / ray->ray_dir_x);
    
    if (ray->ray_dir_y == 0)
        ray->routine_dist_y = INFINITY;
    else
        ray->routine_dist_y = fabs(1 / ray->ray_dir_y);
    
    ray->hit = 0;
    if (ray->ray_dir_x < 0)
    {
        ray->step_x = -1;
        ray->first_dist_x = (game->player.pos_x - ray->map_x) * ray->routine_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->first_dist_x = (ray->map_x + 1.0 - game->player.pos_x) * ray->routine_dist_x;
    }
    
    if (ray->ray_dir_y < 0)
    {
        ray->step_y = -1;
        ray->first_dist_y = (game->player.pos_y - ray->map_y) * ray->routine_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->first_dist_y = (ray->map_y + 1.0 - game->player.pos_y) * ray->routine_dist_y;
    }
}

void dda(t_game *game, t_ray *ray)
{
    // DDA algoritması ile duvara kadar ilerle
    while (ray->hit == 0)
    {
        // Bir sonraki map karesine atla
        if (ray->first_dist_x < ray->first_dist_y)
        {
            ray->first_dist_x += ray->routine_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0; // EW duvarı
        }
        else
        {
            ray->first_dist_y += ray->routine_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1; // NS duvarı
        }
        
        // Duvara çarptık mı kontrol et
        if (game->map.map[ray->map_y][ray->map_x] == '1')
            ray->hit = 1;
    }
}

void calculate_wall_distance(t_ray *ray)
{
    // Duvarın oyuncuya olan dik mesafesini hesapla (fishbowl effect'ten kaçınmak için)
    if (ray->side == 0)
        ray->perp_wall_dist = (ray->first_dist_x - ray->routine_dist_x);
    else
        ray->perp_wall_dist = (ray->first_dist_y - ray->routine_dist_y);
}

static void *get_texture(t_game *game, t_ray *ray)
{
    
    if (ray->side == 0)
    {
        if (ray->ray_dir_x > 0)
            return (game->texture.ea_wall); //doğu
        else
            return (game->texture.we_wall); //batı
    }
    else
    {
        if (ray->ray_dir_y > 0)
            return (game->texture.so_wall); //güney
        else
            return (game->texture.no_wall); //kuzey
    }
}

static void calculate_texture_x(t_game *game, t_ray *ray)
{
    // Duvarda ray'in çarptığı tam konumu hesapla
    if (ray->side == 0)
        ray->wall_x = game->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
    else
        ray->wall_x = game->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
    ray->wall_x -= floor(ray->wall_x);
    
    // Texture'ın x koordinatını hesapla
    ray->tex_x = (int)(ray->wall_x * (double)game->texture.img_width);
    
    // Texture'ı düzgün yöne çevir
    if (ray->side == 0 && ray->ray_dir_x < 0)
        ray->tex_x = game->texture.img_width - ray->tex_x - 1;
    if (ray->side == 1 && ray->ray_dir_y > 0)
        ray->tex_x = game->texture.img_width - ray->tex_x - 1;
}

void draw_vertical_line(t_game *game, t_ray *ray, int x)
{
    int     line_height;
    int     draw_start;
    int     draw_end;
    int     y;
    void    *texture;
    char    *tex_data;
    int     tex_bpp;
    int     tex_line;
    int     tex_endian;
    
    texture = get_texture(game, ray);
    if (!texture)
        return;
    tex_data = mlx_get_data_addr(texture, &tex_bpp, &tex_line, &tex_endian);
    if (!tex_data)
        return;
    
    // Texture x koordinatının hesabı
    calculate_texture_x(game, ray);
    
    // Çizgi yüksekliğinin hesabı
    line_height = (int)(SIZE_Y / ray->perp_wall_dist);
    
    // Çizginin başlangıç ve bitiş noktalarının hesabı
    draw_start = -line_height / 2 + SIZE_Y / 2;
    if (draw_start < 0)
        draw_start = 0;
    
    draw_end = line_height / 2 + SIZE_Y / 2;
    if (draw_end >= SIZE_Y)
        draw_end = SIZE_Y - 1;
    
    // Tavanı çiz 
    y = 0;
    while (y < draw_start)
    {
        int ceiling_color = (game->texture.ceiling_color[0] << 16) | 
                           (game->texture.ceiling_color[1] << 8) | 
                           game->texture.ceiling_color[2];
        char *pixel = game->texture.addr + (y * game->texture.x_byte + x * 4);
        *(unsigned int *)pixel = ceiling_color;
        y++;
    }
    
    // Duvarı texture ile çiz
    y = draw_start;
    while (y < draw_end)
    {
        int tex_y;
        int color;
        
        // Texture'ın y koordinatını hesapla
        tex_y = (int)((y - SIZE_Y / 2 + line_height / 2) * game->texture.img_height / line_height);
        if (tex_y < 0)
            tex_y = 0;
        if (tex_y >= game->texture.img_height)
            tex_y = game->texture.img_height - 1;
        
        // Texture'dan rengi al
        color = *(int *)(tex_data + (tex_y * tex_line + ray->tex_x * (tex_bpp / 8)));
        
        // Pixel'i çiz
        char *pixel = game->texture.addr + (y * game->texture.x_byte + x * 4);
        *(unsigned int *)pixel = color;
        y++;
    }
    
    // Zemini çiz (floor color)
    y = draw_end;
    while (y < SIZE_Y)
    {
        int floor_color = (game->texture.floor_color[0] << 16) | 
                         (game->texture.floor_color[1] << 8) | 
                         game->texture.floor_color[2];
        char *pixel = game->texture.addr + (y * game->texture.x_byte + x * 4);
        *(unsigned int *)pixel = floor_color;
        y++;
    }
}

void raycast(t_game *game)
{
    t_ray ray;
    int x;
    
    x = 0;
    while (x < SIZE_X)
    {
        init_ray(game, &ray, x);
        dda(game, &ray);
        calculate_wall_distance(&ray);
        draw_vertical_line(game, &ray, x);
        x++;
    }
}