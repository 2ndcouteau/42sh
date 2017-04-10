#include "shell.h"

int *new_indexes(int i0, int i1)
{
  int *idxs;

  if ((idxs = (int*)malloc(sizeof(int) * 2)) == NULL)
    return (NULL);
  idxs[0] = i0;
  idxs[1] = i1;
  return (idxs);
}

int **new_itab(int i0, int i1)
{
  int **itab;

  if ((itab = (int**)malloc(sizeof(int*) * 2)) == NULL)
    return (NULL);
  itab[1] = NULL;
  if ((itab[0] = new_indexes(i0, i1)) == NULL)
  {
    free(itab);
    return (NULL);
  }
  return (itab);
}

size_t  itab_len(int **itab)
{
  size_t i;

  if (itab == NULL || *itab == NULL)
    return (0);
  i = 0;
  while (itab[i])
      i++;
  return (i);
}

void	itab_del(int ***itab)
{
	size_t	len;
	size_t	i;

	if (!itab || !*itab)
		return ;
	len = itab_len(*itab);
	i = 0;
	while (i < len)
	{
		free((*itab)[i]);
		i++;
	}
	free(*itab);
	*itab = NULL;
}

int itab_push(int ***itab, int i0, int i1)
{
  size_t  i;
  size_t  len;
  int     **newone;

  if (*itab == NULL)
    *itab = new_itab(i0, i1);
  else
  {
    i = 0;
    len = itab_len(*itab) + 1;
    if ((newone = (int**)malloc(sizeof(int*) * len * 2)) == NULL)
      return (-1);
    newone[len] = NULL;
    while (i < len)
    {
      if (i == len - 1)
        newone[i] = new_indexes(i0, i1);
      else
      {
		newone[i] = new_indexes((*itab)[i][0], (*itab)[i][1]);
		//free((*itab)[i]);
		}
      i++;
    }
    //free((*itab));
	itab_del(itab);
    *itab = newone;
  }
  return (0);
}


void test_idx(t_shell *sh, int ac, char **av, char **env)
{
  int *i;

  (void)sh;(void)ac;(void)av;(void)env;
  if ((i = new_indexes(0, 33)) != NULL)
    ft_printf("[%d:%d]\n", i[0], i[1]);

  int **itab = new_itab(16,22);
  if (*itab != NULL)
    ft_printf("[%d:%d](%zu)\n", itab[0][0], itab[0][1], itab_len(itab));

  itab_push(&itab, 0, 0);
  int j=0;
  int si=itab_len(itab);
  while (j < si)
  {
    ft_printf("(%d)[%d:%d](%zu)\n", j, itab[j][0], itab[j][1], si);
    j++;
  }
}
