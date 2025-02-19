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