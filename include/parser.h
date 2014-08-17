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

typedef struct task_t
{
	char* description; /**< description of what the task is about. */
	int strttm;
	int endtm;
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
 * @param str - a string to parse
 *
 * @return int - the given task object with info stored; NULL if error occured
 * 
 */
Task* task_parse(Task* task, char* str);
