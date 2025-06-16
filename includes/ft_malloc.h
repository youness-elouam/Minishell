#ifndef FT_MALLOC_H
# define FT_MALLOC_H

#include <stdio.h>

void	*ft_malloc(size_t size);
void	ft_free(void *s);

typedef struct s_malloc
{
	void	*ptr;
	struct s_malloc	*next;
}	t_malloc;

#endif