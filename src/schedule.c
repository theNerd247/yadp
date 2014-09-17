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

#include <math.h>

#include "table.h"
#include "schedule.h"

#include "time.h"
#include "dbg.h"

table_t* formattask(int* dim, Task* task)
{
	table_t* out;
	double difftm;
	unsigned int ys,xs;
	size_t i,j;
	size_t cnt,cntmax;

	//sanity checks
	check_mem(task);
	check_mem(dim);

	//init output table
	difftm = difftime(task->endtm,task->starttm);
	ys = ceil((difftm/60)/dim[1]); //number of lines / (min/line)
	xs = difftm/86400;
	xs = (xs >= 1) ? ceil(xs*dim[0]) : dim[0]; //number of days it will cover * (cells/day)

	out = inittbl(' ',xs,ys);
	check_mem(out);

	//create top and bottom borders
	for (i = 0; i < xs; i++)
	{
		setcell(out,'-',i,0);
		setcell(out,'-',i,ys-1);
	}

	//insert task in table 
	cnt = 0;
	cntmax = strlen(task->description);

	for (i = 1; i < ys-1; i++)
	{
		for (j = 1; (j < xs-1); j++)
		{
			if(cnt < cntmax)
				setcell(out,task->description[cnt++],j,i);
			else
				goto elipse;
		}
	}

	//insert elipse if the task description was to long
	elipse:
	if (xs > 4 && cnt < cntmax)
	{
		setcell(out,' ',xs-5,ys-2);
		setcell(out,'.',xs-4,ys-2);
		setcell(out,'.',xs-3,ys-2);
		setcell(out,'.',xs-2,ys-2);
	}

	return out;
	error:
		return NULL;
}
