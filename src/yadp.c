/*
 * yadp.c is part of yadp.
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
 * @file yadp.c 
 *
 * yadp main file
 *
 * @author theNerd247 (noah.harvey247@gmail.com)
 * @copyright GNU Public License 2
 *
 */

#include <stdlib.h>

#include "parser.h"

#define pdate(tm) printf("date(%u): %u/%u/%u/ %u:%u\n",tm.date,tm.month,tm.day,tm.year,tm.hour,tm.min);

int main(int argc, char const *argv[])
{
  //parse args
  Task t,d;
	t.description = "(A) math hw START:08/22/14 08:15 END:08/22/14 03:30";
	d.description = "(A) sci hw START:08:15 END:03:30";

	gettms(&t);
	gettms(&d);

	pdate(t.starttm);
	pdate(t.endtm);

	pdate(d.starttm);
	pdate(d.endtm);
  //parse tasks from given todo file
  //generate day planner
  //save day planner
	return EXIT_SUCCESS;
}
