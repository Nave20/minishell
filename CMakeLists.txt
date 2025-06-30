cmake_minimum_required(VERSION 3.29)
project(minishell C)

set(CMAKE_C_STANDARD 11)

add_executable(minishell
        header/minishell.h
        src/minishell.c
        src/builtins/echo.c
        libft/ft_putendl_fd.c
        src/builtins/cd.c
        src/builtins/pwd.c
        src/builtins/env.c
        src/env_cmd.c
        src/pars_env.c
        src/dev_func.c
        src/builtins/export.c
        src/builtins/unset.c
        src/terminal.c
        src/builtins/hub.c
        src/builtins/exit.c
        src/exec/servo.c)
