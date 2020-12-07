#include "nslookup.h"

int main(int argc, char* argv[])
{
	atexit(common_exit_handler);

	char domain_name[256];
	memset(domain_name, 0, sizeof domain_name);

	if (argc >= 2) {
		strcpy(domain_name, argv[1]);
	}
	else {
		printf("Enter domain name: ");
		scanf("%s", domain_name);
	}

	common_init_handler();

	hostent* he = gethostbyname(domain_name);
	if (he == NULL) {
		printf("%s\n", "Error DNS record retrieve");
		return -1;
	}

	for (char** pa = he->h_addr_list; *pa != NULL; ++pa) {
		handle_he_ip(*pa, he->h_length);
	}

	return 0;
}