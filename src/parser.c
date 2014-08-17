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
#include <math.h> //for parsedate
#include <regex.h> //for parsing task

// TODO: Make this make more sense and move it to another file
//converts from form "YYYY-MM-DD" to DDMMYYYY as an int 
date* parsedate(char* expr)
{
	//pull out the characters in form DDMMYYYY form
    
    /* OLD CODE
	char tmpform[9];
	strsub(expr,8,9,tmpform);
	strsub(expr,5,6,tmpform+2);
	strsub(expr,0,3,tmpform+4);
	tmpform[8] = '\0';
	//the "-48" is to convert from ascii to int
	return atoi(tmpform);
    */
    int year = 0;
    int month = 0;
    int day = 0;
    sscanf(expr, "%d-%d-%d", &year, &month, &day);
    date* d = date_new(year, month, day);
    return d;
}

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
	uint8_t i; 

	//sanity check
	if(!(strt = strpbrk(str,"START:"))) return 0;

	//offset the strt pointer to point at start of numerical time string
	strt += 6;

	//check if all characters are digits (and so time stamp exists)
	for (i = 0; i < 4; i++)
		if(!isdigit(*(strt+i)) return 0;

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
	uint16_t tm = 0;
	char* end = NULL;
	uint8_t i; 

	//sanity check
	if(!(end = strpbrk(str,"START:"))) return 0;

	//offset the strt pointer to point at start of numerical time string
	end += 6;

	//check if all characters are digits (and so time stamp exists)
	for (i = 0; i < 4; i++)
		if(!isdigit(*(end+i)) return 0;

	tm = atoi(end);

	//shift the end time based on the start reference time
	if(tm <= strt)
		tm += 1200;
}

int task_parse(Task* task, char* str)
{
	//sanity checks
	if(!task || !str) return 1;	
	if(*str == '\0') return 1;

	//define variables
	size_t nmatches; //number of regex substrings
	regex_t regexpr; //struct to hold compiled regex (man regex.h for more info)
	char buff[11]; //a large buffer to use with str.sub
	size_t descstrt = 0; //holds the index of the start of the description, default: 0(beginning of str)
	int i;

	//regex string for parsing 
	//       complete?>|priority?---->|date?----------------------------->|desc----->|
	char* regx = "^(x )?(\\([A-Z]\\) )?([0-9]{4,4}-[0-9]{2,2}-[0-9]{2,2} )?([^\n]*)$";

	//compile the regex struct
	int compstat = regcomp(&regexpr,regx,REG_EXTENDED);
  check(compstat == 0, "Regex could not compile: status is %d", compstat);
	nmatches = regexpr.re_nsub;

	//create container to hold regex matches
	regmatch_t* matches = calloc(nmatches, sizeof(regmatch_t));

	//execute the regex tree
	check(regexec(&regexpr,str,nmatches,matches,0) != REG_NOMATCH, "Regex did not match this string.");

	//find the beginning of the description
	for (i = 1; i < nmatches; i++)
	{
		//for each valid index grab substring using the index given by matches[]
		int strt = matches[i].rm_so;
		int end  = matches[i].rm_eo;
		if(strt == -1 || end == -1) continue;
	
		//depending on i set the values of the task
		descstrt = end;	
	}
    
 	free(matches);

	//extract the desccription
	char* desc = malloc(sizeof(char)*(strlen(str)-descstrt+1));
	strsub(str,descstrt,strlen(str)-1,desc);

	if (task->description) free(task->description); //get rid of the old description if it exists
	task->description = desc;


	//grab the start and end times
	task->strttm = getstarttm(desc);
	task->endtm = getendtm(desc,starttm);

	return 0;

	error:
    free(matches);
    return -1;
}

