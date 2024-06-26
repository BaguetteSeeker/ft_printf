#include "ft_printf.h"

int	main(void)
{
	char	*teststring = "%%%d"; // %% int
	//char	*teststring = "Testring address is: %p";
	//char	*teststring = "%s";
	//printf("Abcdef123586");
	ft_printf(teststring, 999);
	printf("\n TRUE PRINTF OUTPUTS : %%%d", 999);
	return (0);
}