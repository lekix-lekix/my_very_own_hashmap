/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lekix <lekix@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 10:52:08 by lekix             #+#    #+#             */
/*   Updated: 2026/04/06 11:09:02 by lekix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define HASH_OFFSET 2166136261
#define FNV_PRIME 16777619

#include <stdint.h>
#include <stdio.h>

uint32_t    hash(char *str)
{
    if (!str)
        return (-1);
    
    uint32_t hash = HASH_OFFSET;
    for (int i = 0; str[i]; i++)
    {
        hash ^= str[i];
        hash *= FNV_PRIME;
    }
    return (hash);
}

int main(int argc, char **argv)
{
    (void) argc;

    printf("hash = %u\n", hash(argv[1]));
}