
<div align="center">
# 🐚 Minishell
 
> *As beautiful as a shell*
 
[![42 School](https://img.shields.io/badge/42-School-000000?style=for-the-badge&logo=42&logoColor=white)](https://42.fr)
[![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Makefile](https://img.shields.io/badge/Makefile-427819?style=for-the-badge&logo=gnu&logoColor=white)](https://www.gnu.org/software/make/)
[![Norminette](https://img.shields.io/badge/Norminette-passing-brightgreen?style=for-the-badge)](https://github.com/42School/norminette)
 
</div>

 
## 📋 Table des matières
 
- [Présentation](#-présentation)
- [Fonctionnalités](#-fonctionnalités)
- [Architecture & Parsing AST](#-architecture--parsing-ast)
- [Structures de données](#-structures-de-données)
- [Installation & Compilation](#-installation--compilation)
- [Utilisation](#-utilisation)
- [Builtins implémentés](#-builtins-implémentés)
- [Gestion des erreurs & signaux](#-gestion-des-erreurs--signaux)
---
 
## 🎯 Présentation
 
**Minishell** est un projet de l'école 42 consistant à recréer un shell fonctionnel inspiré de **bash**. L'objectif est de comprendre en profondeur le fonctionnement d'un interpréteur de commandes : lecture de l'entrée utilisateur, parsing, création de processus, gestion des redirections et des pipes.
 
Notre implémentation se distingue par l'utilisation d'un **AST (Abstract Syntax Tree)** pour le parsing, offrant une représentation hiérarchique et structurée des commandes avant leur exécution.
 
---
 
## ✨ Fonctionnalités
 
| Fonctionnalité | Statut |
|---|---|
| Prompt interactif | ✅ |
| Historique des commandes (`readline`) | ✅ |
| Pipes `\|` | ✅ |
| Redirections `<`, `>`, `>>` | ✅ |
| Here-document `<<` | ✅ |
| Variables d'environnement `$VAR` | ✅ |
| Code de retour `$?` | ✅ |
| Quotes simples `'` | ✅ |
| Quotes doubles `"` | ✅ |
| Signaux `Ctrl+C`, `Ctrl+D`, `Ctrl+\` | ✅ |
| Builtins (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`) | ✅ |
 
---
 
## 🌳 Architecture & Parsing AST
 
### Pourquoi un AST ?
 
Au lieu d'un parsing linéaire classique, nous avons construit un **Abstract Syntax Tree**. Cette approche représente la structure logique d'une commande shell de façon hiérarchique, ce qui rend l'exécution plus naturelle et facilite la gestion des cas complexes (pipes chaînés, redirections multiples).
 
### Pipeline de traitement
 
```
Input utilisateur
      │
      ▼
┌─────────────┐
│   LEXER     │  Tokenisation → liste chaînée de t_token
└─────────────┘
      │
      ▼  t_token*
┌─────────────┐
│   PARSER    │  Construction de l'AST → arbre de t_ast_node
└─────────────┘
      │
      ▼  t_ast_node*
┌─────────────┐
│  EXPANDER   │  Expansion des variables ($VAR, $?)
└─────────────┘
      │
      ▼
┌─────────────┐
│  EXECUTOR   │  Parcours récursif de l'AST + exécution
└─────────────┘
```
 
### Exemple d'AST
 
Pour la commande `echo hello | cat -e > out.txt` :
 
```
              [TOKEN_PIPE]
             /            \
    [TOKEN_STR]            [TOKEN_REDIR_OUT]
    args: ["echo","hello"] /               \
                  [TOKEN_STR]         args: ["out.txt"]
                  args: ["cat","-e"]
```
 
Les nœuds sont parcourus **récursivement** : l'exécuteur descend dans le fils gauche avant d'appliquer la redirection ou le pipe défini par le nœud courant.
 
---
 
## 🔧 Structures de données
 
```c
/* Types de tokens (lexer) et nœuds (AST) */
typedef enum e_enum_type
{
    TOKEN_STR,           // Chaîne, commande ou argument
    TOKEN_PIPE,          // |
    TOKEN_REDIR_IN,      // <
    TOKEN_REDIR_OUT,     // >
    TOKEN_REDIR_APPEND,  // >>
    TOKEN_REDIR_HEREDOC, // <<
    TOKEN_ENV_VAR,       // $VAR
}   t_enum_type;
 
/* Liste chaînée produite par le lexer */
typedef struct s_token
{
    t_enum_type     type;
    char            *value;
    struct s_token  *next;
}   t_token;
 
/* Nœud de l'AST construit par le parser */
typedef struct s_ast_node
{
    t_enum_type         type;
    int                 fd_heredoc; // fd du pipe du here-document
    char                **args;     // Commande + arguments (NULL-terminated)
    struct s_ast_node   *left;      // Fils gauche
    struct s_ast_node   *right;     // Fils droit
}   t_ast_node;
 
/* Variable d'environnement (liste chaînée) */
typedef struct s_env
{
    char         *key;
    char         *value;
    struct s_env *next;
}   t_env;
 
/* Structure globale du shell */
typedef struct s_data
{
    int         exit_code;   // Code de retour courant ($?)
    int         fd_in;       // fd d'entrée courant
    int         fd_out;      // fd de sortie courant
    int         old_fd_in;   // Sauvegarde stdin (restauration post-redirection)
    int         old_fd_out;  // Sauvegarde stdout
    t_env       *env;        // Liste des variables d'environnement
    t_ast_node  *ast;        // Racine de l'AST
}   t_data;
```
 
---
 
## 📁 Structure du projet
 
```
minishell/
├── Makefile
├── includes/
│   └── minishell.h
├── libft/
└── src/
    ├── main.c
    ├── lexer/
    │   ├── lexer.c           # Tokenisation de l'input
    │   ├── token_utils.c
    │   └── quotes.c          # Gestion des guillemets simples et doubles
    ├── parser/
    │   ├── parser.c          # Construction récursive de l'AST
    │   ├── ast_nodes.c       # Création des nœuds t_ast_node
    │   └── ast_free.c        # Libération mémoire de l'AST
    ├── expander/
    │   └── expander.c        # Expansion $VAR et $?
    ├── executor/
    │   ├── executor.c        # Parcours de l'AST et dispatch
    │   ├── pipes.c           # Gestion TOKEN_PIPE
    │   ├── redirections.c    # Gestion TOKEN_REDIR_*
    │   └── heredoc.c         # Gestion TOKEN_REDIR_HEREDOC + fd_heredoc
    ├── builtins/
    │   ├── echo.c
    │   ├── cd.c
    │   ├── pwd.c
    │   ├── export.c
    │   ├── unset.c
    │   ├── env.c
    │   └── exit.c
    └── utils/
        ├── signals.c         # Ctrl+C, Ctrl+D, Ctrl+\
        ├── env_utils.c       # Copie et manipulation de t_env
        └── error.c
```
 
---
 
## 🔧 Installation & Compilation
 
### Prérequis
 
- `gcc` ou `cc`
- `make`
- Bibliothèque `readline`
 
### Compilation
 
```bash
git clone https://github.com/jln-nguyen/minishell.git
cd minishell
 
make        # Compiler
make clean  # Supprimer les .o
make fclean # Tout supprimer
make re     # Recompiler depuis zéro
```
 
---
 
## 🚀 Utilisation
 
```bash
./minishell
```
 
Quelques exemples :
 
```bash
# Commande simple
minishell$ echo "Hello, World!"
 
# Pipe
minishell$ ls -la | grep .c | wc -l
 
# Redirections
minishell$ cat < input.txt > output.txt
minishell$ echo "ligne" >> fichier.txt
 
# Here-document
minishell$ cat << EOF
> Hello
> World
> EOF
 
# Variables d'environnement
minishell$ export MY_VAR=42
minishell$ echo $MY_VAR
minishell$ echo $?
 
# Pipes chaînés + redirection
minishell$ cat fichier.txt | grep "foo" | sort > result.txt
```
 
---
 
## 🛠 Builtins implémentés
 
| Builtin | Description |
|---|---|
| `echo [-n]` | Affiche du texte (`-n` supprime le retour à la ligne) |
| `cd [path]` | Change le répertoire courant (`-` pour le précédent) |
| `pwd` | Affiche le répertoire courant |
| `export [VAR=val]` | Exporte une variable dans l'environnement |
| `unset [VAR]` | Supprime une variable de l'environnement |
| `env` | Affiche les variables d'environnement |
| `exit [n]` | Quitte le shell avec un code de retour optionnel |
 
---
 
## ⚠️ Gestion des erreurs & signaux
 
| Situation | Comportement |
|---|---|
| `Ctrl+C` | Affiche un nouveau prompt (SIGINT) |
| `Ctrl+D` | Quitte le shell proprement (EOF) |
| `Ctrl+\` | Ignoré en mode interactif (SIGQUIT) |
| Commande introuvable | `command not found` → exit code `127` |
| Permission refusée | Message d'erreur → exit code `126` |
| Fichier introuvable (redirection) | Message d'erreur bash-like |
| Quotes non fermées | Erreur de syntaxe |
| Pipe sans commande | Erreur de syntaxe |
 
Le code de retour de la dernière commande est toujours accessible via `$?` et stocké dans `t_data.exit_code`.
 
---
 
<div align="center">
*Projet réalisé dans le cadre du cursus de l'école 42*
**Made with ❤️ by [jln-nguyen](https://github.com/jln-nguyen) and [BrendanVKM](https://github.com/BrendanVKM)*
 
</div>
