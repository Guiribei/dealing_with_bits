/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guribeir <guribeir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:41:18 by ridalgo-          #+#    #+#             */
/*   Updated: 2023/01/15 14:15:18 by guribeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "huffman.h"

void	clean_quit(t_data *data)
{
	clear_dict(data->dict);
	free(data->list);
	free_tree(data->tree);
	free(data->freq_table);
	free(data->text);
	free(data->code);
	free(data->bin);
}

int	main(void)
{
	t_data	*data;
	clock_t    start;
    clock_t    end;
    double    runtime;
    
    start = clock();
	data = (t_data *)calloc(1, sizeof(t_data));
	data->text = read_file(open("infile.txt", O_RDWR));
	if (strlen(data->text) == 0)
		return (0);
	data->freq_table = count_sym(data->text);
	data->list = create_list();
	fill_list(data->freq_table, data->list);
	data->tree = build_tree(data->list);
	data->height = tree_height(data->tree);
	data->dict = init_dict(data->height + 1);
	create_dict(data->dict, data->tree, "", data->height);
	data->code = encode(data->dict, data->text);
	data->bin = compress(data->code);
	encoder_shm(data);
	printf("Total bytes compressed:\t%lu\n", strlen(data->text));
	clean_quit(data);
	free(data);
	end = clock();
    runtime = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Total time:\t%gs\n", runtime);
	return (0);
}
