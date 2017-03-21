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
}				t_mlx;

typedef struct		s_param
{
	t_xy			padding;
	double			scaling;
}					t_param;

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
	t_param			param;	
	t_xy			room_dim;
	int				room_size;
	void			*map_pointer;
	void			*rooms_pointer;
}					t_ants;

typedef struct		s_rooms
{
	char			*roomname;
	int				*links;
	t_xy			pos;
	int				type;
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

void	hook_exposure(ANTS);
int		hook(int k, ANTS);
int		hook_move(int k, t_ants *e);

/*
** parsing (less strict as data has already been fully checked)
*/

void	parse_first_line(t_ants *ants);
void	parse_rooms(t_ants *ants, char name[ants->rooms_nb][ants->maxname + 1],
			t_rooms rooms[ants->rooms_nb]);
void	parse_links(t_ants *ants, t_rooms rooms[ants->rooms_nb], char *line,
			int room_index);

/*
** drawing functions
*/

void	init_rooms(t_ants *ants);
int		draw_ants(ANTS);
void	draw_rooms(ANTS);
void	draw_room(ANTS, void *rooms, int index);
void	ft_put_pixel(t_mlx *m, int x, int y, int color);

/*
**
*/

void	reset_controls(t_param *param);



#endif
