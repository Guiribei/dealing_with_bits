/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huffman.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:45:35 by guribeir          #+#    #+#             */
/*   Updated: 2023/01/13 22:30:21 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "labs.h"

char	*read_file(int fd)
{
	char	*str;
	char	buf[1];
	int		i;

	str = NULL;
	i = 0;
	while (read(fd, buf, 1))
		i++;
	str = calloc(1, i + 1);
	close(fd);
	open("infile.txt", O_RDWR);
	read(fd, str, i);
	str[i] = '\0';
	return (str);
}

int	*count_sym(char *str)
{
	int	*freq_table;
	int	i;

	freq_table = calloc(128, sizeof(int));
	i = 0;
	while (i < 128)
		freq_table[i++] = 0;
	i = 0;
	while (str[i])
	{
		freq_table[(int)(str[i])]++;
		i++;
	}
	return (freq_table);
}

void	clean_quit(char **dict, t_list *list, t_node *tree, int *freq_table, char *str, char *code)
{
	clear_dict(dict);
	free(list);
	free_tree(tree);
	free(freq_table);
	free(str);
	free(code);
}

int main(void)
{
	char	*str;
	int		*freq_table;
	t_list	*list;
	t_node	*tree;
	int		height;
	char	**dict;
	char	*code;
	char	*bin;
	char	*new_code;
	//char	*new_str;
	
	str = read_file(open("infile.txt", O_RDWR));
	freq_table = count_sym(str);
	list = create_list();
	fill_list(freq_table, list);
	tree = build_tree(list);
	height = tree_height(tree);
	dict = init_dict(height + 1);
	create_dict(dict, tree, "", height);
	code = encode(dict, str);
	printf("\nA string codificada é: %s\n", code);
	bin = compress(code);
	printf("\nA string compactada é: %s\n", bin);
	new_code = decompress(bin);
	printf("\nA string descompactada é: %s\n", new_code);
	//new_str = decode(new_code, dict);
	//printf("\nA string decodificada é: %s\n", new_str);
	clean_quit(dict, list, tree, freq_table, str, code);
	return 0;
}
