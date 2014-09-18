/*
 * schedule.h is part of yadp.
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
 * @file schedule.h 
 *
 * Calculation functions and graphics generation functions
 *
 * @author theNerd247
 * @copyright GNU Public License 2
 */

#ifndef __schedule
#define __schedule

#define __table_headerinc__
#include "table.h"

#include "parser.h"

#define MAX_CHAR 1024

/**
 * @brief gets the output formatting of the task based on the task times
 * 
 * Sets the task's x,y coordinates on the print output and its width and height.
 * It also creates the line array of the task's description that is used for
 * printing.
 *
 * @param dim - the max dimensions of a task (@see pweek())
 * @param task - the task to format
 *
 * @return char* - task with formatted text or NULL if error occurs. Note this
 * string should be freed after copied into a buffer.
 * 
 */
table_t* formattask(int* dim, Task* task);

/**
 * @brief creates the day planner from the given todo file
 * 
 * Creates the day planner between the start and end dates. 
 * file must be a todo.txt formatted file. Below is the formatt of each line:
 *
 * `regular task info here RECUR: Fri START: mm/dd/yy END: mm/dd/yy`
 *
 * Where `RECUR:` is the a day in the week that the task should happen on
 * `START: ` and `END: ` are the start and end dates for a given event. 
 * If RECUR is used with START and END then the task will be seen as occuring
 * only between START and END times.
 *
 * **NOTE:** call configplanner() before using this function
 *
 * @param file - the todo file to parse the data from.
 * @param start - the start of the print date
 * @param end - end of the print date
 *
 * @return char* - string representation of the day planner; NULL if an error occurs
 * 
 */
char* getdayplanner(FILE* file, time_t start, time_t end);
#endif 
