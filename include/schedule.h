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

#include "table.h"

#include "parser.h"

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

#endif 
