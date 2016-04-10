#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include "logger.h"
#include "shared_func.h"
#include "sched_thread.h"
#include "ini_file_reader.h"
#include "sockopt.h"
#include "id_generator.h"

int main(int argc, char *argv[])
{
	struct idg_context context;
	int result;
	int i;
	int64_t id;
	const int machine_id = 0;
	const int mid_bits = 8;
	
	log_init();
	//g_log_context.log_level = LOG_DEBUG;

	result = id_generator_init_ex(&context, "/tmp/sn.txt",
		machine_id, mid_bits);
	if (result != 0)
	{
		return result;
	}

	//id_generator_next(&context, &id);
	//printf("id: %"PRId64", %016llX\n", id, id);
	for (i=0; i<100000; i++)
	{
		result = id_generator_next(&context, &id);
		if (result != 0)
		{
			break;
		}
		printf("%"PRId64", %016llX\n", id, id);
	}

	id_generator_destroy(&context);
	return 0;
}

