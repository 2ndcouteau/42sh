// #include "shell.h"
//
// char *ft_getbranch(void)
// {
// 	int fd;
// 	char *line;
// 	char *branche;
//
// 	fd = 0;
// 	if (!(fd = open("./.git/HEAD", O_RDONLY)))
// 		return (NULL);
// 	get_next_line(fd, &line);
// 	if (fd)
// 		close(fd);
// 	if (line && (branche = ft_strrchr(line, '/')))
// 		return (ft_strdup(branche + 1));
// 	else
// 		return (NULL);
// }
