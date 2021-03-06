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
#include <stdio.h>
#include <string.h>
#include <math.h> //for parsedate
#include <regex.h> //for parsing task
#include <time.h>

#include <str.h>

#include "parser.h"
#include "dbg.h"

#ifndef NDEBUG
//TODO: update pdate to print struct tm values
#define pdate(tm) 
#endif

#define PATTERN "(([0-9][0-9])[/|-]([0-9][0-9])[/|-]([0-9][0-9])) ?(([0-9][0-9]):([0-9][0-9]))[.]*"
const char* weeks[7] = {"Sun","Mon","Tue","Wed","Thur","Fri","Sat"};

///helper function for task_parse
struct tm gettm(char* str)
{
	 size_t i;
	size_t nmatches;
	regex_t regt;
	regmatch_t* matches = NULL;
	char* temp = NULL;
	struct tm date;
	time_t tmp;

	check(str,"Invalid time string: %s",str);

	time(&tmp);
	date = *(localtime(&tmp));

	temp = (char*)malloc(sizeof(char)*strlen(str));
	check_mem(temp);

	//regex setup
	check(regcomp(&regt,PATTERN,REG_EXTENDED) == 0, "Failed to compile regex string: %s",PATTERN);

	//set up variables for regex matching
	nmatches = regt.re_nsub+1;
	matches = calloc(sizeof(regmatch_t), nmatches);

	//run regex for start
	check(regexec(&regt,str,nmatches,matches,REG_NOTBOL & REG_NOTEOL) == 0, "Invalid START/END time: %s",str);

	//grab the start and end times
	int b;//temp variable for string to time conversion
 	for (i = 2; i < nmatches; i++)
 	{
		//skip whole matches
		if(i == 5)
			continue;

		if(matches[i].rm_so == -1) 
			continue;

		strncpy(temp,str+matches[i].rm_so,matches[i].rm_eo-matches[i].rm_so);

		temp[matches[i].rm_eo-matches[i].rm_so] = '\0';

		b = atoi(temp) & 0xff;
		switch(i)
		{
			case 2: 
				date.tm_mon = b-1;
				break;
			case 3: 
				date.tm_mday = b;
				break;
			case 4: 
				date.tm_year = (b+2000)-1900;
				break;
			case 6: 
				date.tm_hour = b;
				break;
			case 7: 
				date.tm_min = b;
				break;
		}
 	}
	
	//remove the matches string from the token

	error:
		regfree(&regt);
		free(matches);
		free(temp);

	return date;
}

///helper function for gettms
/** 
 * @brief parses for recurring times
 *
 * Parses the "... RECUR: ..." part of the task for a recurring time and
 * computes the date at which it will occur next (or today). 
 *
 * @param str - the string to parse
 * @param time - the structure to store the parsed time in
 * 
 * @return Task* - given Task* with stored recurring weekday, or NULL if error occurs
 */
Task* getrecurtm(char* str, Task* time)
{
	size_t i;
	//remove beginning white space
	while(*str == ' ' || *str == '\t')
		str++;

	//compare characters to get weekday
	for (i = 0; i < 7; i++)
	{
		if(!strncmp(str,weeks[i],3))
		{
			time->recur = i;
			debug("Recurring Time found: %s",weeks[i]);
			return time;
		}
	}

	return NULL;
}

//imported from 
Task* gettms(Task* task)
{
	//define variables
	char* startstr;
	char* endstr;
	char* temp;
	size_t n;
	struct tm starttm, endtm;

	//sanity checks
	if(!task) goto error;	

	//init recur time
	task->recur = 7;

	n = strlen(task->description);
	temp = (char*)malloc(sizeof(char)*n);
	check_mem(temp);
	strncpy(temp,task->description,n);

	//get reoccurence time if needed
	if((startstr = strstr(temp,"RECUR:")))
	{
		startstr += 6;
		check(getrecurtm(startstr,task),"Invalid Recurring Day");
	}

	//offset the string to the start date
	check((startstr = strstr(temp,"START:")),"No START time found"); 
	startstr += 6;

	//break the string at the end date
	check((endstr = strstr(temp,"END:")),"No END time found");
	endstr += 4;

	//insert '\0' at ':' in 'END:' to make sure the parser works correctly
	*(startstr+(endstr-startstr-1)) = '\0';

	//parse the START: and END: strings for dates and times
	starttm = gettm(startstr);
	endtm = gettm(endstr);

	//shift the end time to military time 
	//TODO: add parsing of "am" and "pm" values
	if(endtm.tm_hour < starttm.tm_hour)
		endtm.tm_hour += 12;

	//convert 24 (midnight) hour to 0	as is proper for struct tm format	
	if(starttm.tm_hour == 24)
		starttm.tm_hour = 0;

	//replace the ':' so the description is saved
	*(startstr-6) = '\0';

	task->description = temp;
	task->starttm = mktime(&starttm);
	task->endtm = mktime(&endtm);

	//throw an error if both start and end times are 0
	//check_error((starttm.date == endtm.date) == 0);

	#ifndef NDEBUG
	pdate(task->starttm); 
	pdate(task->endtm); 
	#endif

	return task;

	error:
    return NULL;
}
