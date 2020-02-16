/*
** EPITECH PROJECT, 2019
** Default
** File description:
** Default
*/

#include <stdio.h>
#include <string.h>
#include "arp.h"

int parse_ip(const char *ip)
{
    int i = 0;

    while (ip[i]) {
        if (IS_NB(ip[i]) == 0 && ip[i] != '.')
            return (0);
        i++;
    }
    return (1);
}

int parse_broadcast(char **av)
{
    if (parse_ip(av[1]) == 0 || parse_ip(av[2]) == 0) {
        return (84);
    }
    if (strcmp(av[4], "--printBroadcast") != 0) {
        return (84);
    }
    print_broadcast(av);
    return (0);
}

int parse_spoof(char **av)
{
    if (parse_ip(av[1]) == 0 || parse_ip(av[2]) == 0)
        return (84);
    if (strcmp(av[4], "--printSpoof") != 0)
        return (84);
    print_spoof(av);
    return (0);
}

int parse_attack(char **av)
{
    if (parse_ip(av[1]) == 0 || parse_ip(av[2]) == 0)
        return (84);
    launch_attack(av);
    return (0);
}

int parse_argv(int ac, char **av)
{
    if (ac < 4 || ac > 6) {
        dprintf(2, "Error: Not the right number of arguments\n");
        return (84);
    } else if (ac == 4)
        return (parse_attack(av));
    else if (ac == 5)
        return (parse_broadcast(av));
    return (parse_spoof(av));
}