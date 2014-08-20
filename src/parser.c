/*
 * parse.c is part of yadp.
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
 * @file parse.c 
 *
 * parser for todo file
 *
 * @author theNerd247 (noah.harvey247@gmail.com)
 * @copyright GNU Public License 2
 */

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h> //for parsedate
#include <regex.h> //for parsing task

#include <str.h>

#include "parser.h"
#include "dbg.h"

///helper function for task_parse
/** 
 * @brief fetches the start time 
 * 
 * @param str - string to parse
 *
 * @return int - start time found (or 0 if no valid time found)
 *
 */
int getstarttm(char* str)
{
	char* strt = NULL;

	//sanity check
	if(!(strt = strstr(str,"START:"))) return 0;

	//offset the strt pointer to point at start of numerical time string
	strt += 6;

	return atoi(strt);
}

///helper function for task_parse
/** 
 * @brief fetches the end time 
 * 
 * @param strt - the start time to reference from
 * @param str - string to parse
 *
 * @return int - end time found (or 0 if no valid time found)
 *
 */
int getendtm(char* str, int strt)
{
	size_t tm = 0;
	char* end = NULL;

	//sanity check
	if(!(end = strstr(str,"END:"))) return 0;

	//offset the strt pointer to point at start of numerical time string
	end += 4;

	tm = atoi(end);

	//shift the end time based on the start reference time
	if(tm <= strt)
		tm += 1200;

	return tm;
}

//imported from 
Task* gettms(Task* task)
{
	//define variables
	char* str = task->description;

	//sanity checks
	if(!task || !str) goto error;	
	if(*str == '\0') goto error;

	//grab the start and end times
	task->strttm = getstarttm(str);
	task->endtm = getendtm(str,task->strttm);

	return task;

	error:
    return NULL;
}
