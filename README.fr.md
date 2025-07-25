# PROJET MINISHELL POUR 42
Par chdonnat (Christophe Donnat de 42 Perpignan, France)

[🇬🇧 Go to English version](README.md)

![tests](images/test_minishell.png)

## BUT DU PROJET :

L'objectif du projet est de créer un shell simplifié qui imite fidèlement le comportement de `bash`. Cela inclut la gestion de l'analyse syntaxique, des redirections, des pipes, des signaux et de l'exécution des commandes via `execve()`, à l'exception des commandes intégrées (built-in), qui doivent être codées directement dans minishell.

### PARTIE BONUS :

Pour obtenir des points bonus, le shell doit gérer :
- Les opérateurs logiques : `&&` (ET) et `||` (OU).
- Les parenthèses `()` pour le groupement de commandes.
- Les wildcards `*` pour l'expansion des noms de fichiers.

### Minishell et les fuites de mémoire
Il est crucial de gérer attentivement les fuites de mémoire et la fermeture des descripteurs de fichiers dans un projet comme Minishell. Le Makefile inclut deux options pour aider à surveiller les fuites :
- Sur macOS : La compilation utilise automatiquement l'outil fsanitize. Cependant, sachez que fsanitize est beaucoup moins précis que valgrind.
- Sur Linux : Le Makefile inclut une règle `make val` qui exécute le programme sous valgrind, tout en ignorant les fuites causées par la fonction `readline()` à l'aide du fichier de suppression `valgrind.sup`.

## QUELQUES COMMANDES UTILES :

Compiler le programme et supprimer les fichiers .o :

	make && make clean

Exécuter le programme :

	./minishell

Exécuter le programme avec valgrind en excluant les fuites de `readline()` :

 (ceci utilise le fichier `valgrind.sup` pour supprimer les fuites de `readline()`)

	make val

## ARCHITECTURE :
- Répertoire `minishell/` avec l'ensemble du projet
	- Répertoire `libft/` avec la libft (+ get_next_line et ft_printf)
 	- Répertoire `dclst/` avec les fonctions et le header pour utiliser des listes doublement chaînées circulaires
	- Répertoire `bonus/` avec les fichiers pour la partie bonus
		- Répertoire `src/` contenant les fichiers principaux du projet
  			- `builtins/` : fichiers pour les commandes intégrées
     		- `env/` : fichiers avec les fonctions nécessaires pour interagir avec les variables d'environnement
        	- `executor/` : fichiers pour exécuter la ligne de commande
          	- `lexer/` : fichiers pour diviser l'entrée utilisateur en tokens, les stocker dans une liste chaînée, vérifier la syntaxe et créer un arbre binaire
            - `signals/` : fichiers pour la gestion des signaux
          	- `text_transformer/` : fichiers pour la gestion de '$', '*' et '~'
		- Répertoire `utils/` pour les fichiers secondaires
		- Répertoire `include/` pour les en-têtes
	- Répertoire `mandatory/` pour la partie obligatoire (vide - tout est dans le répertoire bonus)
- `Makefile` (avec les règles : make bonus clean fclean re)
- `readme.md` pour une explication rapide et les commandes principales du projet
- `valgrind.sup` est un fichier contenant une liste de fuites de `readline()` à supprimer lors de l'exécution de valgrind

## À PROPOS DE MON PROJET :

Ce projet minishell a été implémenté avec les bonus et plusieurs fonctionnalités qui ne sont pas obligatoires selon le sujet.

Comme pour mes projets précédents, j'ai utilisé des fonctions pour manipuler des listes circulaires doublement chaînées (que j'ai créées lors du projet FDF), bien que l'utilisation d'une liste linéaire aurait pu être plus simple. Toutes les fonctions de manipulation de ces listes se trouvent dans le dossier `/dclst`.
Voici un aperçu du fonctionnement du projet :

---

#### **Structure générale :**
Une fois le programme lancé, une structure générale est initialisée. Cette structure contient la plupart des éléments et sera entièrement libérée à la fin du programme, même si de nombreux éléments seront réinitialisés à chaque entrée de l'utilisateur.
Au démarrage, la structure alloue dynamiquement et stocke une copie des variables d'environnement (tout en mettant à jour les variables `SHLVL` et `SHELL`). Cette copie est utilisée pour la gestion des variables d'environnement tout au long de l'exécution de minishell.

---

#### **LEXER :**
Une fois l'entrée utilisateur enregistrée, elle est divisée en différents tokens, stockés dans des structures (organisées en listes chaînées). Chaque token contient une partie de la chaîne de caractères de l'utilisateur, ainsi que des informations supplémentaires (par exemple, le type de token, s'il y a un espace après le token, s'il est entouré de guillemets simples ou doubles, et si la chaîne a été allouée dynamiquement).

Pour les tokens, j'ai cherché à travailler uniquement avec des pointeurs référençant des parties de la chaîne d'entrée pour éviter d'allouer dynamiquement de la mémoire pour les fragments de chaîne stockés dans les tokens. Cependant, cet effort s'est avéré quelque peu inutile plus tard dans le programme. Plus précisément, lors de la gestion des wildcards, je crée de nouveaux tokens avec des chaînes allouées dynamiquement, c'est pourquoi j'ai dû ajouter un drapeau pour déterminer quelles chaînes libérer plus tard. Néanmoins, cette approche reste intéressante pour ceux qui ne prévoient pas de mettre en œuvre les bonus du projet.

Une fois la liste de tokens créée, sa syntaxe est validée dans la fonction `check_syntax`. Si l'entrée se termine par `||`, `&&` ou `|`, une invite supplémentaire est ouverte pour que l'utilisateur complète son entrée. Si la syntaxe de l'entrée est invalide, un message d'erreur est affiché.

La liste de tokens est ensuite passée à une fonction qui crée un **arbre binaire** en parcourant la liste de droite à gauche, à la recherche d'opérateurs comme `||`, `&&`, `|` ou `;`. Chaque opérateur pointe vers ses parties gauche et droite, et l'arbre est construit récursivement jusqu'à atteindre les feuilles. Chaque feuille pointe simplement vers le token le plus à gauche entre les opérateurs. L'arbre binaire n'est pas nécessaire si vous ne prévoyez pas de faire la partie bonus.

---

#### **EXECUTOR :**
L'exécuteur parcourt l'arbre binaire dans la fonction `exec_tree`. S'il rencontre une feuille, il l'exécute. S'il rencontre un opérateur, il exécute les parties gauche et droite (sous certaines conditions). L'opérateur pipe est plus complexe car il doit créer des heredocs s'ils sont trouvés dans ses branches enfants avant de créer le pipe (alors que les heredocs sont normalement créés lors de l'exécution des feuilles s'il n'y a pas de pipes).

Lorsque l'exécuteur atteint une feuille, la fonction `exec_leaf()` traite les redirections d'entrée et de sortie de gauche à droite, puis passe à la fonction `exec_cmd`, qui crée un tableau de chaînes de caractères via la fonction `extract_args` (les arguments sont d'abord traités dans les fonctions TEXT TRANSFORMER pour remplacer les caractères si nécessaire). Ce tableau contient la commande et ses arguments. En fonction du premier argument du tableau (le nom de la commande), le tableau est envoyé à la fonction appropriée : si la commande correspond à un builtin (les quelques commandes codées dans minishell), la fonction correspondante est appelée avec le tableau comme argument ; sinon, la fonction `execve_cmd` est appelée.

La fonction `execve_cmd()` vérifie si la commande se trouve dans l'un des répertoires listés dans la variable d'environnement `PATH`, puis exécute la commande dans un processus enfant via `execve()`. Si la commande n'est pas trouvée, un message d'erreur est affiché.

Les parenthèses sont à la fois un token et un type spécial de feuille dans l'arbre : le contenu entre parenthèses est traité récursivement dans un sous-shell exécuté dans un processus enfant. Le contenu entre parenthèses est tokenisé par le lexer puis exécuté par l'exécuteur.

Comme vous pouvez le voir, je n'ai pas vraiment implémenté d'analyse syntaxique traditionnelle. Au lieu de cela, la fonction exécutant la feuille et celle créant le tableau d'arguments sont responsables de naviguer correctement dans la liste de tokens pour trouver les redirections et les arguments appropriés.
Les fonctions d'exécution des redirections, des parenthèses et des pipes se trouvent dans le dossier "OPERATORS".

---

#### **TEXT TRANSFORMER :**
Lors de la création du tableau d'arguments, les chaînes contenues dans les tokens passent par la fonction `manage_dollar()`, qui renvoie une chaîne allouée dynamiquement après avoir remplacé `$` par la valeur de la variable d'environnement correspondante (si elle existe ; sinon, elle est remplacée par une chaîne vide).

Dans le gestionnaire de dollar, j'ai également ajouté la prise en charge de `~` (qui n'est pas requise par le sujet) : si une chaîne ne contient que le symbole `~` ou commence par `~/`, ce caractère est remplacé par le chemin absolu du répertoire personnel de l'utilisateur (je stocke la valeur de la variable `HOME` dans la structure générale au démarrage de minishell, ce qui signifie que si cette valeur est modifiée avant de lancer minishell, `~` ne fonctionnera pas correctement).

Le transformateur de texte comprend également des fonctions pour gérer les wildcards : d'abord, un tableau de chaînes contenant les noms des fichiers et des répertoires du répertoire courant est créé. Ensuite, chaque entrée est comparée à l'entrée pour trouver des correspondances pour le joker, et un nouveau tableau de chaînes est créé avec chaque entrée correspondante. Sur la base de ce tableau, de nouveaux tokens sont créés et insérés dans la liste de tokens.

Pour les redirections d'entrée ou de sortie, le programme vérifie d'abord si plus d'un nom de fichier ou de répertoire correspond au joker. Si c'est le cas, un message d'erreur est affiché.

---

#### **BUILTINS :**
Les builtins sont les commandes directement codées dans minishell.

### **cd :**
J'ai choisi d'implémenter des arguments non obligatoires, tels que :
- `cd ~` (change pour le répertoire personnel de l'utilisateur),
- `cd -` (revient au répertoire de travail précédent),
- `cd` sans arguments (change pour le répertoire personnel).

Une fois le répertoire de travail changé, les variables d'environnement `PWD` et `OLDPWD` sont mises à jour.

### **pwd :**
Affiche simplement le répertoire de travail actuel.

### **env :**
Affiche le tableau des variables d'environnement, à l'exclusion des variables sans valeur (celles enregistrées sans `=`).
**Note :**
Les fonctions pour manipuler les variables d'environnement (nécessaires pour `export`, `unset`, `cd`, ...) se trouvent dans le répertoire `ENV`.

### **export :**
Lorsqu'elle est utilisée sans arguments, la commande `export` affiche les variables d'environnement triées par ordre alphabétique (y compris celles sans valeur associée) dans un format spécifique.
Lorsqu'elle est utilisée avec des arguments, elle ajoute de nouvelles variables d'environnement ou met à jour la valeur de celles qui existent déjà, après avoir vérifié que le nom de la variable respecte certaines règles :
- Le premier caractère du nom doit être une lettre ou `_`.
- Les caractères suivants doivent être alphanumériques ou `_`.

**Note :**
Les variables sont stockées au format suivant : `NOM=VALEUR`.
Si une variable est exportée sans valeur, elle est stockée sans le caractère `=`, sauf si elle existe déjà dans la liste des variables d'environnement.
Dans ce cas, elle est stockée avec le caractère `=` après son nom mais sans valeur associée.

### **unset :**
Cette commande supprime simplement une variable d'environnement. `unset` ne renvoie jamais d'erreur, donc même si la variable n'existe pas, elle se termine sans erreur.

### `exit` :
`exit` permet au programme de se terminer proprement, en renvoyant soit le statut de sortie de la dernière commande exécutée, soit le statut de sortie fourni en argument.

---

#### **SIGNAUX :**
Contient les fonctions pour gérer les signaux.

---

# DOCUMENTATION :

Pour des explications sur les fonctions et les concepts déjà utilisés dans les projets précédents, consultez les fichiers README de mes autres projets :

https://github.com/donnatchris/philosophers

https://github.com/donnatchris/minitalk

Cependant, à la fin de la section DOCUMENTATION, vous trouverez une section SHORT REMINDER avec un résumé de toutes les fonctions précédemment abordées.

---

### COOPÉRATION GITHUB

Voici les principales commandes pour travailler avec plusieurs branches :

#### Créer une nouvelle branche et basculer sur cette branche
```bash
git checkout -b <nom_de_la_branche>
```

#### Basculer sur une branche
```bash
git checkout <nom_de_la_branche>
```

#### Pousser votre travail sur votre branche
```bash
git add <nom_du_fichier1> <nom_du_fichier2> <...>

git commit -m "votre_message"

git push origin <nom_de_la_branche>
```

#### Fusionner votre branche avec main
```bash
git checkout main

git pull origin main #nécessaire pour récupérer

git merge origin <nom_de_la_branche>

git push origin main
```

---

### Les tokens dans minishell

Un **token** est une séquence de caractères dans une chaîne qui représente une seule unité de données significatives.
En programmation et en analyse syntaxique, les tokens sont les blocs de construction dans lesquels l'analyseur décompose l'entrée pour un traitement ultérieur.
Les tokens peuvent inclure des mots-clés, des identifiants, des opérateurs, des littéraux ou des symboles qui ont une signification dans un contexte spécifique.
Par exemple, dans un langage de programmation, un token peut représenter un mot-clé comme `if`, un opérateur comme `+`, ou un nombre comme `42`.
En général, les tokens permettent à l'analyseur de comprendre et de catégoriser les différentes parties d'une chaîne d'entrée.

Dans le contexte de **Minishell**, les tokens sont les éléments extraits de la ligne de commande d'entrée de l'utilisateur.
Ceux-ci peuvent inclure des commandes, des arguments, des opérateurs (tels que `|`, `&&`, `>`, `<`), des symboles spéciaux (comme les parenthèses pour le groupement), ou des variables d'environnement (par exemple, `$HOME`).
Minishell analyse l'entrée en la décomposant d'abord en tokens, qui sont ensuite utilisés pour construire un arbre de syntaxe abstraite (AST) ou pour interpréter et exécuter directement les commandes.
La gestion correcte des tokens permet à Minishell de traiter des lignes de commande complexes, d'effectuer des redirections, de gérer les pipes et d'étendre les variables d'environnement, lui permettant d'exécuter les commandes de l'utilisateur avec précision et efficacité.

Pour assurer l'exécution correcte des commandes, voici la tokenisation que j'utilise :

1.  **Parenthèses `()`**
    -   Utilisées pour regrouper les commandes et contrôler l'ordre d'exécution dans le shell.

2.  **ET logique `&&`**
    -   Utilisé pour exécuter la deuxième commande uniquement si la première réussit. Haute priorité pour permettre un enchaînement correct des commandes conditionnelles.

3.  **OU logique `||`**
    -   Utilisé pour exécuter la deuxième commande uniquement si la première échoue. Priorité similaire à `&&` pour l'enchaînement des commandes conditionnelles.

4.  **Pipe `|`**
    -   Permet de passer la sortie d'une commande comme entrée à une autre. Il doit être traité ensuite pour gérer les pipelines de commandes.

5.  **Redirections `<`, `>`, `>>`, `<<`**
    -   Utilisées pour rediriger l'entrée et la sortie, y compris l'ajout (`>>`) et la lecture jusqu'à un délimiteur (`<<`).
    Celles-ci doivent être gérées après les pipes pour configurer les flux d'entrée/sortie appropriés, sauf que le fichier temporaire heredoc ('<<') est créé avant l'exécution des pipes.

6.  **Arguments**
    -   Le nom de la commande et ses arguments sont traités en dernier, une fois que tous les opérateurs et tokens spéciaux sont gérés.
    -   J'utilise 3 types d'arguments :
        -   **word** sont des caractères consécutifs ne contenant aucun espace
        -   **strings** sont des caractères contenus entre des guillemets doubles
        -   **litteral** sont des caractères contenus entre des guillemets simples (les métacaractères à l'intérieur ne seront pas interprétés)

---

### Qu'est-ce qu'un arbre binaire ?

Un **arbre binaire** est une structure de données hiérarchique dans laquelle chaque nœud a au plus deux enfants, appelés **enfant gauche** et **enfant droit**. C'est un type de structure arborescente où chaque nœud stocke une valeur et des liens vers ses deux enfants (s'il y en a), formant une structure de branchement.

```markdown
	racine
       /    \
     nœud    nœud
    /   \    /   \
  feuille feuille feuille feuille
```


#### Caractéristiques clés :
1.  **Racine** : Le nœud le plus haut de l'arbre, d'où descendent tous les autres nœuds.
2.  **Parent et Enfant** : Un nœud est un **parent** s'il a au moins un enfant. Les nœuds directement connectés à un autre nœud sont des **enfants**.
3.  **Nœuds feuilles** : Les nœuds qui n'ont pas d'enfants sont appelés **nœuds feuilles**.
4.  **Hauteur** : La hauteur de l'arbre est la longueur du plus long chemin de la racine à un nœud feuille.
5.  **Profondeur** : La profondeur d'un nœud est la longueur du chemin de la racine à ce nœud.

#### Types d'arbres binaires :
-   **Arbre binaire complet** : Chaque nœud a 0 ou 2 enfants.
-   **Arbre binaire complet** : Tous les niveaux sont remplis sauf éventuellement le dernier, qui est rempli de gauche à droite.
-   **Arbre binaire parfait** : Tous les nœuds internes ont exactement deux enfants et tous les nœuds feuilles sont au même niveau.
-   **Arbre binaire équilibré** : Les hauteurs des sous-arbres gauche et droit de tout nœud diffèrent d'au plus un.
-   **Arbre dégénéré (ou pathologique)** : Un arbre où chaque nœud parent n'a qu'un seul enfant, ressemblant à une liste chaînée.

#### Opérations :
-   **Insertion** : Ajout d'un nouveau nœud à l'arbre à une position appropriée.
-   **Parcours** : Visite de chaque nœud dans un ordre spécifique, tel que le parcours **en ordre**, **pré-ordre** ou **post-ordre**.
-   **Recherche** : Recherche d'un nœud ou d'une valeur spécifique dans l'arbre, généralement en le parcourant.
-   **Suppression** : Suppression d'un nœud de l'arbre tout en préservant la structure de l'arbre binaire.

#### Cas d'utilisation des arbres binaires :
-   **Arbre de recherche binaire (BST)** : Un type spécial d'arbre binaire dans lequel l'enfant gauche est inférieur au nœud parent et l'enfant droit est supérieur. Il permet des opérations de recherche, d'insertion et de suppression efficaces.
-   **Arbres d'expression** : Dans le contexte des expressions mathématiques, un arbre binaire peut représenter des opérateurs et des opérandes, permettant une analyse et une évaluation efficaces.
-   **Arbre de codage de Huffman** : Un arbre binaire utilisé dans les algorithmes de compression de données pour un codage efficace des données en fonction de la fréquence.

Dans l'ensemble, les arbres binaires sont largement utilisés en informatique pour organiser et manipuler des données hiérarchiques. Ils servent de base à de nombreuses structures de données et algorithmes plus avancés.

#### **Dans Minishell**
Dans **Minishell**, j'utilise la structure de l'arbre binaire uniquement pour :
✅ **Gérer la précédence des opérateurs** en construisant l'arbre binaire pour refléter l'ordre d'exécution correct, en veillant à ce que les opérations comme les opérateurs logiques (par exemple, `&&`, `||`) et les pipes (`|`) soient traitées dans le bon ordre.

---

### Bibliothèque GNU readline

La bibliothèque GNU Readline est un outil puissant qui fournit des fonctionnalités d'édition de ligne et d'historique des commandes pour les programmes interactifs,
ce qui en fait un composant fondamental de nombreuses interfaces de ligne de commande de type Unix, y compris `bash` et `gdb`.
Elle permet aux utilisateurs de modifier efficacement les entrées à l'aide de raccourcis clavier, de rappeler les commandes précédentes et de naviguer dans le texte de manière transparente.
Pour utiliser `readline` dans un programme C, les en-têtes requis sont `<readline/readline.h>` et `<readline/history.h>`.
Lors de la compilation, le programme doit être lié avec `-lreadline`, et dans certains cas, `-lncurses` est également nécessaire.

Compiler avec la bibliothèque :

	gcc minishell.c -o minishell -lreadline

Compiler avec la bibliothèque et `-lncurses` si nécessaire :

	gcc minishell.c -o minishell -lreadline -lncurses

Installer `libreadline` si nécessaire (linux) :

	sudo apt-get install libreadline-dev

Installer `libreadline` si nécessaire (Macos) :

 	brew install readline

---

### `readline()`

> #include <readline/readline.h>
```c
char *readline(const char *prompt);
```

-   `prompt` : Une chaîne qui est affichée à l'utilisateur avant d'attendre une entrée. Elle peut être utilisée pour guider ou inviter l'utilisateur à une entrée spécifique.

-   **Retourne** : Un pointeur vers la chaîne contenant l'entrée de l'utilisateur. L'entrée est allouée dynamiquement, et il est de la responsabilité de l'appelant de `free()` la chaîne retournée lorsqu'elle n'est plus utilisée.

La fonction `readline()` fait partie de la bibliothèque GNU Readline, qui fournit un moyen de lire une ligne d'entrée de l'utilisateur, permettant des fonctionnalités d'édition de ligne avancées comme l'historique des commandes, la complétion d'entrée, et plus encore.

#### **Cas d'utilisation clés**
-   **Programmes shell interactifs** : `readline()` est couramment utilisé pour implémenter des programmes shell interactifs, où l'utilisateur entre des commandes, et le shell lit et traite l'entrée.
-   **Applications en ligne de commande** : Il est utilisé pour recueillir les entrées de l'utilisateur avec des fonctionnalités d'édition avancées, telles que le mouvement du curseur, le rappel de l'historique et l'auto-complétion.

#### **Comment ça marche**
Lorsque `readline()` est appelée, le programme :
1.  Affiche la chaîne d'invite à l'utilisateur.
2.  Attend que l'utilisateur entre une ligne de texte (terminée en appuyant sur Entrée).
3.  Traite l'entrée, y compris la gestion des pressions sur les touches de retour arrière ou de flèche pour éditer le texte.
4.  Retourne l'entrée sous forme de chaîne allouée dynamiquement.

#### **Exemple d'utilisation**
```c
#include <stdio.h>
#include <readline/readline.h>

int main(void)
{
    char *input = readline("Entrez la commande : ");

    if (input)
    {
        printf("Vous avez entré : %s\n", input);
        free(input);  // N'oubliez pas de libérer la mémoire !
    }

    return 0;
}
```

#### **Gestion des erreurs**
-   Si `readline()` rencontre une erreur ou si l'entrée est incomplète, elle peut retourner `NULL`. Cela peut se produire en cas de problèmes avec la mise en mémoire tampon de l'entrée ou l'allocation de mémoire.
-   Si l'utilisateur appuie sur Ctrl+D (fin de l'entrée), `readline()` retourne `NULL`, ce qui peut être géré en vérifiant la valeur `NULL` pour détecter quand l'utilisateur termine la session.

#### **Dans Minishell**
Dans **Minishell**, vous utiliserez `readline()` pour :
✅ **Inviter l'utilisateur à entrer des commandes** de manière interactive et capturer l'entrée.
✅ **Lire et modifier l'entrée de l'utilisateur** avec des fonctionnalités d'édition de ligne (par exemple, retour arrière, historique et auto-complétion).
✅ **Gérer l'entrée de l'utilisateur avec élégance** avec une détection d'erreur appropriée (par exemple, valeur de retour `NULL`) et la libération de la mémoire allouée.

---

### `rl_clear_history()`

> #include <readline/readline.h>
```c
void rl_clear_history(void);
```

-   **Retourne** : Rien.

La fonction `rl_clear_history()` fait partie de la bibliothèque GNU Readline et est utilisée pour effacer la liste d'historique qui est maintenue pendant la session. La liste d'historique contient les commandes ou les entrées précédemment saisies et est utilisée pour faciliter des fonctionnalités telles que la navigation dans l'historique, l'auto-complétion et la répétition des commandes.

#### **Cas d'utilisation clés**
-   **Effacer l'historique des commandes** : Utile lorsque vous souhaitez effacer toutes les entrées de l'historique, peut-être avant de commencer une nouvelle session ou après certaines commandes que vous ne souhaitez pas conserver dans l'historique.
-   **Confidentialité et sécurité** : Dans les scénarios où des commandes sensibles ou privées ne doivent pas être conservées dans l'historique, cette fonction garantit que l'historique est effacé.

#### **Comment ça marche**
Lorsque `rl_clear_history()` est appelée :
1.  Elle supprime toutes les entrées de la liste d'historique.
2.  Toutes les commandes ou entrées précédemment saisies sont supprimées, réinitialisant efficacement le suivi de l'historique.

#### **Exemple d'utilisation**
```c
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    // Simuler l'ajout d'une commande à l'historique
    add_history("echo Hello, World!");
    add_history("ls -l");

    // Effacer l'historique
    rl_clear_history();

    // Confirmer l'effacement de l'historique
    if (history_length == 0)
    {
        printf("Historique effacé avec succès.\n");
    }
    else
    {
        printf("L'historique contient toujours %d entrées.\n", history_length);
    }

    return 0;
}
```

#### **Gestion des erreurs**
-   Cette fonction ne rencontre généralement pas d'erreurs lors de son utilisation. Cependant, si l'historique n'a pas été initialisé auparavant, l'appel de `rl_clear_history()` n'aura tout simplement aucun effet.

#### **Dans Minishell**
Dans **Minishell**, vous utiliserez `rl_clear_history()` pour :
✅ **Effacer l'historique** lors du démarrage d'une nouvelle session ou lorsque des commandes spécifiques (par exemple, l'effacement de données sensibles) nécessitent que l'historique soit effacé.
✅ **Assurer la confidentialité** en supprimant les commandes stockées de l'historique avant de quitter ou après que certaines actions soient terminées.
✅ **Maintenir une session propre** en supprimant toutes les commandes non pertinentes ou obsolètes de l'historique.

---

### `rl_on_newline()`

> #include <readline/readline.h>
```c
void rl_on_newline(void);
```

-   **Retourne** : Rien.

La fonction `rl_on_newline()` fait partie de la bibliothèque GNU Readline et est utilisée pour indiquer à la bibliothèque Readline que l'utilisateur a appuyé sur la touche Entrée (nouvelle ligne). Cela peut être utile dans les scénarios où Readline doit effectuer une action ou répondre à l'utilisateur après avoir reçu une nouvelle ligne, comme le traitement de l'entrée ou le déclenchement de certains comportements dans l'interface de ligne de commande.

#### **Cas d'utilisation clés**
-   **Gestion explicite des nouvelles lignes** : Dans certaines applications, lors du traitement des commandes ou des entrées, vous pouvez vouloir signaler manuellement à Readline qu'une nouvelle ligne a été rencontrée, surtout si vous gérez manuellement le traitement des entrées.
-   **Déclencher une action après une nouvelle ligne** : Utile lors de l'implémentation de comportements personnalisés qui doivent se produire immédiatement après que l'utilisateur appuie sur Entrée, comme l'exécution d'une commande ou le nettoyage des tampons d'entrée.

#### **Comment ça marche**
Lorsque `rl_on_newline()` est appelée :
1.  Elle définit un drapeau interne indiquant que l'utilisateur a appuyé sur Entrée.
2.  Ce drapeau peut être utilisé par les mécanismes internes de Readline pour déclencher toutes les actions nécessaires qui seraient gérées après une entrée de nouvelle ligne.

#### **Exemple d'utilisation**
```c
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char *input = readline("Entrez une commande : ");
    if (input)
    {
        // Simuler le traitement après une nouvelle ligne
        rl_on_newline();  // Déclencher une action après avoir appuyé sur Entrée
        printf("Vous avez entré : %s\n", input);
        free(input);
    }

    return 0;
}
```

#### **Gestion des erreurs**
-   Cette fonction ne rencontre généralement pas d'erreurs mais repose sur l'état interne correct de la bibliothèque Readline. Si la bibliothèque n'est pas initialisée correctement, elle peut ne pas avoir l'effet souhaité.

#### **Dans Minishell**
Dans **Minishell**, vous utiliserez `rl_on_newline()` pour :
✅ **Déclencher des actions après que l'utilisateur appuie sur Entrée** lors de la saisie de commandes, comme l'exécution de la commande ou le traitement de l'entrée.
✅ **Permettre une gestion correcte** des nouvelles lignes lors de l'utilisation de la bibliothèque Readline, en particulier lors de la personnalisation du comportement après avoir reçu une entrée de l'utilisateur.
✅ **Coordonner avec d'autres fonctions de gestion des entrées** pour assurer des interactions utilisateur fluides, en particulier pour les configurations readline personnalisées.

---

### `rl_replace_line()`

> #include <readline/readline.h>
```c
void rl_replace_line(const char *text, int clear_undo);
```

-   `text` : La nouvelle chaîne qui remplacera la ligne actuelle dans le tampon Readline.
-   `clear_undo` : Un drapeau indiquant s'il faut effacer l'historique d'annulation. S'il est défini sur une valeur non nulle, l'historique d'annulation sera effacé. S'il est défini sur `0`, l'historique d'annulation est préservé.

-   **Retourne** : Rien.

La fonction `rl_replace_line()` remplace la ligne d'entrée actuelle dans le tampon Readline par la chaîne spécifiée (`text`). Cette fonction est généralement utilisée lorsque vous devez modifier la ligne en cours d'édition, comme dans le cas de la complétion d'une commande ou de la mise à jour de l'invite.

#### **Cas d'utilisation clés**
-   **Modification de ligne** : Vous pouvez utiliser `rl_replace_line()` si vous souhaitez modifier ou mettre à jour la ligne que l'utilisateur est en train de modifier dans l'invite de commande, sans que l'utilisateur ait à la retaper manuellement.
-   **Implémentation de la complétion de commande** : Lors de l'implémentation de l'auto-complétion ou d'autres fonctionnalités où une partie de l'entrée de l'utilisateur doit être remplacée ou modifiée.
-   **Édition interactive** : Elle peut être utile pour modifier la ligne après que l'utilisateur a saisi du texte, mais avant qu'il n'appuie sur Entrée.

#### **Comment ça marche**
Lorsque `rl_replace_line()` est appelée :
1.  Elle remplace le contenu actuel du tampon de ligne par la chaîne `text`.
2.  Si `clear_undo` est défini sur `1`, elle efface l'historique d'annulation, ce qui signifie que les états précédents de la ligne ne peuvent plus être annulés.
3.  Si `clear_undo` est défini sur `0`, les états précédents de la ligne sont conservés dans l'historique d'annulation, permettant à l'utilisateur d'annuler le remplacement.

#### **Exemple d'utilisation**
```c
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char *input = readline("Entrez une commande : ");
    if (input)
    {
        // Remplacer la ligne actuelle par une version modifiée
        rl_replace_line("Commande modifiée", 0);  // Ligne remplacée, historique d'annulation préservé
        printf("Entrée modifiée : %s\n", input);
        free(input);
    }

    return 0;
}
```

#### **Gestion des erreurs**
-   Il n'y a pas de conditions d'erreur courantes pour cette fonction, mais elle nécessite une initialisation correcte de la bibliothèque Readline. Si la bibliothèque Readline n'est pas configurée ou si la ligne d'entrée est invalide, un comportement inattendu peut se produire.

#### **Dans Minishell**
Dans **Minishell**, vous utiliserez `rl_replace_line()` pour :
✅ **Modifier la ligne en cours d'édition** en réponse à l'auto-complétion, aux corrections de commandes ou à d'autres fonctionnalités interactives.
✅ **Mettre à jour le tampon d'entrée de l'utilisateur** sans que l'utilisateur ait à retaper des commandes ou des réponses.
✅ **Contrôler l'historique d'annulation** pour une gestion fine des modifications apportées à la ligne lors de l'édition.

---

### `rl_redisplay()`

> #include <readline/readline.h>
```c
void rl_redisplay(void);
```

-   **Retourne** : Rien.

La fonction `rl_redisplay()` force Readline à ré-afficher la ligne d'entrée actuelle, affichant ainsi à nouveau le tampon actuel sur le terminal. Cette fonction est utile lorsque la ligne doit être mise à jour ou redessinée après que des modifications ont été apportées, comme après avoir modifié la ligne avec `rl_replace_line()`, ou pour gérer les cas où l'écran a été effacé ou redimensionné.

#### **Cas d'utilisation clés**
-   **Mises à jour de ligne** : Si vous modifiez la ligne actuelle à l'aide de `rl_replace_line()`, vous devrez peut-être appeler `rl_redisplay()` pour refléter ces modifications sur le terminal.
-   **Redimensionnement du terminal** : Lorsque le terminal est redimensionné ou que l'écran est effacé, `rl_redisplay()` garantit que la ligne est ré-affichée correctement à la nouvelle position.
-   **Mise à jour de l'invite** : Après avoir mis à jour l'invite de manière dynamique, `rl_redisplay()` peut être appelée pour afficher immédiatement les modifications à l'utilisateur.
-   **Comportement du shell interactif** : Dans les shells, cela est utile pour maintenir l'interface utilisateur réactive, en particulier lors de l'interaction avec l'invite de commande ou de l'implémentation de fonctionnalités en temps réel.

#### **Comment ça marche**
Après l'appel de `rl_redisplay()` :
1.  La ligne actuelle dans le tampon Readline est redessinée sur le terminal.
2.  Elle garantit que toutes les modifications apportées à la ligne ou à l'invite sont immédiatement visibles par l'utilisateur, ce qui rend l'interface du shell plus réactive et conviviale.

#### **Exemple d'utilisation**
```c
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char *input = readline("Entrez une commande : ");
    if (input)
    {
        rl_replace_line("Commande modifiée", 0);  // Modifier la ligne
        rl_redisplay();  // Ré-afficher la ligne mise à jour
        free(input);
    }

    return 0;
}
```

#### **Gestion des erreurs**
-   Il n'y a pas de conditions d'erreur courantes pour `rl_redisplay()`. Cependant, il est important que Readline soit correctement initialisé avant d'utiliser cette fonction, car elle dépend de l'état interne de la bibliothèque Readline pour fonctionner correctement.

#### **Dans Minishell**
Dans **Minishell**, vous utiliserez `rl_redisplay()` pour :
✅ **Mettre à jour et redessiner la ligne de commande actuelle** après l'avoir modifiée, en veillant à ce que l'utilisateur voie les dernières modifications.
✅ **Gérer efficacement les mises à jour de l'écran** lorsque le terminal est redimensionné ou lorsque des invites dynamiques sont utilisées.
✅ **Assurer que l'affichage du terminal reste cohérent** lors de l'édition de la ligne de commande, améliorant ainsi l'expérience utilisateur.

---

### `add_history()`

> #include <readline/readline.h>
```c
int add_history(const char *line);
```

-   **`line`** : Une chaîne représentant la ligne à ajouter à la liste d'historique.
-   **Retourne** : `0` en cas de succès, ou `-1` en cas d'erreur.

La fonction `add_history()` ajoute une nouvelle ligne de texte à la liste d'historique de Readline, ce qui permet de la rappeler dans les sessions de shell ultérieures ou lors de la navigation dans la ligne de commande (par exemple, en utilisant les touches fléchées haut et bas). Cette liste d'historique est conservée en mémoire et peut être enregistrée ou chargée à partir d'un fichier à l'aide d'autres fonctions de Readline.

#### **Cas d'utilisation clés**
-   **Historique des commandes** : Conserve une trace des commandes que l'utilisateur a saisies, permettant de rappeler les commandes précédentes pour plus de commodité.
-   **Navigation dans l'historique du shell** : Permet aux utilisateurs du shell de naviguer dans les commandes passées en appuyant sur les touches fléchées haut et bas.
-   **Historique persistant** : Lorsqu'elle est combinée avec des fonctions comme `read_history()` et `write_history()`, `add_history()` permet un historique des commandes persistant entre les sessions.

#### **Comment ça marche**
Lorsque `add_history()` est appelée :
1.  La `line` fournie est ajoutée à la liste d'historique stockée dans la bibliothèque Readline.
2.  La liste d'historique est alors disponible pour la navigation via les fonctionnalités d'édition de ligne intégrées de Readline (comme l'utilisation des touches fléchées pour rappeler les commandes précédentes).
3.  La liste d'historique peut être enregistrée ou chargée à partir d'un fichier à l'aide de `write_history()` et `read_history()`, respectivement, pour garantir que l'historique persiste entre les sessions.

#### **Exemple d'utilisation**
```c
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char *input = readline("Entrez une commande : ");
    if (input)
    {
        add_history(input);  // Ajouter la commande saisie à l'historique
        free(input);
    }

    return 0;
}
```

#### **Gestion des erreurs**
-   Si la `line` est `NULL` ou invalide, la fonction retournera `-1`.
-   S'il y a un problème avec l'allocation de mémoire ou la gestion interne de la liste d'historique, elle retournera également `-1`.

#### **Dans Minishell**
Dans **Minishell**, vous utiliserez `add_history()` pour :
✅ **Ajouter les commandes de l'utilisateur** à la liste d'historique, permettant un rappel facile des commandes passées dans les sessions futures.
✅ **Améliorer l'expérience utilisateur** en permettant une navigation transparente dans les commandes précédemment saisies à l'aide des touches fléchées haut et bas.
✅ **Stocker l'historique** qui peut persister entre les sessions de shell en l'enregistrant ou en le chargeant à partir d'un fichier.

---

### `access()`

> #include <unistd.h>
```c
int access(const char *pathname, int mode);
```

-   **`pathname`** : Le chemin du fichier ou du répertoire à vérifier.
-   **`mode`** : Un masque de bits qui spécifie les vérifications à effectuer. Il peut s'agir d'une ou plusieurs des valeurs suivantes :
    -   `R_OK` : Vérifier si le fichier est lisible.
    -   `W_OK` : Vérifier si le fichier est accessible en écriture.
    -   `X_OK` : Vérifier si le fichier est exécutable.
    -   `F_OK` : Vérifier si le fichier existe.
-   **Retourne** : `0` si le fichier spécifié existe et que l'accès demandé est autorisé, ou `-1` en cas d'erreur avec `errno` défini en conséquence.

La fonction `access()` vérifie l'accessibilité d'un fichier ou d'un répertoire. Elle vérifie si le processus en cours dispose des autorisations requises (lecture, écriture, exécution) pour le fichier spécifié. Elle peut également vérifier l'existence du fichier, en fonction des indicateurs de mode passés.

#### **Cas d'utilisation clés**
-   **Vérifications des autorisations** : Déterminer si un fichier est lisible, accessible en écriture ou exécutable avant de tenter des opérations dessus.
-   **Vérification de l'existence d'un fichier** : Vérifier si un fichier ou un répertoire existe sans tenter de l'ouvrir.
-   **Pré-vérification de l'accessibilité des fichiers** : Prévenir les erreurs en vérifiant les autorisations d'accès avant d'effectuer des actions comme l'ouverture ou l'exécution d'un fichier.

#### **Comment ça marche**
`access()` vérifie le fichier spécifié par `pathname` en fonction du mode d'accès passé dans `mode`.
-   Si la vérification réussit, `access()` retourne `0`, indiquant que le fichier existe et que l'accès requis est autorisé.
-   Si la vérification échoue (par exemple, le fichier n'existe pas ou l'utilisateur n'a pas l'autorisation), `access()` retourne `-1` et définit `errno` sur le code d'erreur approprié (par exemple, `ENOENT` pour "Aucun fichier ou répertoire de ce type").

#### **Exemple d'utilisation**
```c
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    if (access("/chemin/vers/fichier.txt", F_OK) == 0)
    {
        printf("Le fichier existe !\n");
    }
    else
    {
        perror("La vérification du fichier a échoué");
    }

    return 0;
}
```

#### **Gestion des erreurs**
-   Si `pathname` est `NULL`, ou si le fichier ne peut pas être accédé en raison d'arguments non valides, `access()` retournera `-1` et définira `errno`.
-   Les codes d'erreur suivants peuvent être définis :
    -   `ENOENT` : Le fichier n'existe pas.
    -   `EACCES` : Autorisation refusée pour le mode d'accès demandé.
    -   `ENOTDIR` : Un composant du chemin n'est pas un répertoire.

#### **Dans Minishell**
Dans **Minishell**, vous utiliserez `access()` pour :
✅ **Vérifier l'existence d'un fichier** avant de tenter de l'exécuter ou de l'ouvrir, prévenant ainsi les erreurs.
✅ **Vérifier l'accessibilité** des fichiers pour s'assurer que l'utilisateur actuel dispose des autorisations appropriées pour lire, écrire ou exécuter.
✅ **Améliorer l'expérience utilisateur** en autorisant des vérifications conditionnelles sur les autorisations de fichiers avant d'exécuter des commandes ou de manipuler des fichiers.

---

### `wait3()`

> #include <sys/wait.h>
```c
p_t wait3(int *status, int options, struct rusage *rusage);
```

-   **`status`** : Un pointeur vers un entier où le statut de sortie du processus enfant sera stocké. La valeur pointée par `status` peut être utilisée avec des macros comme `WIFEXITED`, `WEXITSTATUS`, `WIFSIGNALED`, etc., pour analyser l'état de terminaison du processus enfant.
-   **`options`** : Un masque de bits d'options qui affectent le comportement de `wait3()`. Il peut inclure des indicateurs tels que `WNOHANG` (ne pas bloquer si aucun enfant n'est sorti), `WUNTRACED` (attendre également les processus enfants arrêtés), ou `WCONTINUED` (attendre les processus enfants continués).
-   **`rusage`** : Un pointeur vers une `struct rusage` où les informations sur l'utilisation des ressources pour le processus enfant seront stockées. Cela peut inclure des informations telles que le temps CPU consommé, l'utilisation de la mémoire, etc. Si `rusage` est `NULL`, aucune information sur l'utilisation des ressources n'est retournée.
-   **Retourne** : L'ID de processus de l'enfant qui s'est terminé, ou `-1` en cas d'erreur avec `errno` défini en conséquence.

`wait3()` est utilisé par un processus parent pour attendre la fin d'un processus enfant. Il se comporte de la même manière que `wait()`, mais en plus de retourner le statut de terminaison de l'enfant, il vous permet également de récupérer des informations sur l'utilisation des ressources pour le processus enfant.

#### **Cas d'utilisation clés**
-   **Surveillance de la fin d'un processus enfant** : Utilisé lorsque vous souhaitez savoir quand un processus enfant se termine et éventuellement récupérer des informations sur la façon dont il s'est terminé.
-   **Suivi de l'utilisation des ressources** : Utile pour surveiller la quantité de temps CPU ou de mémoire qu'un processus enfant a consommée pendant son exécution.
-   **Gestion avancée des processus** : `wait3()` fournit des informations plus détaillées que `wait()`, en particulier en termes d'utilisation des ressources.

#### **Comment ça marche**
La fonction `wait3()` attend la fin de n'importe quel processus enfant. Si un ou plusieurs enfants se sont terminés, elle retourne immédiatement avec l'ID de processus de l'enfant.
-   Si `rusage` est fourni, `wait3()` remplira également la `struct rusage` avec les données d'utilisation des ressources pour le processus enfant.
-   Si l'indicateur `options` est défini sur `WNOHANG`, `wait3()` retournera immédiatement si aucun enfant ne s'est terminé, au lieu de bloquer.

#### **Différence avec `wait()`**
-   **`wait()`** : Attend la fin d'un processus enfant et retourne son statut de sortie. Il ne fournit pas d'informations sur l'utilisation des ressources.
-   **`wait3()`** : Comme `wait()`, mais permet également de récupérer les données d'utilisation des ressources pour le processus enfant terminé via l'argument `rusage`.

#### **Exemple d'utilisation**
```c
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/resource.h>

int main(void)
{
    pid_t pid;
    int status;
    struct rusage usage;

    pid = fork();
    if (pid == 0)
    {
        // Processus enfant
        printf("Processus enfant en cours d'exécution\n");
        _exit(0);
    }
    else
    {
        // Processus parent
        pid_t child_pid = wait3(&status, 0, &usage);
        if (child_pid > 0)
        {
            printf("Enfant %d terminé\n", child_pid);
            printf("Temps CPU utilisé : %ld.%06ld secondes\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
        }
        else
        {
            perror("wait3 a échoué");
        }
    }

    return 0;
}
```

#### **Gestion des erreurs**
-   Si `status` est `NULL`, `wait3()` échouera et retournera `-1` avec `errno` défini sur `EFAULT`.
-   Si `rusage` est invalide, `wait3()` peut échouer, retournant `-1` et définissant `errno`.
-   D'autres erreurs peuvent être dues à des processus enfants qui ne se terminent pas ou à l'incapacité de `wait3()` de récupérer des informations.

#### **Dans Minishell**
Dans **Minishell**, vous utiliserez `wait3()` pour :
✅ **Attendre la fin des processus enfants** et obtenir des informations détaillées sur leur statut.
✅ **Surveiller l'utilisation des ressources** des processus enfants (par exemple, l'utilisation du CPU et de la mémoire), ce qui est utile pour le débogage ou l'optimisation de la consommation des ressources.
✅ **Améliorer la gestion des processus** en fournissant une version plus avancée de `wait()` qui donne accès à la fois au statut de sortie et aux détails d'utilisation des ressources pour les processus enfants.

---

### `wait4()`

> #include <sys/wait.h>
```c
pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);
```

-   **`pid`** : L'ID de processus de l'enfant à attendre. S'il est de `-1`, `wait4()` attend la fin de n'importe quel processus enfant. S'il est de `0`, il attend n'importe quel processus enfant du même groupe de processus. Sinon, il attend l'ID de processus spécifié.
-   **`status`** : Un pointeur vers un entier où le statut de sortie du processus enfant sera stocké. La valeur pointée par `status` peut être utilisée avec des macros comme `WIFEXITED`, `WEXITSTATUS`, `WIFSIGNALED`, etc., pour analyser l'état de terminaison du processus enfant.
-   **`options`** : Un masque de bits d'options qui affectent le comportement de `wait4()`. Il peut inclure des indicateurs tels que `WNOHANG` (ne pas bloquer si aucun enfant n'est sorti), `WUNTRACED` (attendre également les processus enfants arrêtés), ou `WCONTINUED` (attendre les processus enfants continués).
-   **`rusage`** : Un pointeur vers une `struct rusage` où les informations sur l'utilisation des ressources pour le processus enfant seront stockées. Cela peut inclure des informations telles que le temps CPU consommé, l'utilisation de la mémoire, etc. Si `rusage` est `NULL`, aucune information sur l'utilisation des ressources n'est retournée.
-   **Retourne** : L'ID de processus de l'enfant qui s'est terminé, ou `-1` en cas d'erreur avec `errno` défini en conséquence.

`wait4()` est similaire à `wait3()`, mais il offre plus de flexibilité dans la sélection du processus enfant à attendre. Il est utilisé pour attendre la fin d'un processus enfant spécifique (ou de n'importe quel processus enfant si `pid == -1`), avec l'avantage supplémentaire de collecter des informations sur l'utilisation des ressources.

#### **Cas d'utilisation clés**
-   **Surveillance de la fin d'un processus enfant** : Utilisé lorsque vous souhaitez savoir quand un processus enfant spécifique se termine et éventuellement récupérer des informations sur la façon dont il s'est terminé.
-   **Suivi de l'utilisation des ressources** : Utile pour surveiller la quantité de temps CPU ou de mémoire qu'un processus enfant a consommée pendant son exécution.
-   **Gestion avancée des processus** : `wait4()` fournit des informations détaillées sur un processus enfant spécifié ou n'importe quel processus enfant, avec un contrôle plus fin que `wait()`.

#### **Comment ça marche**
La fonction `wait4()` se comporte de la même manière que `wait()` et `wait3()`, mais elle vous permet de :
-   Attendre un processus enfant spécifique en passant son `pid`.
-   Récupérer des informations sur l'utilisation des ressources en fournissant une `struct rusage`.
-   Personnaliser le comportement à l'aide de l'argument `options` (par exemple, `WNOHANG` pour un comportement non bloquant).

#### **Différence avec `wait()` et `wait3()`**
-   **`wait()`** : Attend la fin de n'importe quel processus enfant et retourne son statut de sortie. Il ne permet pas de spécifier quel processus enfant attendre ni de récupérer les données d'utilisation des ressources.
-   **`wait3()`** : Comme `wait()`, mais il permet de récupérer des informations sur l'utilisation des ressources pour le processus enfant terminé.
-   **`wait4()`** : Permet un contrôle encore plus grand sur le processus enfant à attendre (via l'argument `pid`), tout en fournissant des détails sur l'utilisation des ressources, comme `wait3()`.

#### **Exemple d'utilisation**
```c
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/resource.h>

int main(void)
{
    pid_t pid;
    int status;
    struct rusage usage;

    pid = fork();
    if (pid == 0)
    {
        // Processus enfant
        printf("Processus enfant en cours d'exécution\n");
        _exit(0);
    }
    else
    {
        // Processus parent
        pid_t child_pid = wait4(pid, &status, 0, &usage);
        if (child_pid > 0)
        {
            printf("Enfant %d terminé\n", child_pid);
            printf("Temps CPU utilisé : %ld.%06ld secondes\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
        }
        else
        {
            perror("wait4 a échoué");
        }
    }

    return 0;
}
```

#### **Gestion des erreurs**
-   Si `status` est `NULL`, `wait4()` échouera et retournera `-1` avec `errno` défini sur `EFAULT`.
-   Si `rusage` est invalide, `wait4()` peut échouer, retournant `-1` et définissant `errno`.
-   D'autres erreurs peuvent être dues à des processus enfants qui ne se terminent pas ou à l'incapacité de `wait4()` de récupérer des informations.

#### **Dans Minishell**
Dans **Minishell**, vous utiliserez `wait4()` pour :
✅ **Attendre la fin de processus enfants spécifiques** et récupérer des informations détaillées sur leur statut.
✅ **Surveiller l'utilisation des ressources** des processus enfants (par exemple, l'utilisation du CPU et de la mémoire), ce qui est utile pour le débogage ou l'optimisation de la consommation des ressources.
✅ **Améliorer la gestion des processus** en offrant plus de contrôle sur le processus enfant à attendre, et l'accès à la fois au statut de sortie et aux détails d'utilisation des ressources pour le processus enfant terminé.

---

### `exit()`

> #include <stdlib.h>
```c
void exit(int status);
```

-   `status` : Un code de statut entier. Un `status` de `0` indique généralement un succès, tandis qu'une valeur non nulle indique une erreur ou une fin anormale.

-   **Retourne** : Cette fonction ne retourne pas ; elle termine le programme.

La fonction `exit()` est utilisée pour terminer un programme. Elle effectue un processus de nettoyage avant la fin du programme, garantissant que les ressources sont libérées correctement. Le code de statut passé à `exit()` est retourné à l'environnement, souvent utilisé pour indiquer si le programme s'est terminé avec succès ou a rencontré une erreur.

#### **Cas d'utilisation clés**
-   **Fin de programme en douceur** : Utilisé lorsqu'un programme a terminé son exécution, ou s'il rencontre une erreur qui empêche toute exécution ultérieure.
-   **Retour d'un code de statut** : Le code de statut peut être utilisé par le système d'exploitation ou le processus parent pour déterminer le résultat de l'exécution du programme.

#### **Comment ça marche**
Lorsque `exit()` est appelée, il se passe ce qui suit :
1.  Le programme commence le processus de sortie.
2.  Les fonctions enregistrées via `atexit()` sont appelées dans l'ordre inverse.
3.  Tous les fichiers ouverts sont fermés (similaire à l'appel de `fclose()`).
4.  La mémoire allouée dynamiquement via `malloc()`, `calloc()`, etc., n'est pas automatiquement libérée, mais peut être nettoyée par le système d'exploitation.
5.  Le programme retourne le code de statut de sortie au système d'exploitation.

#### **Nettoyage effectué par `exit()`**
Avant la fin du programme, `exit()` effectue les tâches de nettoyage suivantes :
-   **Ferme tous les descripteurs de fichiers ouverts** : Les fichiers, sockets, etc., qui ont été ouverts pendant l'exécution du programme sont fermés. Cela évite les fuites de descripteurs de fichiers et garantit que toutes les modifications apportées aux fichiers sont écrites.
-   **Appelle les fonctions de sortie enregistrées** : Toutes les fonctions enregistrées à l'aide de `atexit()` sont appelées dans l'ordre inverse de leur enregistrement. Cela permet aux utilisateurs d'effectuer des tâches de nettoyage finales (par exemple, libérer la mémoire allouée dynamiquement).
-   **Vide les tampons de sortie** : Toute sortie mise en mémoire tampon qui n'a pas encore été écrite (par exemple, dans `stdout` ou `stderr`) est vidée pour garantir que toutes les données sont sorties.
-   **Libère les ressources système** : Le système d'exploitation peut récupérer toutes les ressources (comme la mémoire et les verrous) utilisées par le programme.

#### **Exemple d'utilisation**
```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Du code

    if (/* une condition d'erreur */)
    {
        fprintf(stderr, "Une erreur s'est produite !\n");
        exit(1);  // Quitter avec le statut 1 indiquant une erreur
    }

    // Fin normale du programme
    exit(0);  // Quitter avec le statut 0 indiquant un succès
}
```

#### **Gestion des erreurs**
-   Si `exit()` est appelée sans effectuer au préalable le nettoyage nécessaire ou sans libérer les ressources, certaines fuites de mémoire ou de descripteurs de fichiers peuvent se produire.
-   Le code de statut passé à `exit()` peut fournir des informations sur la façon dont le programme s'est terminé (par exemple, `exit(0)` pour un succès, `exit(1)` pour une erreur).

#### **Dans Minishell**
Dans **Minishell**, vous utiliserez `exit()` pour :
✅ **Terminer le shell en douceur** après avoir exécuté des commandes ou lorsqu'une erreur se produit.
✅ **Retourner un code de statut** qui indique le succès ou l'échec au système d'exploitation ou au processus parent.
✅ **S'assurer que les ressources sont nettoyées** correctement, comme la fermeture des descripteurs de fichiers et l'appel des fonctions de sortie pour les tâches de nettoyage définies par l'utilisateur.

---

### `getcwd()`

> #include <unistd.h>
```c
char *getcwd(char *buf, size_t size);
```

-   **`buf`** : Un pointeur vers un tampon où le chemin absolu du répertoire de travail actuel sera stocké. Si `buf` est `NULL`, la fonction allouera de la mémoire pour le chemin de manière dynamique (si `size` est suffisamment grand).
-   **`size`** : La taille du tampon `buf` en octets. Si la taille est trop petite pour stocker le chemin complet, `getcwd()` retournera `NULL` et définira `errno` sur `ERANGE`.
-   **Retourne** : Un pointeur vers le `buf` en cas de succès, ou `NULL` en cas d'erreur avec `errno` défini en conséquence.

La fonction `getcwd()` est utilisée pour récupérer le chemin absolu du répertoire de travail actuel. Elle peut soit stocker le résultat dans un tampon existant, soit allouer de la mémoire de manière dynamique si nécessaire.

#### **Cas d'utilisation clés**
-   **Obtenir le répertoire de travail actuel** : Utile lorsque vous avez besoin de connaître le répertoire actuel où votre programme s'exécute, en particulier avant d'effectuer des opérations comme changer de répertoire ou manipuler des chemins de fichiers.
-   **Chemin relatif vs. chemin absolu** : Lorsque vous traitez des chemins de fichiers, connaître le répertoire de travail actuel peut vous aider à construire des chemins absolus à partir de chemins relatifs.

#### **Comment ça marche**
`getcwd()` récupère le répertoire de travail actuel et le stocke dans le tampon fourni par l'utilisateur. Si le tampon est trop petit pour contenir le répertoire, il échouera et retournera `NULL`, avec `errno` défini sur `ERANGE`. Si `buf` est `NULL`, un tampon alloué dynamiquement sera utilisé pour stocker le résultat. Vous pouvez ensuite utiliser `free()` pour libérer ce tampon si `buf` était `NULL`.

#### **Exemple d'utilisation**
```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    char *cwd = getcwd(NULL, 0);
    if (cwd)
    {
        printf("Répertoire de travail actuel : %s\n", cwd);
        free(cwd);  // Libérer le tampon alloué dynamiquement
    }
    else
    {
        perror("getcwd a échoué");
    }

    return 0;
}
```

#### **Gestion des erreurs**
-   Si `getcwd()` échoue, il retourne `NULL` et définit `errno` en conséquence :
    -   `ENOMEM` : Il n'y avait pas assez de mémoire pour allouer un tampon.
    -   `ERANGE` : Le tampon fourni était trop petit pour stocker le chemin complet.
    -   `EINVAL` : Le répertoire actuel n'est pas valide (par exemple, il a été supprimé après le démarrage du processus).
    -   `EACCES` : Le processus n'a pas l'autorisation d'accéder au répertoire actuel.

#### **Dans Minishell**
Dans **Minishell**, vous utiliserez `getcwd()` pour :
✅ **Obtenir le répertoire de travail actuel** pour le montrer à l'utilisateur ou pour construire des chemins pour les commandes.
✅ **Vérifier le répertoire actuel** avant d'effectuer des opérations comme changer de répertoire (`cd`).
✅ **Gérer les chemins relatifs et absolus** lors du traitement des opérations sur les fichiers dans le shell.

---

### `chdir()`

> #include <unistd.h>
```c
int chdir(const char *path);
```

-   **`path`** : Une chaîne représentant le chemin du répertoire vers lequel vous souhaitez changer. Ce chemin peut être absolu ou relatif.
-   **Retourne** : `0` en cas de succès, ou `-1` en cas d'erreur avec `errno` défini en conséquence.

La fonction `chdir()` est utilisée pour changer le répertoire de travail actuel du processus appelant vers le répertoire spécifié. Cette fonction met à jour le répertoire de travail interne du processus, ce qui affectera les résolutions de chemins relatifs (par exemple, pour les opérations sur les fichiers). Elle ne modifie pas le système de fichiers réel mais met simplement à jour l'état du processus.

#### **Cas d'utilisation clés**
-   **Navigation dans les répertoires** : Elle est utilisée pour changer le répertoire de travail du processus avant d'exécuter des commandes qui dépendent de chemins relatifs.
-   **Opérations sur le système de fichiers** : Utile lorsque vous souhaitez changer de manière programmatique le répertoire actuel avant d'effectuer des opérations sur les fichiers ou les répertoires dans le shell ou d'autres programmes.

#### **Comment ça marche**
Lorsque `chdir()` est appelée, le répertoire de travail du processus est changé pour le chemin spécifié. Si le chemin est absolu, il part du répertoire racine (`/`), tandis que s'il est relatif, il est relatif au répertoire de travail actuel.

La fonction n'affecte pas le répertoire de travail du processus parent et ne change que le répertoire actuel du processus appelant.

#### **Exemple d'utilisation**
```c
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    if (chdir("/home/user") == 0)
        printf("Répertoire changé avec succès !\n");
    else
        perror("chdir a échoué");

    return 0;
}
```

#### **Gestion des erreurs**
-   Si `chdir()` échoue, il retourne `-1` et définit `errno` :
    -   `ENOENT` : Le répertoire n'existe pas.
    -   `ENOTDIR` : Un composant du chemin n'est pas un répertoire.
    -   `EACCES` : L'autorisation d'accéder au répertoire est refusée.
    -   `EINVAL` : Le chemin fourni est invalide.
    -   `ENOMEM` : Pas assez de mémoire pour traiter la demande.

#### **Dans Minishell**
Dans **Minishell**, vous utiliserez `chdir()` pour :
✅ **Changer le répertoire de travail actuel** lors de l'exécution de la commande `cd`.
✅ **Naviguer vers des répertoires** en fonction de l'entrée de l'utilisateur (chemins absolus ou relatifs).
✅ **Gérer les erreurs avec élégance** si le répertoire n'existe pas, n'est pas accessible, ou si d'autres erreurs se produisent lors de la navigation.

---

### `stat()`

> #include <sys/stat.h>
```c
int stat(const char *path, struct stat *statbuf);
```

-   **`path`** : Une chaîne représentant le chemin du fichier ou du répertoire dont vous souhaitez récupérer le statut.
-   **`statbuf`** : Un pointeur vers une `struct stat` où les informations sur le statut du fichier seront stockées.
-   **Retourne** : `0` en cas de succès, ou `-1` en cas d'erreur avec `errno` défini en conséquence.

La fonction `stat()` récupère des informations sur un fichier ou un répertoire et les stocke dans une `struct stat`. Cette structure contient diverses métadonnées sur le fichier, telles que sa taille, ses autorisations et ses horodatages.

#### **Cas d'utilisation clés**
-   **Métadonnées de fichier** : `stat()` est utilisé pour récupérer des informations détaillées sur les fichiers, telles que leur taille, leurs autorisations et leurs dates de modification.
-   **Vérification de l'existence d'un fichier** : Elle peut être utilisée pour vérifier si un fichier ou un répertoire existe et pour recueillir des informations à son sujet.
-   **Gestion des répertoires et des fichiers** : Souvent utilisée dans les scripts shell ou les utilitaires système pour analyser les fichiers ou déterminer les types de fichiers (fichier régulier, répertoire, lien symbolique, etc.).

#### **Comment ça marche**
Lorsque `stat()` est appelée, elle remplit la `struct stat` avec les informations suivantes :
-   **Type de fichier** (par exemple, fichier régulier, répertoire, lien symbolique).
-   **Taille du fichier** (en octets).
-   **Autorisations** (lecture/écriture/exécution).
-   **Horodatages** (par exemple, dernière heure d'accès, dernière heure de modification).
-   **Inode du fichier** (identifiant unique au sein du système de fichiers).

La structure `statbuf` est définie comme suit :
```c
struct stat {
    dev_t     st_dev;     // ID de l'appareil
    ino_t     st_ino;     // Numéro d'inode
    mode_t    st_mode;    // Mode du fichier (autorisations)
    nlink_t   st_nlink;   // Nombre de liens durs
    uid_t     st_uid;     // ID de l'utilisateur propriétaire du fichier
    gid_t     st_gid;     // ID du groupe propriétaire du fichier
    dev_t     st_rdev;    // ID de l'appareil (pour les fichiers spéciaux)
    off_t     st_size;    // Taille totale en octets
    blksize_t st_blksize; // Taille de bloc pour les E/S du système de fichiers
    blkcnt_t  st_blocks;  // Nombre de blocs de 512 octets alloués
    time_t    st_atime;   // Dernière heure d'accès
    time_t    st_mtime;   // Dernière heure de modification
    time_t    st_ctime;   // Dernière heure de changement de statut
};
```

#### **Exemple d'utilisation**
```c
#include <stdio.h>
#include <sys/stat.h>

int main(void)
{
    struct stat sb;
    if (stat("/chemin/vers/fichier", &sb) == 0) {
        printf("Taille du fichier : %ld octets\n", sb.st_size);
        printf("Autorisations du fichier : %o\n", sb.st_mode & 0777);
    } else {
        perror("stat a échoué");
    }
    return 0;
}
```

#### **Gestion des erreurs**
-   Si `stat()` échoue, il retourne `-1` et définit `errno` :
    -   `ENOENT` : Le fichier ou le répertoire n'existe pas.
    -   `ENOTDIR` : Un composant du chemin n'est pas un répertoire.
    -   `EACCES` : L'autorisation d'accéder au fichier ou au répertoire est refusée.
    -   `EINVAL` : Le chemin fourni est invalide.
    -   `ENOMEM` : Pas assez de mémoire pour récupérer les informations sur le fichier.

#### **Dans Minishell**
Dans **Minishell**, vous utiliserez `stat()` pour :
✅ **Récupérer les métadonnées des fichiers** (taille, autorisations, horodatages) lors du traitement de commandes comme `ls` ou de la vérification de l'existence de fichiers.
✅ **Vérifier le type de fichier** (fichier régulier, répertoire, lien symbolique) pour gérer correctement les commandes qui dépendent du type de fichier.
✅ **Gérer les erreurs avec élégance** lorsque les fichiers ou les répertoires n'existent pas ou ne peuvent pas être accédés.

---

### `lstat()`

> #include <sys/stat.h>
```c
int lstat(const char *path, struct stat *statbuf);
```

-   **`path`** : Une chaîne représentant le chemin du fichier ou du répertoire dont vous souhaitez récupérer le statut.
-   **`statbuf`** : Un pointeur vers une `struct stat` où les informations sur le statut du fichier seront stockées.
-   **Retourne** : `0` en cas de succès, ou `-1` en cas d'erreur avec `errno` défini en conséquence.

La fonction `lstat()` récupère des informations sur un fichier ou un répertoire, de la même manière que `stat()`, mais avec une différence essentielle : si le fichier est un lien symbolique, `lstat()` retournera les informations sur le lien symbolique lui-même, et non sur le fichier vers lequel il pointe. Si le fichier n'est pas un lien symbolique, il se comporte exactement comme `stat()`.

#### **Différences clés entre `stat()` et `lstat()`**
-   **`stat()`** : Récupère des informations sur le fichier ou le répertoire auquel le `path` fourni fait référence, en suivant les liens symboliques.
-   **`lstat()`** : Récupère des informations sur le lien symbolique lui-même, et non sur sa cible. Si `path` est un lien symbolique, `lstat()` fournira les métadonnées du lien, et non du fichier vers lequel il pointe.

#### **Cas d'utilisation clés**
-   **Métadonnées de fichier** : Comme `stat()`, `lstat()` est utilisé pour récupérer des informations sur les fichiers, y compris la taille du fichier, les autorisations et les horodatages.
-   **Gestion des liens symboliques** : `lstat()` est utilisé lorsque vous devez vérifier les propriétés d'un lien symbolique lui-même, plutôt que du fichier cible.
-   **Vérification de l'existence d'un fichier** : `lstat()` peut être utilisé pour vérifier si un lien symbolique existe et pour recueillir des informations à son sujet, sans suivre le lien.

#### **Comment ça marche**
Lorsque `lstat()` est appelée, elle remplit la `struct stat` avec les informations suivantes, de la même manière que `stat()` :
-   **Type de fichier** (par exemple, fichier régulier, répertoire, lien symbolique).
-   **Taille du fichier** (en octets).
-   **Autorisations** (lecture/écriture/exécution).
-   **Horodatages** (par exemple, dernière heure d'accès, dernière heure de modification).
-   **Inode du fichier** (identifiant unique au sein du système de fichiers).

La structure `statbuf` est remplie avec les mêmes champs qu'avec `stat()`, mais `lstat()` ne suivra pas les liens symboliques. Au lieu de cela, elle fournit des informations sur le lien lui-même.

#### **Exemple d'utilisation**
```c
#include <stdio.h>
#include <sys/stat.h>

int main(void)
{
    struct stat sb;
    if (lstat("/chemin/vers/fichier", &sb) == 0) {
        printf("Taille du fichier : %ld octets\n", sb.st_size);
        printf("Autorisations du fichier : %o\n", sb.st_mode & 0777);
    } else {
        perror("lstat a échoué");
    }
    return 0;
}
```

#### **Gestion des erreurs**
-   Si `lstat()` échoue, il retourne `-1` et définit `errno` :
    -   `ENOENT` : Le fichier ou le répertoire n'existe pas.
    -   `ENOTDIR` : Un composant du chemin n'est pas un répertoire.
    -   `EACCES` : L'autorisation d'accéder au fichier ou au répertoire est refusée.
    -   `EINVAL` : Le chemin fourni est invalide.
    -   `ENOMEM` : Pas assez de mémoire pour récupérer les informations sur le fichier.

#### **Dans Minishell**
Dans **Minishell**, vous utiliserez `lstat()` pour :
✅ **Gérer les liens symboliques** en récupérant des informations sur le lien lui-même, sans le suivre.
✅ **Vérifier le type de fichier** et les **autorisations** pour les liens symboliques, les répertoires et les fichiers réguliers.
✅ **Différencier les liens symboliques** des fichiers réguliers lors du traitement des chemins dans des commandes comme `ls -l`, ou lorsque vous devez examiner le lien plutôt que le fichier vers lequel il pointe.

---

### `fstat()`

> #include <sys/stat.h>
```c
int fstat(int fd, struct stat *statbuf);
```

-   **`fd`** : Un descripteur de fichier faisant référence à un fichier ou un socket ouvert.
-   **`statbuf`** : Un pointeur vers une `struct stat` où les informations sur le statut du fichier seront stockées.
-   **Retourne** : `0` en cas de succès, ou `-1` en cas d'erreur avec `errno` défini en conséquence.

La fonction `fstat()` récupère des informations sur le fichier associé au descripteur de fichier donné. Elle se comporte de la même manière que `stat()` mais opère sur un fichier ouvert, un socket ou d'autres descripteurs de fichiers, plutôt que sur un fichier spécifié par un chemin.

#### **Différences clés entre `fstat()`, `stat()` et `lstat()`**
-   **`stat()`** : Récupère des informations sur un fichier en fonction de son chemin, en suivant les liens symboliques vers la cible du fichier.
-   **`lstat()`** : Récupère des informations sur un fichier ou un répertoire, mais ne suit pas les liens symboliques, retournant à la place les informations sur le lien lui-même.
-   **`fstat()`** : Récupère les informations sur le fichier à partir d'un descripteur de fichier ouvert, qui peut être un fichier régulier, un répertoire ou un socket. Il n'a pas besoin d'un chemin, contrairement à `stat()` et `lstat()`.

#### **Cas d'utilisation clés**
-   **Métadonnées de fichier à partir d'un fichier ouvert** : `fstat()` est utile lorsque vous avez déjà un descripteur de fichier ouvert et que vous souhaitez récupérer des informations sur le fichier correspondant, sans avoir à le rouvrir avec `stat()` ou `lstat()`.
-   **Taille et type de fichier** : Vous pouvez utiliser `fstat()` pour obtenir la taille d'un fichier ouvert, vérifier son type (par exemple, fichier régulier, répertoire) et examiner ses autorisations.
-   **Sockets et pipes** : `fstat()` peut être utilisé pour récupérer des informations sur les sockets, les pipes et les périphériques ouverts.

#### **Comment ça marche**
Lorsque `fstat()` est appelée, elle remplit la `struct stat` avec des informations sur le fichier ou le périphérique associé au descripteur de fichier :
-   **Type de fichier** (par exemple, fichier régulier, répertoire, lien symbolique, socket).
-   **Taille du fichier** (en octets).
-   **Autorisations** (lecture/écriture/exécution).
-   **Horodatages** (par exemple, dernière heure d'accès, dernière heure de modification).
-   **Inode** (identifiant unique au sein du système de fichiers).

La structure `statbuf` est remplie de la même manière qu'avec `stat()` ou `lstat()`, mais `fstat()` fonctionne avec un descripteur de fichier ouvert plutôt qu'un chemin.

#### **Exemple d'utilisation**
```c
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    if (fd == -1) {
        perror("open a échoué");
        return 1;
    }

    struct stat sb;
    if (fstat(fd, &sb) == 0) {
        printf("Taille du fichier : %ld octets\n", sb.st_size);
        printf("Autorisations du fichier : %o\n", sb.st_mode & 0777);
    } else {
        perror("fstat a échoué");
    }

    close(fd);
    return 0;
}
```

#### **Gestion des erreurs**
-   Si `fstat()` échoue, il retourne `-1` et définit `errno` :
    -   `EBADF` : Le descripteur de fichier n'est pas valide ou ne fait pas référence à un fichier ouvert.
    -   `EINVAL` : Le descripteur de fichier n'est pas associé à un fichier.
    -   `ENOMEM` : Pas assez de mémoire pour récupérer les informations sur le fichier.
    -   D'autres erreurs peuvent inclure des problèmes avec le système de fichiers ou les autorisations.

#### **Dans Minishell**
Dans **Minishell**, vous utiliserez `fstat()` pour :
✅ **Obtenir des informations sur les fichiers** à partir de descripteurs de fichiers ouverts, comme la vérification de la taille, du type et des autorisations des fichiers.
✅ **Travailler avec des descripteurs de fichiers** dans les commandes shell, par exemple lors de la manipulation de fichiers avec redirection ou pipes.
✅ **Gérer les sockets et les fichiers spéciaux** qui sont ouverts et nécessitent des métadonnées pour être traités sans avoir besoin d'un chemin de fichier.

---

### `unlink()`

> #include <unistd.h>
```c
int unlink(const char *pathname);
```

-   **`pathname`** : Le chemin du fichier à supprimer.
-   **Retourne** : `0` en cas de succès, ou `-1` en cas d'erreur avec `errno` défini en conséquence.

La fonction `unlink()` supprime un fichier du système de fichiers. Elle supprime l'entrée de répertoire pour le fichier spécifié, ce qui rend le fichier inaccessible par son nom. S'il n'y a plus de références au fichier (c'est-à-dire pas de descripteurs de fichiers ouverts ni de liens durs), le fichier est réellement supprimé du disque.

#### **Cas d'utilisation clés**
-   **Suppression de fichiers** : `unlink()` est utilisé pour supprimer des fichiers du système de fichiers, libérant ainsi de l'espace.
-   **Suppression de liens inutiles** : Si plusieurs liens durs vers un fichier existent, `unlink()` supprime un seul lien. Le fichier lui-même n'est supprimé que lorsque le dernier lien est supprimé.
-   **Suppression de fichiers temporaires** : Couramment utilisé dans les scripts shell et les programmes pour nettoyer les fichiers temporaires qui ne sont plus nécessaires.

#### **Comment ça marche**
Lorsque vous appelez `unlink()` sur un fichier :
-   Le système de fichiers supprime l'entrée de répertoire pour le fichier.
-   S'il n'y a plus de liens vers le fichier et qu'aucun processus ne l'a ouvert, le fichier est supprimé et l'espace disque est libéré.
-   S'il existe encore d'autres liens durs vers le fichier ou s'il est ouvert par un processus, le fichier reste sur le disque et n'est supprimé que lorsque le dernier lien ou descripteur de fichier ouvert est fermé.

#### **Notes clés**
-   `unlink()` ne fonctionne que sur les fichiers réguliers. Il ne fonctionne pas sur les répertoires (pour cela, vous utiliseriez `rmdir()`).
-   Si le fichier est ouvert lorsque `unlink()` est appelée, il n'est supprimé que lorsqu'il est fermé, mais le descripteur de fichier permet toujours d'accéder à son contenu jusqu'à ce qu'il soit fermé.
-   `unlink()` ne nécessite pas que le fichier soit fermé avant d'être supprimé, bien que le contenu du fichier puisse toujours être accessible jusqu'à ce que le dernier descripteur de fichier soit fermé.

#### **Exemple d'utilisation**
```c
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    const char *filename = "test.txt";

    if (unlink(filename) == 0) {
        printf("Fichier %s supprimé avec succès.\n", filename);
    }
    else {
        perror("unlink a échoué");
    }

    return 0;
}
```

#### **Gestion des erreurs**
`unlink()` peut échouer et retourner `-1`, avec `errno` défini pour indiquer l'erreur :
-   `ENOENT` : Le fichier n'existe pas.
-   `EACCES` : L'appelant n'a pas l'autorisation de supprimer le fichier.
-   `EPERM` : L'appelant n'a pas les privilèges requis pour dissocier le fichier.
-   `ENOTDIR` : Un composant du chemin n'est pas un répertoire.
-   `EBUSY` : Le fichier est utilisé par un processus.

#### **Dans Minishell**
Dans **Minishell**, vous utiliserez `unlink()` pour :
✅ **Supprimer les fichiers temporaires** créés lors de l'exécution du shell.
✅ **Gérer la suppression de fichiers** lors du traitement de commandes qui impliquent la suppression de fichiers ou le nettoyage après les processus.
✅ **Supprimer les fichiers spécifiés par l'utilisateur**, en particulier dans les cas de redirection de fichiers ou de manipulation de la sortie.

>### à propos des inodes et des liens durs
>
>#### Qu'est-ce qu'un **inode** ?
>Un **inode** (nœud d'index) est une **structure de données** dans un système de fichiers qui stocke des **métadonnées** sur un fichier mais **pas** son nom ni son contenu.
>
>##### Que contient un inode ?
>✅ **Type de fichier** (fichier régulier, répertoire, etc.)
>✅ **Autorisations** (lecture, écriture, exécution)
>✅ **Propriétaire et groupe**
>✅ **Taille du fichier**
>✅ **Horodatages** (création, modification, accès)
>✅ **Nombre de liens durs**
>✅ **Pointeurs vers les blocs de données** (où le contenu réel du fichier est stocké)
>
>##### Points clés :
>- Chaque **fichier et répertoire** a un **numéro d'inode unique** au sein d'un système de fichiers.
>- Les noms de fichiers sont stockés séparément dans des **répertoires**, qui mappent les noms aux **numéros d'inode**.
>- Les liens durs partagent le **même inode** (mêmes données).
>- Les liens symboliques (symlinks) ont **leur propre inode**, pointant vers le nom d'un autre fichier.
>
>##### Vérifier les inodes avec `ls -i` :
>```bash
>ls -i fichier.txt
>```
>🔍 Affiche le **numéro d'inode** du fichier ! 🚀
>
>#### Qu'est-ce qu'un **lien dur** ?
>Un **lien dur** est une entrée de répertoire supplémentaire qui pointe vers les **mêmes données (inode)** qu'un fichier existant. Contrairement à un **lien symbolique**, un lien dur est **indiscernable** du fichier d'origine.
>
>##### Caractéristiques clés :
>✅ Pointe directement vers le **même inode (données)** que le fichier d'origine.
>✅ **Indépendant** du fichier d'origine (la suppression de l'un n'affecte **pas** l'autre).
>✅ Toute modification s'applique aux deux fichiers puisqu'ils partagent des **données identiques**.
>✅ Doit être sur le **même système de fichiers** (contrairement aux liens symboliques, qui peuvent traverser les systèmes de fichiers).
>✅ Pas un raccourci, c'est une **vraie référence** au fichier.
>
>##### Exemple (Linux) :
>```bash
touch fichier.txt          # Créer un fichier
ln fichier.txt lien_dur   # Créer un lien dur
```
>👉 Maintenant, `fichier.txt` et `lien_dur` sont **identiques** :
>- La modification de l'un modifie l'autre.
>- La suppression de `fichier.txt` n'affecte **pas** `lien_dur`.
>
>##### Différence avec un **lien symbolique** :
>| **Caractéristique** | **Lien dur** | **Lien symbolique** |
>|---|---|---|
>| Pointe vers | Inode (données réelles) | Nom de fichier (chemin) |
>| Fonctionne si l'original est supprimé ? | ✅ Oui | ❌ Non (lien brisé) |
>| Peut traverser les systèmes de fichiers ? | ❌ Non | ✅ Oui |
>
>##### Vérifier avec `ls -li` (inode) :
>```bash
>ls -li fichier.txt lien_dur
```
>🔍 S'ils ont le **même numéro d'inode**, c'est un lien dur ! 🚀

---

### `execve()`

> #include <unistd.h>
>
> #include <sys/types.h>
```c
int execve(const char *pathname, char *const argv[], char *const envp[]);
```
-   `pathname` : Une chaîne représentant le chemin absolu ou relatif du fichier exécutable à exécuter.
-   `argv` : Un tableau de pointeurs vers les arguments du programme, où `argv[0]` est généralement le nom du programme, et le dernier élément doit être `NULL`.
-   `envp` : Un tableau de pointeurs vers les variables d'environnement du nouveau programme, terminé par `NULL`.
-   **Retourne** : Ne retourne pas en cas de succès (le processus actuel est remplacé). Retourne `-1` en cas d'erreur, avec `errno` défini en conséquence.

La fonction `execve()` remplace l'image mémoire du processus appelant par un **nouveau programme** spécifié par `pathname`. Contrairement à `fork()`, elle ne **crée pas un nouveau processus** mais transforme le processus existant en nouveau programme tout en conservant le **même PID**.

#### Exécution d'un nouveau programme
Lorsque `execve()` est appelée, le processus actuel est **complètement remplacé** par le programme cible. Le nouveau programme hérite de certaines caractéristiques du processus d'origine, telles que les **descripteurs de fichiers ouverts**, mais il ne **conserve pas la pile, le tas ou les segments de code précédents**.

-   **`argv` (arguments du programme)** : Utilisé pour passer des arguments de ligne de commande au programme exécuté, de la même manière que l'exécution d'une commande dans un terminal.
-   **`envp` (variables d'environnement)** : Définit un environnement personnalisé pour le processus, utile pour modifier le comportement du programme.

#### Différence avec les autres fonctions `exec`
-   `execve()` est la **fonction de plus bas niveau** de la famille `exec`, interagissant directement avec le système.
-   `execl()` et `execv()` sont des variantes plus simples qui n'incluent pas `envp`.
-   `execle()` et `execve()` permettent de spécifier un environnement personnalisé.

#### Gestion des erreurs
`execve()` échoue et retourne `-1` dans plusieurs cas :
-   Si le fichier n'existe pas (`ENOENT`).
-   Si le fichier n'est pas exécutable (`EACCES`).
-   Si le programme dépasse les limites de mémoire du système (`ENOMEM`).
-   Si `argv` ou `envp` est malformé (`EFAULT`).

La fonction `execve()` est essentielle pour implémenter un shell (tel que `minishell`), car elle permet d'exécuter des commandes externes en remplaçant le processus du shell par la commande demandée.

#### **Dans Minishell**
Dans **Minishell**, vous appelez `execve()` pour :
✅ Exécuter une commande externe (par exemple, `ls -l`)
✅ Rechercher la commande dans `$PATH` si ce n'est pas un chemin absolu
✅ Lancer un processus enfant avec `fork()` pour éviter de remplacer Minishell
✅ Gérer les pipes et les redirections avant d'exécuter la commande

---

### `dup()`

> #include <unistd.h>
```c
int dup(int oldfd);
```
-   `oldfd` : Un descripteur de fichier faisant référence à un fichier ouvert.
-   **Retourne** : Un nouveau descripteur de fichier qui fait référence au même fichier que `oldfd`, ou `-1` en cas d'erreur avec `errno` défini en conséquence.

La fonction `dup()` crée un duplicata du descripteur de fichier `oldfd` et retourne le descripteur de fichier disponible le plus bas. Le nouveau descripteur fait référence au **même fichier** que `oldfd`, ce qui signifie qu'ils partagent le même décalage de fichier et les mêmes indicateurs d'état de fichier.

#### **Duplication de descripteurs de fichiers**
Lorsque `dup()` est appelée, elle trouve le descripteur de fichier disponible le plus bas et l'attribue au duplicata. Le nouveau descripteur de fichier et l'original peuvent être utilisés de manière interchangeable pour lire ou écrire dans le fichier.

#### **Exemple d'utilisation**
Un cas d'utilisation courant de `dup()` est la redirection de l'entrée, de la sortie ou de l'erreur standard. Par exemple, la duplication de `stdout` vers un autre descripteur permet de modifier l'endroit où la sortie est écrite tout en préservant le flux de sortie d'origine.

#### **Différence entre `dup()` et `dup2()`**
-   `dup()` **retourne toujours le descripteur de fichier disponible le plus bas**.
-   `dup2(int oldfd, int newfd)` permet de spécifier le numéro exact du nouveau descripteur de fichier, en fermant d'abord `newfd` si nécessaire.

#### **Gestion des erreurs**
`dup()` peut échouer dans plusieurs cas :
-   Si `oldfd` n'est pas un descripteur de fichier valide, il retourne `-1` avec `errno` défini sur `EBADF`.
-   Si le système manque de descripteurs de fichiers, il retourne `-1` avec `errno` défini sur `EMFILE`.

L'utilisation de `dup()` est utile dans **Minishell** lors de la gestion des **redirections d'E/S**, permettant aux commandes de lire ou d'écrire dans des fichiers au lieu de l'entrée/sortie standard.

#### **Dans Minishell**
Dans **Minishell**, vous utiliserez `dup()` pour :
✅ **Sauvegarder et restaurer `stdin` et `stdout`** lors de la gestion des redirections (`>`, `<`)
✅ **Gérer les pipes (`|`)** en redirigeant correctement l'entrée/sortie du processus
✅ **Prévenir les problèmes de redirection permanente** en restaurant les descripteurs de fichiers d'origine après l'exécution

Sans `dup()`, vos redirections et pipes pourraient interférer avec l'affichage et l'exécution de votre shell !

---

### `dup2()`

> #include <unistd.h>
```c
int dup2(int oldfd, int newfd);
```
-   `oldfd` : Le descripteur de fichier à dupliquer.
-   `newfd` : Le descripteur de fichier à remplacer. Si `newfd` est déjà ouvert, il sera fermé avant d'être réutilisé.
-   **Retourne** : Le nouveau descripteur de fichier (`newfd`), ou `-1` en cas d'erreur avec `errno` défini en conséquence.

La fonction `dup2()` duplique le descripteur de fichier `oldfd` vers `newfd`. Si `newfd` est déjà ouvert, il est d'abord fermé avant d'être remplacé par `oldfd`. Les deux descripteurs de fichiers font alors référence au même fichier, ce qui signifie qu'ils partagent le même décalage de fichier et les mêmes indicateurs d'état de fichier.

#### **Cas d'utilisation clés**
-   **Redirection** : `dup2()` est couramment utilisé pour la **redirection d'E/S**, comme la redirection de `stdout` ou `stderr` vers un fichier ou un pipe. En spécifiant `STDOUT_FILENO` (1) comme `newfd`, vous pouvez rediriger la sortie vers un fichier.
-   **Contrôle des descripteurs de fichiers** : Il est utile lorsque vous devez contrôler ou gérer le descripteur de fichier qu'un processus utilise, en particulier dans les processus enfants (par exemple, avec `fork()`).

#### **Différence entre `dup()` et `dup2()`**
-   `dup2()` vous permet de spécifier le numéro exact du nouveau descripteur de fichier (`newfd`).
-   `dup()` retourne toujours le **descripteur de fichier disponible le plus bas**.

#### **Gestion des erreurs**
`dup2()` peut échouer dans plusieurs cas :
-   Si `oldfd` n'est pas un descripteur de fichier valide, il retourne `-1` avec `errno` défini sur `EBADF`.
-   Si le processus manque de descripteurs de fichiers, il retourne `-1` avec `errno` défini sur `EMFILE`.

#### **Dans Minishell**
Dans **Minishell**, vous utiliserez `dup2()` pour :
✅ **Rediriger l'entrée/sortie** pour gérer les redirections (`>`, `<`) et les pipes (`|`)
✅ **Rediriger `stdout` vers un fichier** lors de l'implémentation de la redirection de sortie
✅ **Rediriger `stdin`** depuis un fichier lors de l'implémentation de la redirection d'entrée
✅ **Éviter les fuites de descripteurs de fichiers** en gérant correctement les descripteurs de fichiers lors de la gestion des pipes et des redirections

---

### `pipe()`

> #include <unistd.h>
```c
int pipe(int pipefd[2]);
```
-   `pipefd` : Un tableau de deux entiers. Le premier élément (`pipefd[0]`) est l'extrémité de lecture du pipe, et le second élément (`pipefd[1]`) est l'extrémité d'écriture.
-   **Retourne** : `0` en cas de succès, ou `-1` en cas d'erreur avec `errno` défini en conséquence.

La fonction `pipe()` crée un pipe, un canal de communication unidirectionnel utilisé pour transférer des données entre les processus. Elle configure deux descripteurs de fichiers : un pour lire depuis le pipe et un autre pour y écrire. Après avoir appelé `pipe()`, les données écrites dans `pipefd[1]` peuvent être lues depuis `pipefd[0]`.

#### **Cas d'utilisation clés**
-   **Communication inter-processus (IPC)** : Les pipes sont couramment utilisés dans un shell pour rediriger la sortie d'une commande vers l'entrée d'une autre (par exemple, avec l'opérateur `|`).
-   **Transfert de données entre processus** : Ils permettent de passer directement la sortie d'un processus à un autre, sans utiliser de fichiers temporaires.

#### **Comment ça marche**
Après avoir appelé `pipe()`, les descripteurs de fichiers `pipefd[0]` et `pipefd[1]` peuvent être utilisés comme n'importe quel autre descripteur de fichier. L'extrémité d'écriture (`pipefd[1]`) peut être utilisée pour envoyer des données, tandis que l'extrémité de lecture (`pipefd[0]`) peut être utilisée pour recevoir des données. Vous utilisez généralement `dup2()` pour rediriger l'entrée ou la sortie standard d'un processus vers ou depuis le pipe.
Par exemple, dans un shell, lorsqu'un utilisateur entre une commande comme :
```sh
ls | grep ".c"
```
`pipe()` sera utilisé pour connecter la sortie de `ls` (via `pipefd[1]`) à l'entrée de `grep` (via `pipefd[0]`).

#### **Gestion des erreurs**
`pipe()` peut échouer dans plusieurs cas :
-   Si le système manque de descripteurs de fichiers, il retourne `-1` avec `errno` défini sur `EMFILE`.
-   S'il y a un problème lors de la création du pipe en raison d'une limitation du système, il retourne `-1` avec `errno` défini sur `ENFILE`.

#### **Dans Minishell**
Dans **Minishell**, vous utiliserez `pipe()` pour :
✅ **Créer un canal de communication** entre les processus lors de l'implémentation des pipes (`|`)
✅ **Connecter la sortie d'une commande** à l'entrée d'une autre, permettant d'enchaîner les commandes
✅ **Faciliter une communication inter-processus efficace** sans écrire dans des fichiers temporaires

---

### `opendir()`

> #include <dirent.h>
```c
DIR *opendir(const char *dirname);
```
-   `dirname` : Une chaîne représentant le chemin du répertoire à ouvrir.
-   **Retourne** : Un pointeur vers un objet `DIR` en cas de succès, ou `NULL` en cas d'erreur avec `errno` défini en conséquence.

La fonction `opendir()` est utilisée pour ouvrir un flux de répertoire correspondant au répertoire spécifié par `dirname`. Elle retourne un pointeur vers un objet `DIR`, qui peut être utilisé avec d'autres fonctions liées aux répertoires comme `readdir()` et `closedir()` pour lire le contenu du répertoire ou fermer le répertoire lorsque vous avez terminé. Le pointeur `DIR` retourné représente le flux de répertoire et est utilisé pour interagir avec les entrées du répertoire.

#### **Cas d'utilisation clés**
-   **Parcours de répertoire** : `opendir()` est couramment utilisé dans les applications de gestion de fichiers pour parcourir ou lister les fichiers d'un répertoire.
-   **Lecture du contenu d'un répertoire** : Après avoir ouvert un répertoire avec `opendir()`, vous pouvez utiliser `readdir()` pour parcourir les entrées du répertoire.

#### **Comment ça marche**
Une fois qu'un répertoire est ouvert avec succès à l'aide de `opendir()`, vous pouvez lire son contenu en appelant `readdir()`, qui retourne un pointeur vers une `struct dirent` représentant chaque entrée (par exemple, fichier ou sous-répertoire). Pour fermer le flux de répertoire, vous utilisez `closedir()`.
Par exemple :
```c
DIR *dir = opendir("/home/user/documents");
if (dir) {
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("Trouvé : %s\n", entry->d_name);
    }
    closedir(dir);
}
```

#### **Gestion des erreurs**
`opendir()` peut échouer dans plusieurs cas :
-   Si le répertoire n'existe pas, il retourne `NULL` avec `errno` défini sur `ENOENT`.
-   Si l'utilisateur n'a pas l'autorisation de lire le répertoire, il retourne `NULL` avec `errno` défini sur `EACCES`.
-   S'il y a une erreur de ressource système, il retourne `NULL` avec `errno` défini sur `EMFILE`.

#### **Dans Minishell**
Dans **Minishell**, vous utiliserez `opendir()` pour :
✅ **Ouvrir des répertoires** lors de l'implémentation de commandes comme `ls` ou `cd` pour lister ou naviguer dans les répertoires.
✅ **Lire le contenu d'un répertoire** pour récupérer les fichiers et sous-répertoires d'un chemin spécifié.
✅ **Faciliter l'exploration des répertoires** dans votre shell, offrant des fonctionnalités aux utilisateurs pour parcourir et interagir avec le système de fichiers.

>#### Qu'est-ce qu'un **répertoire** ?
>Un **répertoire** est un type de fichier spécial qui **stocke des références à d'autres fichiers** (y compris leurs numéros d'inode). Il agit comme une **table de correspondance** qui mappe les noms de fichiers aux inodes.
>
>##### Un répertoire est-il un inode ?
>- Un **répertoire lui-même a un inode**, tout comme les fichiers réguliers.
>- L'**inode d'un répertoire** stocke des **métadonnées** (autorisations, propriétaire, horodatages, etc.), mais au lieu de pointer vers des données de fichier, il pointe vers **une liste de noms de fichiers et leurs inodes correspondants**.
>
>##### Comment fonctionnent les répertoires :
>- Lorsque vous créez un **nouveau fichier**, le système :
>   - Alloue un **inode** pour celui-ci.
>   - Ajoute une **entrée dans le répertoire** liant le nom de fichier au numéro d'inode.
>- Lorsque vous **listez un répertoire (`ls -l`)**, il lit l'inode du répertoire pour trouver les noms de fichiers et récupère leurs inodes pour les métadonnées.
>
>##### Vérifier le contenu d'un répertoire avec `ls -i` :
>```bash
>ls -i /home/user
>```
>📌 Cela affichera les numéros d'inode de tous les fichiers et sous-répertoires à l'intérieur de `/home/user`. 🚀

---

### readdir()

> #include <dirent.h>
```c
struct dirent *readdir(DIR *dirp);
```
-   `dirp` : Un pointeur vers l'objet `DIR` retourné par `opendir()`, représentant le flux de répertoire à lire.
-   **Retourne** : Un pointeur vers une `struct dirent` représentant la prochaine entrée de répertoire en cas de succès, ou `NULL` lorsqu'il n'y a plus d'entrées disponibles ou qu'une erreur se produit.

La fonction `readdir()` lit la prochaine entrée du flux de répertoire référencé par `dirp`. Elle retourne un pointeur vers une `struct dirent` contenant des informations sur l'entrée de répertoire (comme le nom du fichier ou du répertoire). Lorsque la fin du répertoire est atteinte, ou si une erreur se produit, elle retourne `NULL`.

#### **Cas d'utilisation clés**
-   **Parcours de répertoire** : `readdir()` est utilisé pour parcourir le contenu d'un répertoire qui a été ouvert avec `opendir()`.
-   **Listage des entrées de répertoire** : Il est souvent utilisé en combinaison avec `opendir()` et `closedir()` pour lister ou traiter les fichiers et sous-répertoires d'un répertoire.

#### **Comment ça marche**
Après avoir ouvert un répertoire avec `opendir()`, vous pouvez appeler `readdir()` pour obtenir la prochaine entrée de répertoire. Chaque appel à `readdir()` retourne le prochain fichier ou répertoire dans le flux de répertoire. Si `readdir()` atteint la fin du répertoire, il retourne `NULL`.
Par exemple :
```c
DIR *dir = opendir("/home/user/documents");
if (dir) {
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("Trouvé : %s\n", entry->d_name);
    }
    closedir(dir);
}
```

#### **Gestion des erreurs**
`readdir()` peut échouer dans plusieurs cas :
-   Si le flux de répertoire n'est pas valide (par exemple, si le répertoire n'a pas été ouvert avec `opendir()`), il retourne `NULL`.
-   S'il y a une erreur lors de la lecture du répertoire, il retourne `NULL` et définit `errno` sur un code d'erreur approprié.

#### **Dans Minishell**
Dans **Minishell**, vous utiliserez `readdir()` pour :
✅ **Lire le contenu d'un répertoire** après l'avoir ouvert avec `opendir()` pour lister les fichiers et sous-répertoires.
✅ **Parcourir les répertoires** lors de l'implémentation de commandes comme `ls` ou `find`.
✅ **Vérifier la présence de fichiers spécifiques** lors de l'implémentation de fonctionnalités comme l'auto-complétion ou la recherche de fichiers.

---

### closedir()

> #include <dirent.h>
```c
int closedir(DIR *dirp);
```
-   `dirp` : Un pointeur vers l'objet `DIR` représentant le flux de répertoire à fermer.
-   **Retourne** : `0` en cas de succès, ou `-1` en cas d'erreur avec `errno` défini en conséquence.

La fonction `closedir()` est utilisée pour fermer un flux de répertoire qui a été précédemment ouvert par `opendir()`. Après avoir appelé `closedir()`, le flux de répertoire n'est plus valide et ne peut pas être utilisé avec `readdir()` ou toute autre fonction liée aux répertoires. Il est important de fermer le flux de répertoire après avoir fini de lire un répertoire pour libérer les ressources système.

#### **Cas d'utilisation clés**
-   **Gestion des ressources** : `closedir()` garantit que les ressources système allouées pour le flux de répertoire sont libérées après utilisation.
-   **Nettoyage de répertoire** : Après avoir parcouru les entrées d'un répertoire avec `readdir()`, vous devez appeler `closedir()` pour fermer le flux de répertoire et éviter les fuites de ressources.

#### **Comment ça marche**
Lorsque vous avez fini de lire un répertoire à l'aide de `opendir()` et `readdir()`, vous devez toujours appeler `closedir()` pour fermer le flux de répertoire. Cela libère toutes les ressources système qui lui sont associées.
Par exemple :
```c
DIR *dir = opendir("/home/user/documents");
if (dir) {
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("Trouvé : %s\n", entry->d_name);
    }
    closedir(dir);
}
```

#### **Gestion des erreurs**
`closedir()` peut échouer dans plusieurs cas :
-   Si `dirp` n'est pas un pointeur valide vers un flux de répertoire ouvert (par exemple, si le répertoire n'a jamais été ouvert ou a déjà été fermé), il retourne `-1` et définit `errno` sur `EBADF`.
-   S'il y a une erreur système lors de la fermeture du répertoire, il retourne `-1` et définit `errno` sur un code d'erreur approprié.

#### **Dans Minishell**
Dans **Minishell**, vous utiliserez `closedir()` pour :
✅ **Fermer le flux de répertoire** après avoir lu le contenu du répertoire avec `readdir()` pour libérer les ressources système.
✅ **Prévenir les fuites de ressources** lors du traitement de plusieurs répertoires lors d'opérations telles que le listage de fichiers ou la navigation dans le système de fichiers.
✅ **Assurer un nettoyage correct** après les opérations sur les répertoires pour maintenir une gestion efficace des ressources.

---

### `isatty()`

> #include <unistd.h>

```c
int isatty(int fd);
```

-   `fd` : Un descripteur de fichier, généralement `STDIN_FILENO`, `STDOUT_FILENO` ou `STDERR_FILENO`.
-   **Retourne** : `1` si `fd` fait référence à un terminal, ou `0` si ce n'est pas le cas. En cas d'erreur, il retourne `0` et définit `errno`.

La fonction `isatty()` vérifie si le descripteur de fichier donné correspond à un terminal (TTY). Elle est couramment utilisée pour déterminer si un programme s'exécute de manière interactive dans un shell ou si son entrée/sortie est redirigée (par exemple, vers un fichier ou un pipe).

#### **Cas d'utilisation clés**
-   **Détection du mode interactif** : De nombreux programmes, y compris les shells, utilisent `isatty(STDIN_FILENO)` pour vérifier s'ils reçoivent une entrée d'un utilisateur ou d'un fichier.
-   **Ajustement du format de sortie** : Des programmes comme `ls` utilisent `isatty(STDOUT_FILENO)` pour décider s'il faut afficher la sortie en colonnes (terminal interactif) ou dans une liste simple (lorsqu'elle est redirigée vers un fichier).
-   **Gestion correcte des redirections** : Les scripts ou les commandes peuvent adapter leur comportement selon qu'ils interagissent avec un utilisateur ou un autre programme.

#### **Comment ça marche**
`isatty(fd)` vérifie en interne si le descripteur de fichier fait référence à un périphérique de caractères (un terminal). Il est souvent utilisé en combinaison avec `ttyname()` pour récupérer le nom du terminal.

Par exemple, dans un shell :
```sh
echo "hello" | cat
```
Ici, `isatty(STDIN_FILENO)` à l'intérieur de `cat` retournerait `0`, indiquant que l'entrée provient d'un pipe plutôt que d'un terminal.

#### **Gestion des erreurs**
-   Si `fd` est invalide ou fermé, `isatty()` retourne `0` et définit `errno` sur `EBADF`.
-   Si `fd` fait référence à un fichier, un socket ou un pipe, il retourne également `0`, sans définir `errno` (puisque ce n'est pas une erreur).

#### **Dans Minishell**
Dans **Minishell**, vous utiliserez `isatty()` pour :
✅ **Vérifier si le shell s'exécute dans un terminal interactif** pour décider s'il faut afficher des invites.
✅ **Déterminer si l'entrée provient d'un utilisateur ou d'un script** pour gérer les modes interactifs et non interactifs.
✅ **Adapter le comportement en fonction de la redirection de la sortie**, comme les différences de formatage dans des commandes comme `ls`.

>#### `STDIN_FILENO`, `STDOUT_FILENO` et `STDERR_FILENO`
>
>Ce sont des **macros de descripteurs de fichiers** définies dans `<unistd.h>` qui représentent les flux d'entrée, de sortie et d'erreur standard dans les systèmes de type Unix.
>
>| Macro | Valeur | Description |
>|---|---|---|
>| `STDIN_FILENO` | **0** | Entrée standard (clavier par défaut) |
>| `STDOUT_FILENO` | **1** | Sortie standard (terminal par défaut) |
>| `STDERR_FILENO` | **2** | Erreur standard (également terminal par défaut) |
>
>##### Comment ils sont utilisés :
>**Lecture depuis l'entrée standard**
>```c
>char buffer[100];
>read(STDIN_FILENO, buffer, 100);  // Lit l'entrée de l'utilisateur
>```
>
>**Écriture sur la sortie standard**
>```c
>write(STDOUT_FILENO, "Hello, world!\n", 14);  // Affiche sur le terminal
>```
>
>**Écriture d'un message d'erreur sur l'erreur standard**
>```c
>write(STDERR_FILENO, "Erreur : Entrée invalide !\n", 22);  // Affiche les messages d'erreur
>```
>
>##### Pourquoi utiliser ces macros ?
>✅ Rend le code plus **portable** et **lisible** au lieu d'utiliser des nombres bruts (`0, 1, 2`).
>✅ Utile lors de la **redirection** de l'entrée/sortie dans les shells (par exemple, `ls > output.txt`, `./program < input.txt`).
>
>📌 **Dans Minishell**, vous utiliserez ces descripteurs de fichiers pour **gérer les redirections et les pipes**, en veillant à ce que l'entrée/sortie soit correctement gérée. 🚀

---

### `ttyname()`

> #include <unistd.h>

```c
char *ttyname(int fd);
```

-   `fd` : Un descripteur de fichier, généralement `STDIN_FILENO`, `STDOUT_FILENO` ou `STDERR_FILENO`.
-   **Retourne** : Un pointeur vers une chaîne contenant le nom de fichier du terminal associé à `fd`, ou `NULL` en cas d'erreur avec `errno` défini en conséquence.

La fonction `ttyname()` récupère le nom du périphérique de terminal associé au descripteur de fichier donné. Elle est utile pour identifier à quel terminal un processus est connecté.

#### **Cas d'utilisation clés**
-   **Trouver le périphérique de terminal** : Aide à déterminer quel fichier `/dev/tty*` correspond au terminal du processus.
-   **Débogage et journalisation** : Certains programmes enregistrent avec quel terminal ils interagissent.
-   **Assurer une exécution interactive** : Peut être utilisé pour confirmer que l'entrée/sortie est liée à un terminal réel.

#### **Comment ça marche**
`ttyname(fd)` vérifie si `fd` est un terminal (en utilisant `isatty(fd)`) et, si c'est le cas, récupère le chemin du périphérique de terminal associé (par exemple, `/dev/pts/0` sur Linux).

Exemple d'utilisation en C :
```c
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("Terminal : %s\n", ttyname(STDIN_FILENO));
    return 0;
}
```
Si exécuté dans un terminal, cela pourrait afficher :
```
Terminal : /dev/pts/1
```
Si l'entrée est redirigée, `ttyname(STDIN_FILENO)` retourne `NULL`.

#### **Gestion des erreurs**
-   Si `fd` est invalide ou n'est pas un terminal, `ttyname()` retourne `NULL` et définit `errno` sur `EBADF` ou `ENOTTY`.

#### **Dans Minishell**
Dans **Minishell**, vous utiliserez `ttyname()` pour :
✅ **Identifier le périphérique de terminal** lors de la gestion du contrôle des tâches ou du débogage.
✅ **Vérifier si le shell est attaché à un terminal** pour les fonctionnalités du mode interactif.
✅ **Afficher les informations sur le terminal** lors de l'exécution de commandes intégrées comme `tty`.

---

### `ttyslot()`

> # #include <unistd.h>

```c
int ttyslot(void);
```

-   **Retourne** : L'index du terminal actuel dans `/etc/ttys`, ou `0` en cas d'échec.

La fonction `ttyslot()` trouve le numéro d'emplacement du terminal actuel dans la liste des terminaux du système. Elle est utile pour identifier quelle entrée dans `/etc/ttys` correspond au terminal de contrôle du processus.

#### **Cas d'utilisation clés**
-   **Déterminer l'emplacement du terminal** : Aide à localiser la position du terminal dans les bases de données du système.
-   **Gestion du suivi de session** : Peut être utile pour la gestion des sessions multi-utilisateurs.
-   **Journalisation et surveillance des processus** : Permet aux systèmes de journalisation d'associer les sessions utilisateur aux entrées de terminal.

#### **Comment ça marche**
La fonction recherche dans `/etc/ttys` (ou la liste interne des terminaux du système) le terminal de contrôle du processus et retourne son index. Cet index est utile pour accéder aux informations système associées.

Exemple d'utilisation en C :
```c
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("Emplacement du terminal : %d\n", ttyslot());
    return 0;
}
```
Si le processus est connecté à un terminal, `ttyslot()` retourne un entier positif représentant sa position dans la liste des terminaux. Sinon, il retourne `0`.

#### **Gestion des erreurs**
-   Retourne `0` si aucun terminal associé n'est trouvé.

#### **Dans Minishell**
Dans **Minishell**, vous utiliserez `ttyslot()` pour :
✅ **Déterminer le numéro d'emplacement** du terminal pour la gestion des sessions.
✅ **Intégrer avec la journalisation ou le contrôle des tâches** en identifiant le terminal actif.
✅ **Améliorer le débogage** en récupérant la position du terminal dans la liste du système.

---

### `ioctl()`

> #include <sys/ioctl.h>
>
> #include <unistd.h>

```c
int ioctl(int fd, unsigned long request, ...);
```

-   `fd` : Le descripteur de fichier du périphérique ou du terminal à contrôler.
-   `request` : Une commande spécifiant l'opération à effectuer.
-   `...` : Un troisième argument facultatif, en fonction de la `request`.
-   **Retourne** : `0` en cas de succès, `-1` en cas d'échec avec `errno` défini en conséquence.

La fonction `ioctl()` est un appel système qui fournit un moyen d'envoyer des commandes de contrôle spécifiques au périphérique aux descripteurs de fichiers. Elle est largement utilisée pour configurer les paramètres du terminal, les périphériques réseau et d'autres opérations liées au matériel.

#### **Cas d'utilisation clés**
-   **Contrôle du terminal** : Modifier les attributs du terminal comme la taille de la fenêtre (`TIOCGWINSZ`).
-   **Interaction matérielle** : Communiquer avec les pilotes de périphériques (par exemple, les pilotes de disque, de réseau ou de son).
-   **Paramètres de socket et de réseau** : Récupérer ou modifier les paramètres de l'interface réseau.

#### **Comment ça marche**
`ioctl()` prend un descripteur de fichier, un code de requête et un argument facultatif. La requête détermine l'action effectuée sur le descripteur de fichier. Les exemples courants incluent :

-   **Obtenir la taille de la fenêtre du terminal** :
    ```c
    #include <sys/ioctl.h>
    #include <stdio.h>
    #include <unistd.h>

    int main(void)
    {
        struct winsize w;
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0)
            printf("Taille du terminal : %d lignes × %d colonnes\n", w.ws_row, w.ws_col);
        else
            perror("ioctl");
        return 0;
    }
    ```
    Ici, `TIOCGWINSZ` récupère les dimensions du terminal.

-   **Contrôler une interface réseau** :
    ```c
    struct ifreq ifr;
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    strcpy(ifr.ifr_name, "eth0");
    ioctl(sock, SIOCGIFADDR, &ifr);
    ```

#### **Gestion des erreurs**
-   Retourne `-1` si `fd` est invalide ou ne prend pas en charge `ioctl()`.
-   `errno` est défini en conséquence (par exemple, `ENOTTY` si le descripteur de fichier n'est pas un terminal).

#### **Dans Minishell**
Dans **Minishell**, vous utiliserez `ioctl()` pour :
✅ **Récupérer dynamiquement la taille de la fenêtre du terminal** (`TIOCGWINSZ`)
✅ **Modifier les paramètres du terminal** lors de l'implémentation de fonctionnalités comme l'entrée en mode brut
✅ **Gérer les descripteurs de fichiers spéciaux** qui nécessitent un contrôle direct

---

### `getenv()`

> #include <stdlib.h>

```c
char *getenv(const char *name);
```

-   `name` : Le nom de la variable d'environnement à récupérer.
-   **Retourne** : Un pointeur vers la valeur de la variable d'environnement, ou `NULL` si elle n'est pas trouvée.

La fonction `getenv()` récupère la valeur d'une variable d'environnement en recherchant la variable globale `environ`, qui contient l'environnement du processus actuel.

#### **Cas d'utilisation clés**
-   **Accès aux variables d'environnement** : Récupérer des chemins (`PATH`), des détails sur l'utilisateur (`HOME`, `USER`) et des paramètres système.
-   **Configuration du comportement du programme** : Vérifier `SHELL`, `LANG` ou `TERM` pour adapter l'exécution.
-   **Interaction avec des programmes externes** : Les scripts et les applications s'appuient souvent sur les variables d'environnement pour la configuration.

#### **Comment ça marche**
`getenv()` recherche dans l'environnement le nom de la variable donnée et retourne un pointeur vers sa valeur. Le pointeur retourné ne doit **pas** être modifié ou libéré, car il fait directement référence à la mémoire de l'environnement du processus.

Exemple d'utilisation :
```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *path = getenv("PATH");
    if (path)
        printf("PATH : %s\n", path);
    else
        printf("Variable PATH non trouvée.\n");
    return 0;
}
```

#### **Gestion des erreurs**
-   Si `name` est `NULL`, le comportement est indéfini.
-   Si la variable n'est pas trouvée, `getenv()` retourne `NULL`.

#### **Dans Minishell**
Dans **Minishell**, vous utiliserez `getenv()` pour :
✅ **Récupérer des variables d'environnement** comme `PATH` pour localiser les commandes exécutables
✅ **Accéder aux variables liées à l'utilisateur** (`HOME`, `PWD`, etc.) pour les commandes intégrées (`cd`, `echo`)
✅ **Personnaliser le comportement du shell** en s'adaptant à `SHELL`, `TERM` et d'autres paramètres

---

### `tcsetattr()`

> #include <termios.h>
```c
int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);
```

-   `fd` : Descripteur de fichier du terminal (généralement `STDIN_FILENO`).
-   `optional_actions` : Spécifie quand les modifications prennent effet (`TCSANOW`, `TCSADRAIN` ou `TCSAFLUSH`).
-   `termios_p` : Pointeur vers une `struct termios` contenant les nouveaux attributs du terminal.
-   **Retourne** : `0` en cas de succès, ou `-1` en cas d'erreur avec `errno` défini en conséquence.

La fonction `tcsetattr()` définit les attributs d'un périphérique de terminal, modifiant son comportement en ce qui concerne le traitement des entrées et des sorties.

#### **Cas d'utilisation clés**
-   **Désactivation du mode canonique** : Permet de lire l'entrée caractère par caractère au lieu de ligne par ligne.
-   **Modification des paramètres d'écho** : Contrôle si l'entrée de l'utilisateur (par exemple, les mots de passe) est affichée.
-   **Configuration des caractères de contrôle spéciaux** : Ajuste le comportement pour les signaux comme `Ctrl+C` ou `Ctrl+Z`.

#### **Comment ça marche**
Pour modifier les paramètres du terminal, récupérez les attributs actuels à l'aide de `tcgetattr()`, modifiez-les et appliquez-les avec `tcsetattr()`.

Exemple : Désactiver l'écho de l'entrée de l'utilisateur (utile pour les invites de mot de passe).
```c
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int main(void)
{
    struct termios term;

    tcgetattr(STDIN_FILENO, &term); // Obtenir les paramètres actuels
    term.c_lflag &= ~ECHO;          // Désactiver l'écho
    tcsetattr(STDIN_FILENO, TCSANOW, &term); // Appliquer les modifications

    printf("Entrez quelque chose : ");
    char input[100];
    fgets(input, sizeof(input), stdin);
    printf("\nVous avez entré : %s\n", input);

    term.c_lflag |= ECHO; // Réactiver l'écho
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    return 0;
}
```
