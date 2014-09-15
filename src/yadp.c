/*
 * yadp.c is part of yadp.
 * 
 * yadp is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * yadp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with yadp.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file yadp.c 
 *
 * yadp main file
 *
 * @author theNerd247 (noah.harvey247@gmail.com)
 * @copyright GNU Public License 2
 *
 */

/*#define UNITTST*/

#include <stdlib.h>
#include <time.h>

#include "parser.h"
#include "sput.h"
#include "schedule.h"

#define pdate(tm) printf("date(%u): %u/%u/%u/ %u:%u\n",tm.date,tm.month,tm.day,tm.year,tm.hour,tm.min);

extern Task* getrecurtm(char*,Task*);
static void test_getrecur()
{
	Task task;
	task.description = "(A) do hw RECUR: Fri";
	sput_fail_if(getrecurtm(" Fri",&task) == NULL, "RECUR succeed test");

	task.description = "(A) do hw RECUR: ";
	sput_fail_unless(gettms(&task) == NULL, "RECUR fail test");

	task.description = "(A) do hw RECUR: Fri START: 08/22/14 08:00 END: 08-22-14 09:22";
	sput_fail_if(gettms(&task) == NULL, "RECUR succeed test with start/end");

	task.description = "(A) do hw RECUR: START: 08/22/14 08:00 END: 08-22-14 09:22";
	sput_fail_unless(gettms(&task) == NULL, "RECUR fail test with start/end");
}

static void test_gettm_success()
{
	Task task;
	task.description = "(A) do hw START: 08/22/14 08:00 END: 08-22-14 09:22";
	sput_fail_if(gettms(&task) == NULL, "gettm(): start/end succeed test");
}

static void test_gettm_fail()
{
	Task task;
	task.description = "(A) do hw START: bob";
	sput_fail_unless(gettms(&task) == NULL, "gettm(): start fail test");
 
	task.description = "(A) do hw END: bob";
	sput_fail_unless(gettms(&task) == NULL, "gettm(): end fail test");

	task.description = "(A) do hw START: bob END: larry";
	sput_fail_unless(gettms(&task) == NULL, "gettm(): end fail test");
}

static void test_getformat_success()
{
	Task task;
	task.description = "(A) do hw START: 09/15/14 10:00 END: 09/15/14 12:00";
	int dim[4] = {15,30,100,100};
	size_t i;

	gettms(&task);
	table_t* tbl = formattask(dim,&task);

	printf("starttm: %s\n", ctime(&task.starttm));
	printf("endtm: %s\n", ctime(&task.endtm));

	printf("tblsize: %i,%i\n", tbl->xsize,tbl->ysize);
	for (i = 0; i < tbl->ysize; i++)
	{
		printf("%s\n", tbl->cells[i]);
	}
}

int main(int argc, char const *argv[])
{
	//run unit tests
	#ifdef UNITTST

	sput_start_testing();
	sput_enter_suite("getrecurtm(): RECUR parsing");
	sput_run_test(test_getrecur);

	sput_enter_suite("gettm() parsing");
	sput_run_test(test_gettm_success);
	sput_run_test(test_gettm_fail);

	sput_finish_testing();
	#endif

	test_getformat_success();

 	return EXIT_SUCCESS;
}
