#include <stdarg.h>
#include <unistd.h>
void    print_string(char *str, int *len)
{
    if (!str)
        str = "(null)";
    int i = 0;
    while (str[i])
        *len += write(1, &str[i++], 1);
}
void    print_number(long long num, int base, int *len)
{
    char    *hexa;
    hexa = "0123456789abcdef";
    if (num < 0)
    {
        num *= -1;
        *len += write(1, "-", 1);
    }
    if (num >= base)
        print_number(num / base, base, len);
    *len += write(1, &hexa[num % base], 1);
}
int ft_printf(const char *str, ...)
{
    int len = 0;
    int i = 0;
    va_list ptr;
    va_start(ptr, str);
    while (str[i])
    {
        if (str[i] == '%' && str[i + 1])
        {
            i++;
            if (str[i] == 's')
                print_string(va_arg(ptr, char *), &len);
            else if (str[i] == 'd')
                print_number((long long)va_arg(ptr, int), 10, &len);
            else if ((str[i]) == 'x')
                print_number((long long)va_arg(ptr, unsigned int), 16, &len);
        }
        else
            len += write(1, &str[i], 1);
        i++;
    }
    va_end(ptr);
    return (len);
}
int main()
{
    ft_printf("Magic %s is %d", "number", 42);
}