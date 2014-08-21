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

#define PATTERN "(([0-9][0-9])/([0-9][0-9])/([0-9][0-9]))? ?(([0-9][0-9]):([0-9][0-9]))?[.]*"

///helper function for task_parse
int gettm(char* str, const char* ind, regex_t* regt)
{
	size_t nmatches;
	regmatch_t* matches;
 	size_t i;
	char* temp;

	//find the offset of the given indicator
	if(!(str = strstr(str,ind))) return -1;
	str += strlen(ind);

	//set up matching variables for regex
	nmatches = regt->re_nsub;
	matches = calloc(sizeof(regmatch_t), nmatches);

	//run regex
	if(regexec(regt,str,nmatches,matches,REG_NOTBOL & REG_NOTEOL) == REG_NOMATCH)
		return -1;

	//grab the start and end times
 	for (i = 1; i < nmatches; i++)
 	{
		if(matches[i].rm_so == -1) 
			continue;

		strncpy(temp,str,matches[i].rm_eo-matches[i].rm_so+1);

		printf("%i: %s\n",i,temp);

/*
 * 		switch(i)
 * 		{
 * 			case 1: 
 * 				
 * 				break;
 * 			case 2: 
 * 				
 * 				break;
 * 		}
 * 		 */
 	}

	return 0;
}

//imported from 
Task* gettms(Task* task)
{
	//define variables
	char* str = task->description;
	regex_t regt;

	//sanity checks
	if(!task || !str) goto error;	
	if(*str == 0) goto error;

	//regex setup
	check(regcomp(&regt,PATTERN,REG_EXTENDED) == 0, "Failed to compile regex");

	int a = gettm(str,"START:",&regt);	

	return task;

	error:
    return NULL;
}
