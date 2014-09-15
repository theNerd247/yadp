#include "table.h"

table_t* setcell(table_t* tbl, TBLTYPE val, unsigned int x, unsigned int y)
{
	if(tbl == NULL) 
		return NULL;
	else if(x >= tbl->xsize || y >= tbl->ysize || x < 0 || y < 0)
		return NULL; 

	tbl->cells[y][x] = val;
	return tbl;
}

table_t* inittbl(TBLTYPE val, unsigned int x, unsigned int y)
{
	size_t i,j;
	table_t* newtbl = (table_t*)malloc(sizeof(table_t));

	if (newtbl == NULL) 
		goto error;

	//create row containers
	newtbl->cells = (TBLTYPE**)calloc(y,sizeof(TBLTYPE*));

	if(newtbl->cells == NULL)
		goto error;

	newtbl->xsize = x;
	newtbl->ysize = y;

	//create row cols
	for (i = 0; i < y; i++)
		newtbl->cells[i] = (TBLTYPE*)calloc(x,sizeof(TBLTYPE));

	//init table values
	for (i = 0; i < y; i++)
		for (j = 0; j < x; j++)
			setcell(newtbl,val,j,i);

	return newtbl;

	error:
		return NULL;
}

TBLTYPE getcell(table_t* tbl, unsigned int x, unsigned int y)
{
	if(tbl == NULL)
		return 0;
	else if(x >= tbl->xsize || y >= tbl->ysize || x < 0 || y < 0) 
		return 0; 

	return tbl->cells[y][x];
}

