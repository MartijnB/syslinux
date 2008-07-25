#include <stdio.h>
#include <stdlib.h>
#include <console.h>

#include "elf_module.h"

#define KLIBC_NAME			"klibc.dyn"

#define ELF_DIRECTORY		"/dyn/"

static struct elf_module	*mod_klibc;

int modules_com32_setup() {
	int res;

	res = modules_init();

	if (res != 0)
		return res;

	////////////////////////////////////////
	// Load the klibc module

	// Create its associated structure
	mod_klibc = module_alloc(ELF_DIRECTORY KLIBC_NAME);

	if (mod_klibc == NULL) {
		return -1;
	}

	res = module_load(mod_klibc);

	if (res != 0) {
		return res;
	}

	return 0;
}

void modules_com32_finalize() {
	modules_term();
}

int main(int argc, char **argv) {
	int res;

	// Open a standard r/w console
	openconsole(&dev_stdcon_r, &dev_stdcon_w);

	// Initializing the module subsystem
	res = modules_com32_setup();

	if (res != 0) {
		printf("ERROR: Could not fully initialize the module!\n");
		return res;
	}

	modules_com32_finalize();

	return 0;
}
