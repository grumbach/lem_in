#ifndef LEM_IN_VIEWER_H
# define LEM_IN_VIEWER_H

# define WIDTH 		1024
# define HEIGHT		632

# define K_A		0
# define K_LEFT		123
# define K_D		2
# define K_RIGHT	124
# define K_S		5//need to check
# define K_DOWN		125
# define K_W		13
# define K_UP		126

# define LEFT		1
# define RIGHT		2
# define DOWN		4
# define UP			8

# define KEYPRESS		2
# define KEYPRESSMASK	(1L << 0)
# define KEYRELEASE		3
# define KEYRELEASEMASK	(1L << 1)

# include "libft.h"//
# include "mlx.h"

typedef struct	s_xy
{
	int			x;
	int			y;
}				t_xy;

/*
** struct for mlx
*/

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			bpp;
	int			endian;
	int			sl;
	t_xy		i;
}				t_mlx;

typedef struct		s_button
{
	int				padding;
}					t_button;
/*
** taking Anselme structure
*/


typedef struct		s_array
{
	void				*content;
	size_t				typesize;
	unsigned long long	arraysize;
}					t_array;

typedef struct		s_ants
{
	t_mlx			*mlx;
	int				ants_nb;
	int				rooms_nb;
	int				maxname;
	int				maxlinks;
	t_xy			max;
	t_xy			min;
	t_xy			dim;
	int				gflag;
	t_button		button;	
	t_xy			room_dim;	
}					t_ants;

typedef struct		s_rooms
{
	char			*roomname;
	int				*links;
}					t_rooms;

typedef struct		s_lem
{
	t_array			*parse;
	t_rooms			*rooms;
}					t_lem;

# define ANTS		t_ants *ants	
# define ROOMS		int	map[ants->dim.y][ants->dim.x]

/*
** mlx functions
*/

int		mlx_loop_hook2(void *mlx_ptr, int (*funct_ptr)(), ANTS, ROOMS);
void	hook_exposure(ANTS);
int		hook(int k, ANTS);
int		hook_move(int k, t_ants *e);

/*
** drawing functions
*/

int		draw_ants(ANTS, ROOMS);
void	draw_rooms(ANTS, ROOMS);
void	draw_room(t_xy pos, ANTS);
void	ft_put_pixel(t_mlx *m, int x, int y, int color);



#endif