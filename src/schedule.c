/*
 * schedule.c is part of yadp.
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
 * @file schedule.c 
 *
 * definition file for schedule.h
 *
 * @author theNerd247
 * @copyright GNU Public License 2
 */

#include "schedule.h"
#include "parser.h"
#include "time.h"

Task* normtask(date_t sp, date_t ep, Task* task)
{
	timer tmr;
	struct tm tme;
	//sanity checks
	check(task,"Invalid Task struct");

	//check for recurring time
	if(task.recur)
	{
		//normalize recur time
		time(&tmr);
		tme = *(localtime(&tmr));
		if(tme.tm_mday > task.recur)
	}

	//check the start and end time against print period
	check_error((sp <= task.startm.date && task.endtm.date <= ep));


	//calculate the start end time
	error:
		return NULL;
}
