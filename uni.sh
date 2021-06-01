./ft_nm $1 > lol; nm $1 > lol2; diff lol lol2
valgrind ./ft_nm $1 1>&-
