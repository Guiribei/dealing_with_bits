#ifndef LABS_H
#define LABS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct s_node
{
	int				freq;
	char			c;
	struct s_node	*left;
	struct s_node	*right;
	struct s_node	*next;
}	t_node;

typedef struct s_list
{
	t_node	*start;
	int		size;
}	t_list;

t_list	*create_list();
void	sorted_insert(t_list *list, t_node *node);
t_node	*create_node(int *freq_table, int *i);
void	fill_list(int *freq_table, t_list *list);
void	print_list(t_list *list);
void	print_tree(t_node *root, int size);
t_node	*build_tree(t_list *list);
t_node	*remove_node(t_list *list);
int		tree_height(t_node *root);
char	**init_dict(int	height);
void	create_dict(char **dict, t_node *root, char *direction, int height);
void	print_dict(char **dict);
void	clear_dict(char **ptrs);
void	lstclear(t_node **lst);
void	free_tree(t_node *tree);
char	*encode(char **dict, char *str);
char	*decode(char *str, char**dict);
char	*compress(char *code);
char	*decompress(char *zip);
//char	*concatenate_strings(char** dict);


#endif