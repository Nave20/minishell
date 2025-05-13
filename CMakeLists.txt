cmake_minimum_required(VERSION 3.29)
project(minishell C)

set(CMAKE_C_STANDARD 11)

add_executable(minishell
        header/minishell.h
        src/minishell.c)
