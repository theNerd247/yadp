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

#include "parser.h"

/**
 * @brief normalizes the times for a newly parsed task
 * 
 * Takes the recurring time (if any), the start and end time and calculates the
 * next time the task occures. If the task doesn't fall within the printing
 * period then it is freed from memory and NULL is returned. If no hour:minute
 * time exists then the task is kept only if it falls within the print period.
 * It will be printed as a todo item
 *
 * @param task - the given task to calculate
 *
 * @return Task* - given task with normalized times or NULL if error occurs.
 * 
 */
Task* normtask(Task* task);
