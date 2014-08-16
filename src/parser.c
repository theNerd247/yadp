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

#include <stdio.h>

int task_parse(Task* task, char* str)
{
	//sanity checks
	if(!task || !str) return -1;	
	if(strcmp(str,"") == 0) return -1;

	//define variables
	size_t nmatches; ///<number of regex substrings
	regex_t regexpr; // struct to hold compiled regex (man regex.h)
	char buff[11]; // a large buffer to use with str.sub
	size_t descstrt = 0; //holds the index of the start of the description, default: beginning of 0
	
	//regex string for parsing 
	//       complete?>|priority?_--->|date?-------______---------------->|desc----->|
	char* regx = "^(x )?(\\([A-Z]\\) )?([0-9]{4,4}-[0-9]{2,2}-[0-9]{2,2} )?([^\n]*)$";

	//compile the regex struct
	int compstat = regcomp(&regexpr,regx,REG_EXTENDED);
    check(compstat == 0, "Regex could not compile: status is %d", compstat);
	nmatches = regexpr.re_nsub;

	regmatch_t *matches = calloc(sizeof(regmatch_t), nmatches);

	//execute the regex tree
	check(regexec(&regexpr,str,nmatches,matches,0) != REG_NOMATCH, "Regex did not match this string.");

	//grab the data matched and store it in the Task
	int i;
	for (i = 1; i < nmatches; i++)
	{
		//for each valid index grab substring using the index given by matches[]
		/* map i =
 		 * 1 - complete?
 		 * 2 - priority?
 		 * 3 - date? 
 		 */
		int strt = matches[i].rm_so;
		int end  = matches[i].rm_eo;
		if(strt == -1 || end == -1) continue;
	
		//depending on i set the values of the task
		descstrt = end;	
		switch(i)
		{
			case 1: 
				task->complete = true;
				break;
			case 2: 
				task->priority = *(str+strt+1);
				break;
			case 3: 
				task->datestamp = parsedate(strsub(str,strt,end,buff));
				break;
		}
	}
    
    free(matches);

    //get the description which starts from the last valid end index
	char* desc = malloc(sizeof(char)*(strlen(str)-descstrt+1));
	strsub(str,descstrt,strlen(str)-1,desc);

	if (task->description) free(task->description); //get rid of the old description if it exists
	task->description = desc;

	return 0;

error:
    free(matches);
    return -1;
}

