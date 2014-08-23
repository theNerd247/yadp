/*
 * parser.c is part of yadp.
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
 * @file parser.h 
 *
 * parser declarations
 *
 * @author theNerd247 
 * @copyright GNU Public License 2
 */

#include <stdio.h>

typedef union
{
	unsigned long int date:40;
	struct
	{
		unsigned char year:8;
		unsigned char month:8;
		unsigned char day:8;
		unsigned char hour:8;
		unsigned int min:8;
	};
} date_t;

typedef struct task_t
{
	char* description; /**< description of what the task is about. */
	date_t starttm;
	date_t endtm;
}Task;

/**
 * @brief fetches the tasklist from an assumed todo.txt file
 * 
 *
 * @param file - file must be in the format of a todo.txt file (see the interwebs for details)
 *
 * @return Task* - array of Tasks; NULL if error occured
 * 
 */
Task* gettasklist(FILE* file);

/**
 * @brief parses the given string for task info
 * 
 * Parse the given string for task information and store it in the given task
 *
 * @param task - the given Task to store the found info in.
 *
 * @return int - the given task object with info stored; NULL if error occured
 * 
 * @todo add date extraction (yyyy-mm-dd)
 */
Task* gettms(Task* task);
