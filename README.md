# Minishell Project

## Description

Minishell is a simple UNIX command interpreter written in C that replicates the basic functionalities of a traditional shell, being bash this project main inspiration, This project is part of the 42 network curriculum, designed to deepen understanding of system calls, process creation, and manipulation, as well as the environments of a UNIX-like system.

## Features

- Command execution with full path (`/usr/bin/env`)
- Builtins: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Signal handling (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`) to mimic bash behavior
- Environment variable expansion and command history
- Simple pipe execution and basic redirections (`>`, `>>`, `<`, `<<`)
- Error handling and proper usage messages

## Installation

```bash
git clone https://github.com/FInacio97/minishell minishell
cd minishell
make
```
## Run
```
./minishell
```
## Authors

Rafa - https://github.com/rafaelva-z
Myself - https://github.com/FInacio97
