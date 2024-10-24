#include <stdio.h>
#include <string.h>

#include "lib/error.h"
#include "7_tasks.h"

typedef error_t (*opt_handler_t)(int argc, char** argv);

typedef struct opt {
	char name[16];
	char args[64];
	char desc[256];
	opt_handler_t handler;
} opt_t;

error_t parse_opt(const char* flag, opt_t opts[], int nOpts, opt_t* outOpt) {
	if (flag[0] != '-' && flag[0] != '/') {
		return ERROR_INVALID_PARAMETER;
	}

	++flag;

	for (int i = 0; i != nOpts; ++i) {
		if (strncmp(opts[i].name, flag, 16) == 0) {
			*outOpt = opts[i];
			return ERROR_SUCCESS;
		}
	}

	return ERROR_INVALID_PARAMETER;
}

void print_opts(opt_t opts[], int nOpts) {
	for (int i = 0; i != nOpts; ++i) {
		opt_t opt = opts[i];
		fprintf(stdout, "  /%s, -%s %s: %s\n", opt.name, opt.name, opt.args, opt.desc);
	}
}

int main(int argc, char** argv) {
	error_t error;

	opt_t opts[] = {{"r", "<file 1> <file 2> <output file>", "merges lexemes from file 1 and file 2", &merge_lexemes},
	                {"a", "<input> <output>", "does various things to lexemes in the input file", &process_lexemes}};
	int nOpts = sizeof(opts) / sizeof(opt_t);

	if (argc == 1) {
		printf("Usage: %s <flag> <...>\nFlags:\n", argv[0]);
		print_opts(opts, nOpts);
		return -ERROR_INVALID_PARAMETER;
	}

	opt_t opt;
	error = parse_opt(argv[1], opts, nOpts, &opt);
	if (error != ERROR_SUCCESS) {
		fprintf(stderr, "Invalid option. See usage for more details.\n");
		return -ERROR_INVALID_PARAMETER;
	}

	error = opt.handler(argc, argv);
	if (error != ERROR_SUCCESS) {
		error_print(error);
		return -(int)error;
	}
}
