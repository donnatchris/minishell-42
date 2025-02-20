/*
La commande export dans un shell Unix ou Linux est utilisée pour définir ou mettre à jour des variables d'environnement.
Voici quelques points clés concernant export :

Définir des variables d'environnement :
Lorsque tu utilises export pour définir une variable, celle-ci devient accessible à tous les processus fils du shell.
Par exemple, si tu exécutes export VAR=value, la variable VAR sera disponible pour les scripts ou les programmes lancés depuis ce shell.

Mettre à jour des variables existantes :
Si la variable d'environnement existe déjà, utiliser export avec la même variable met à jour sa valeur.
Par exemple, export VAR=new_value changera la valeur de VAR à new_value.

Affichage des variables exportées :
Si tu exécutes export sans arguments, cela affichera toutes les variables d'environnement actuellement exportées dans le shell.

ATTENTION:
- export sans argument affiche les variables d'environnement exportées CLASSEES PAR ORDRE ALPHABETIQUE
- export avec un argument affiche la variable d'environnement correspondante
- export avec un argument de la forme "key=value" ajoute la variable d'environnement correspondante
- export avec un argument de la forme "key=" ou "key" met une chaine de caactere vide comme valeur de la variable d'environnement correspondante
- export respecte les tokens string ou littéral ou word (mais en cas de string ou de littéral, enregistre la variable avec guilmlemets)

NOMS DES VARIABLES D'ENVIRONNEMENT:
dans un shell, les noms de variables d'environnement qui peuvent être définis avec export doivent respecter certaines règles :
- Caractères autorisés :
Les noms de variables peuvent contenir des lettres (a-z, A-Z), des chiffres (0-9) et des caractères de soulignement (_).
Cependant, le nom ne doit pas commencer par un chiffre.
- Pas d'espaces : Les noms de variables ne doivent pas contenir d'espaces ou de caractères spéciaux (comme @, $, %, &, etc.).
SINON AFFICHE UN MESSAGE D'ERREUR du type: "bash: export: `nom-de-variable': not a valid identifier"
mais s'il y a plusieurs arguments, affiche le message d'erreur pour chaque argument invalide, mais exécute les arguments valides
*/
#include "../../include/minishell.h"











// Function to find the lowest variable in the environment (alphabetically)
// above the variable passed as an argument
// Returns the address of the variable in the environment or NULL if not found
char	*find_next_lowest_var(char *var, char **envp)
{
	int		i;
	char	*temp;

	if (!envp)
		return (NULL);
	i = 0;
	if (!var)
		var = "";
	temp = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(envp[i])) > 0 && (!temp || ft_strncmp(envp[i], temp, ft_strlen(envp[i])) < 0))
			temp = envp[i];
		i++;
	}
	return (temp);
}

// Function to print characters of a string from pointer start to pointer end
void	print_chars(char *start, char *end)
{
	while (start < end)
	{
		ft_putchar_fd(*start, 1);
		start++;
	}
}

// Function to print all the variables in the environment
// sorted alphabetically
void	print_exp_var_env(char **envp)
{
	char	*var;
	char	*eq;
	char	*value;

	if (!envp)
		return (ft_printf("\n"));
	var = NULL;
	while (1)
	{
		var = find_next_lowest_var(var, envp);
		if (!var)
			break ;
		ft_printf("declare -x ");
		eq = ft_strchr(var, '=');
		if (!eq)
			ft_printf("%s\n", var);
		else
		{
			value = eq + 1;
			print_chars(var, eq);
			ft_printf("=\"%s\"", value);
		}
	}
}







// Function to print error message of export_cmd
// Returns -1
int	print_export_error(char *arg)
{
	ft_putstr_fd("export : `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (-1);
}

// Function to check is the string is a valid variable name
// Return 1 if the string is valid, 0 if not
int	is_valid_var_name(char *str)
{
	if (!str)
		return (0);
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	str++;
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

// Function to export variables and store them in the envp
// or update the value of an existing variable
// or print the value of existing variables in the envp
// Returns 0 on success, -1 on failure
int export_cmd(char **args, char **envp)
{
	int		i;
	char	value;

	if (!envp)
		return (ft_putstr_fd("export_cmd: envp not set\n", 2), -1);	
	if (!args || !*args)
		return (print_exp_var_env(envp), 0);
	i = 0;
	while (args[i])
	{
		if (!is_valid_var_name(args[i]))
			print_export_error(args[i]);
		else
			update_env_var(args[i], ft_strchr(args[i], '='), envp);
		args++;
	}
	return (0);
}




// // POUR INFORMATION:
// // Function to update an existing variable in the environment
// // Returns 0 on success, -1 on failure
// int	update_env_var(const char *key, const char *value, char **envp)
// {
// 	char	**var;
// 	char	*temp;
// 	char	*new_entry;

// 	if (!envp || !key || !value)
// 		return (ft_putstr_fd("update_env_var: invalid arguments\n", 2), -1);
// 	var = find_env_var(key, envp);
// 	if (!var)
// 		return(create_env_var(key, value, &envp));
// 	temp = ft_strjoin(key, "=");
// 	if (!temp)
// 		return (ft_putstr_fd("update_env_var: strjoin failed\n", 2), -1);
// 	if (!new_entry)
// 		return (free(temp), ft_putstr_fd("update_env_var: strjoin failed\n", 2), -1);
// 	free(temp);
// 	free(*var);
// 	*var = new_entry;
// 	return (0);
// }

// int	create_env_var(const char *key, const char *value, char ***envp)
// {
// 	char	*temp;
// 	char	*new_entry;
// 	char	**new_envp;
// 	size_t	size;

// 	if (!envp || !key || !value)
// 		return (ft_putstr_fd("create_env_var: invalid arguments\n", 2), -1);
// 	temp = ft_strjoin(key, "=");
// 	if (!temp)
// 		return (ft_putstr_fd("create_env_var: strjoin failed\n", 2), -1);
// 	new_entry = ft_strjoin(temp, value);
// 	if (!new_entry)
// 		return (free(temp), ft_putstr_fd("create_env_var: strjoin failed\n", 2), -1);
// 	free(temp);
// 	size = count_env_size(*envp);
// 	new_envp = ft_realloc_env(*envp, size + 1);
// 	if (!new_envp)
// 		return (free(new_entry), ft_putstr_fd("create_env_var: realloc failed\n", 2), -1);
// 	new_envp[size] = new_entry;
// 	new_envp[size + 1] = NULL;
// 	*envp = new_envp;
// 	return (0);
// }