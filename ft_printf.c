# include "libftprintf.h"

int ft_param_handle(unsigned char flag)
{
    char    *paramset;
    size_t  paramlen;

    paramset = "cspdiuxX%";
    switch (flag)
    {
    case 'c':
        /* code */
        break;

    case 's':
        /* code */
        break;

    case 'p':
        /* code */
        break;

    case 'd':
        /* code */
        break;

    case 'i':
        /* code */
        break;

    case 'u':
        /* code */
        break;

    case 'x':
        /* code */
        break;

    case 'X':
        /* code */
        break;

    case '%':
        /* code */
        break;
   
    default:
        paramlen = 0;
        break;
    }
    return (paramlen);
}

int  ft_printf(const char *str, ...)
{
    va_list args;
    size_t  output_size;
    int     flag;
    char    *strtoprint;
    char    *tmpstr;
    char    **chains;

    va_start(args, str);
    if (!args)
        ft_putstr_fd(str, 1);
    else
        chains = ft_split(str, '%');

    while (chains)
    {
        if (!flag)
        {
            strtoprint = *chains;
            flag = 1;
        }
        else
        {
            output_size = ft_param_handle(**chains);
            //call flag function based on first letter if flag > 0
            tmpstr = strtoprint;
            strtoprint = ft_join(tmpstr[1], *chains);
            free(tmpstr);
        }
        chains++;
    }
    return (ft_strlen(strtoprint));
}