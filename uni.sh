./ft_nm $* > .lol; nm $* > .lol2; diff .lol .lol2
valgrind ./ft_nm $* 1>&-
