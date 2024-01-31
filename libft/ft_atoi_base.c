#include "libft.h"

// static int conditions(const char *base)
// {
//     int len_base;
//     int i;
//     int j;

//     len_base = ft_strlen(base);
//     i = 0;
//     if (len_base == 0 || len_base == 1)
//         return (0);
//     while (base[i] != '\0')
//     {
//         if (base[i] == '+' || base[i] == '-')
//             return (0);
//         j = i + 1;
//         while (base[j] != '\0')
//         {
//             if (base[i] == base[j])
//                 return (0);
//             j++;
//         }
//         i++;
//     }
//     return (1);
// }

static int in_base(char c, const char *base)
{
    int i;

    i = 0;
    while (base[i] != '\0')
    {
        if (c == base[i])
            return (1);
        i++;
    }
    return (0);
}

static int calculate_number(const char *str, const char *base, int i)
{
    int nb;
    int j;

    nb = 0;
    while (in_base(str[i], base) == 1)
    {
        j = 0;
        while (base[j] != str[i])
            j++;
        nb = nb * ft_strlen(base) + j;
        i++;
    }
    return (nb);
}

int ft_atoi_base(const char *str, const char *base)
{
    int i;
    int nb;

    nb = 0;
    // if (conditions(base) == 0)
        // return (nb);
    i = 0;
    nb = calculate_number(str, base, i);
    return (nb);
}