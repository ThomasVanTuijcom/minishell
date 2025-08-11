# A fixer


echo "H'"o'"""" (fix normalement)
--------------------------------------------------------
Export var= (fix normalement)
Export var+=lol (fix normalement)
--------------------------------------------------------
Echo > blablabla | echo test >> out >> file (fix normalement)
--------------------------------------------------------
Echo > test | echo > test2 (fix normalement)
--------------------------------------------------------
Echo hello | echo > a >> a (fix normalement)
--------------------------------------------------------
cat > a << eof --> segmentation fault
--------------------------------------------------------
cat << "end"

Si il y a des guillemets n'expand pas
--------------------------------------------------------
Cat << $PWD

On doit pas écrire $PWD mais la valeur expand
--------------------------------------------------------
Fichier qui reste ouvert après des pipes/execution de certaines commandes
--------------------------------------------------------
cat << e << t | cat << ty (fix normalement)
--------------------------------------------------------
Signals dans heredoc
--------------------------------------------------------
valgrind --show-leak-kinds=all --leak-check=full --track-origins=yes --trace-children=yes --track-fds=yes --suppressions=readline.supp -s ./minishell
