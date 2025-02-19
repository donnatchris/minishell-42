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

// Function to check is the string is a valid variable name
// Return 1 if the string is valid, 0 if not
int	is_valid_var_name(char *str)
{
    if (!str)
		return (0);
	if (!ft_isalpha(*str) && *str != '_')
        return (0);
    str++;
    while (*str)
    {
        if (!ft_isalphanum(*str) && *str != '_')
			return (0);
		str++;
    }
	return (1);
}

// Function to get the string to manage
// Returns a pointer to the string to manage or NULL on failure


// Function to export variables and store them in the envp
// Returns 0 on success, -1 on failure
int export_cmd(t_token *tok, char **envp)
{
    char    *str;
	int		mem_alloc;

    if (!envp || !tok || tok->type < TOKEN_STRING && tok->type > TOKEN_LITTERAL)
        return (ft_putsrt_fd("export : invalid arguments", 2), -1);
	mem_alloc = 0;
	if (tok->type != TOKEN_LITTERAL)
	{
		str = replace_each_dollar(tok->start, envp);
		if (!str)
			return (-1);
		mem_alloc = 1;
	}
	else
		str = ft_substr(tok->start, 1, tok->end - tok->start - 1);
    
    
}




// POUR INFORMATION:
// Function to update an existing variable in the environment
// Returns 0 on success, -1 on failure
int	update_env_var(const char *key, const char *value, char **envp)
{
	char	**var;
	char	*temp;
	char	*new_entry;

	if (!envp || !key || !value)
		return (ft_putstr_fd("update_env_var: invalid arguments\n", 2), -1);
	var = find_env_var(key, envp);
	if (!var)
		return(create_env_var(key, value, &envp));
	temp = ft_strjoin(key, "=");
	if (!temp)
		return (ft_putstr_fd("update_env_var: strjoin failed\n", 2), -1);
	if (!new_entry)
		return (free(temp), ft_putstr_fd("update_env_var: strjoin failed\n", 2), -1);
	free(temp);
	free(*var);
	*var = new_entry;
	return (0);
}

int	create_env_var(const char *key, const char *value, char ***envp)
{
	char	*temp;
	char	*new_entry;
	char	**new_envp;
	size_t	size;

	if (!envp || !key || !value)
		return (ft_putstr_fd("create_env_var: invalid arguments\n", 2), -1);
	temp = ft_strjoin(key, "=");
	if (!temp)
		return (ft_putstr_fd("create_env_var: strjoin failed\n", 2), -1);
	new_entry = ft_strjoin(temp, value);
	if (!new_entry)
		return (free(temp), ft_putstr_fd("create_env_var: strjoin failed\n", 2), -1);
	free(temp);
	size = count_env_size(*envp);
	new_envp = ft_realloc_env(*envp, size + 1);
	if (!new_envp)
		return (free(new_entry), ft_putstr_fd("create_env_var: realloc failed\n", 2), -1);
	new_envp[size] = new_entry;
	new_envp[size + 1] = NULL;
	*envp = new_envp;
	return (0);
}