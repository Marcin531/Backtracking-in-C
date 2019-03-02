#include "move.h"


#define PRINT

int move( int** pTab, int nRow, int nCol, int nDepth, int move, int x, int y, int* px, int * py, int** pRoot )
{
	
	switch( move )
	{
	case 0: *py -= 1; break;
	case 1: *py += 1; break;
	case 2: *px -= 1; break;
	case 3: *px += 1; break;
	default: printf( "Zly ruch\n" );
	}

	//printf( "\npRoot[%d][%d]: %d", *px,*py,pRoot[*px][*py] );

	if( (*px >= nCol) || (*px<0) || ( *py >= nRow ) || ( *py < 0 ) )
	{
		//printf( "Nie mozna wykonac ruchu" );
			*py = y;
			*px = x;
			return 0;	
	}
	if( ( ( pTab[*py][*px] ) <= ( nDepth ) ) )
	{
		//printf( "Nie mozna wykonac ruchu" );
		*py = y;
		*px = x;
		return 0;
	}
	
	if( ( pRoot[*py][*px] ) )
	{
		*py = y;
		*px = x;
		return 0;
	}
	pRoot[*py][*px] = 1;
	
	return 1;
}

int root( int** pTab, int nRow, int nCol, int nDepth, int x, int y, int** pRoot, int x_dest, int y_dest )
{
	//static int a = 0; // gdy w ktorejs rekurencji statek dotrze do portu ustawiam a jako 1 

#ifdef PRINT
	printf( "(%d,%d)->", x, y );
#endif

	pRoot[y][x] = 1;
	if( pRoot[y_dest][x_dest] ) {  return 1; } //a=1
	else
	{
		int xx = 0; //xx=x;
		int yy = 0; //yy=y;

		for( int i = UP; i <= RIGHT; i++ )
		{
			if( !move( pTab, nRow, nCol, nDepth, i, x, y, &xx, &yy, pRoot ) )
			{
				continue;
			}
			if( root( pTab, nRow, nCol, nDepth, xx, yy, pRoot, x_dest, y_dest ) )
				{
					//x = xx; // musze zmienic parametry, zeby w rekurencji one rowniez wrocily do poprzedniego stanu
					//y = yy;
					return 1; //return a
				}

			
		}
		/*	zdefiniowac nowe wspolrzedne
	sprawdzic wszyskie mozliwosci ruchu
	jesli ruch jest mozliwy w zadanym kierunku - wykorzystac funkcje move
	jesli wykonanie kolejnego kroku sie powiodlo rekurencyjnie root()*/

	pRoot[y][x] = 2;
		return 0;
	}


}

void setTab( char* sFile, int**pTab, int nRow, int nCol )
{
	FILE* fin;
	if( ( fin = fopen( sFile, "r" ) ) == NULL ) //jesli nie znajdzie pliku zwraca NULL
	{
		perror( "ERROR- nie mozna otworzyc pliku" );
	}
	
	int** pT = pTab;
	
	for( int i = 0; i < nRow; i++ )
	{
		int* pColumn = *pT++;	 //za kazdym zwiekszeniem pM ponownie trzeba to zadeklarowac - zmiana wiersza
		for( int j = 0; j < nCol; j++, pColumn++ )
		{
			fscanf( fin, "%ld", pColumn );
		}
	}
	fclose( fin );
}

void PrintTab( int** pTab, int nRow,int nCol )
{
	printf( "\t" );
	for( int i = 0; i < nCol; i++ )
	{
		printf( "%d:\t",i );
	}
	printf( "\n" );
	//double** pRow = pTab; // sluzy do zmiany wiersza, zmienne wprowadzone aby nie modyfikowac pTab
	for( int i = 0; i < nRow; i++ )
	{
		int* pColumn = *pTab++;//sluzy do przesuwania sie po kolumnach w danych wierszu
		printf( "%d:\t", i );
		for( int j = 0; j < nCol; j++, pColumn++ )
		{
			printf( "%ld\t", *pColumn );
		}

		printf( "\n" );
	}
}


int CreateTab( int*** pTab, int nRow,int nCol )
{

	int** p = *pTab = ( int** ) calloc( nRow,sizeof( int* ) ); 	 //alokacja pamieci na wiersze
																	   //**p oznacza numer wiersza- wskaznik umozliwiajacy przesuwanie sie po wierszach
	if( !( *pTab ) )													   //*p oznacza numer kolumny- wskaznik umozliwiajacy przesuwanie sie po kolumnach
	{
		perror( "ERROR-BAD MEMORY ALLOCATION!!!" );
		return 0;
	}

	for( int i = 0; i < nCol; i++, p++ ) // przesuwanie wskaznika p i alokowanie pamieci w wierszu
	{
		*p = ( int* ) calloc(nCol, sizeof( int ) );
		//!!!!	
		if( !( *p ) )
		{
			perror( "ERROR-BAD MEMORY ALLOCATION!!!" );
			return 0;
		}
	}
	return 1;
}

//int root( int** pTab, int nRow, int nCol, int nDepth, int x, int y, int** pRoot, int x_dest, int y_dest )
//{
//	printf( "(%d,%d)->", x, y );
//	pRoot[x][y] = 1;
//	if( pRoot[x_dest][y_dest] ) return 1;
//	else
//	{
//		if( !( ( ( y - 1 ) >= nRow ) || ( ( y - 1 ) < 0 ) || ( pTab[x][y - 1] < ( nDepth + 1 ) ) || ( pRoot[x][y - 1] ) ) )
//		{
//			//printf( "Nie mozna wykonac ruchu/ statek juz byl w tym miejscu" );
//
//			if( move( pTab, nRow, nCol, nDepth, UP, x, y, &x, &y, pRoot ) )root( pTab, nRow, nCol, nDepth, x, y, pRoot, x_dest, y_dest );
//
//		}
//		else if( !( ( ( y + 1 ) >= nRow ) || ( ( y + 1 ) < 0 ) || ( pTab[x][y + 1] < ( nDepth + 1 ) ) || ( pRoot[x][y + 1] ) ) )
//		{
//			//printf( "Nie mozna wykonac ruchu/ statek juz byl w tym miejscu" );
//
//			if( move( pTab, nRow, nCol, nDepth, DOWN, x, y, &x, &y, pRoot ) )root( pTab, nRow, nCol, nDepth, x, y, pRoot, x_dest, y_dest );
//
//		}
//		else if( !( ( ( x + 1 ) >= nCol ) || ( ( x + 1 ) < 0 ) || ( pTab[( x + 1 )][y] < ( nDepth + 1 ) ) || ( pRoot[x + 1][y] ) ) )
//		{
//			//printf( "Nie mozna wykonac ruchu" );
//
//			if( move( pTab, nRow, nCol, nDepth, RIGHT, x, y, &x, &y, pRoot ) )root( pTab, nRow, nCol, nDepth, x, y, pRoot, x_dest, y_dest );
//
//		}
//		else if( !( ( ( x - 1 ) >= nCol ) || ( ( x - 1 ) < 0 ) || ( pTab[( x - 1 )][y] < ( nDepth + 1 ) ) || ( pRoot[x - 1][y] ) ) )
//		{
//			//printf( "Nie mozna wykonac ruchu" );
//
//			if( move( pTab, nRow, nCol, nDepth, LEFT, x, y, &x, &y, pRoot ) ) root( pTab, nRow, nCol, nDepth, x, y, pRoot, x_dest, y_dest );
//
//		}
//
//
//		/*	zdefiniowac nowe wspolrzedne
//	sprawdzic wszyskie mozliwosci ruchu
//	jesli ruch jest mozliwy w zadanym kierunku - wykorzystac funkcje move
//	jesli wykonanie kolejnego kroku sie powiodlo rekurencyjnie root()*/
//		pRoot[x][y] = 0;
//		return 0;
//	}
//
//}

//	
		//if( move( pTab, nRow, nCol, nDepth, UP, x, y, &x, &y, pRoot ) )
		//	root( pTab, nRow, nCol, nDepth, x, y, pRoot, x_dest, y_dest );
		//	
		//else if( move( pTab, nRow, nCol, nDepth, DOWN, x, y, &x, &y, pRoot ) )
		//	root( pTab, nRow, nCol, nDepth, x, y, pRoot, x_dest, y_dest );
		//	
		//else if( move( pTab, nRow, nCol, nDepth, RIGHT, x, y, &x, &y, pRoot ) )
		//	root( pTab, nRow, nCol, nDepth, x, y, pRoot, x_dest, y_dest );
		//		
		//else if(move( pTab, nRow, nCol, nDepth, LEFT, x, y, &x, &y, pRoot )) 
		//	root(pTab,nRow,nCol,nDepth,x,y,pRoot,x_dest,y_dest);
