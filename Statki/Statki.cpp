
//Celem dzialania programu jest wykorzystanie backtrackingu do znalezienia drogi pomiedzy wprowadzonymi punktami 
//The purpose of this program is to use backtracking to find the way between given points

#include "move.h"

#define DEPTH_MIN 10
#define DEBUG_MAIN
#define ROW 10
#define COLUMN 10

int main(int argc, char* argv[])
{
	if( argc != 2 )
	{
		perror( "Podaj prawidlowa liczb argumentow" );
	}
	
	int nRow = ROW;
	int nCol=COLUMN;

#ifdef DEBUG_MAIN
	printf( "Wymiar tablicy: %d x %d\n", nRow, nCol );
#endif
	
	int** pTab = NULL; 
	
	if( !CreateTab( &pTab, nRow, nCol ) )
	{
		perror( "Nie udalo sie utworzyc tablicy" );
	}

	setTab( argv[1], pTab, nRow, nCol );

#ifdef DEBUG_MAIN
	printf( "Tablica glebokosci: \n");
	PrintTab( pTab, nRow, nCol );
#endif


	int** pRoot = NULL;

	if( !CreateTab( &pRoot, nRow, nCol ) )
	{
		perror( "Nie udalo sie utworzyc tablicy" );
	}

	int x_dest = 6, y_dest = 7;
	if( root( pTab, nRow, nCol, DEPTH_MIN, 0, 0, pRoot, x_dest, y_dest ) )
		printf( "(%d,%d) Udalo sie dotrzec do portu!",x_dest,y_dest);
	else
		printf( "Nie mozna dotrzec do portu" );
	


	
}
