// SHAPES - an OOP program to handle properties of shapes
//          as in Wilf's Programmers' Workshop (issue 115)

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <dos.h>
#include <ctype.h>
#include <math.h>

//////////////////////////////////////////////////////////////////////////////
int lastitem;

class shape{
	int Exists;
	int Xlocation;
	int Ylocation;
	int Colour;
	float Size;
	int NumberOfPoints;

// the following characteristics are "hidden":

//	float Area;
//	float Lateral;
//	float Perimeter;
//	int AngleAtPoint;	// output only

	shape(void);	//constructor

public:
	int GetExistence(void);
	void SetExistence(int);

	void ShowColour(void);
	void ShowShape(void);
	void ShowLocation(void);

	int GetXlocation(void);
	void PutXlocation(int);
	int GetYlocation(void);
	void PutYlocation(int);
	int GetColour(void);
	void PutColour(int);
	float GetSize(void);
	void PutSize(int);
	int GetNumberOfPoints(void);
	void PutNumberOfPoints(int);
	float GetArea(void);
	void PutArea(int);
	float GetLateral(void);
	void PutLateral(int);
	float GetPerimeter(void);
	void PutPerimeter(int);
	int GetAngleAtPoint(void);
};

shape::shape(void)		// constructor
{
	Exists = 0;
	PutXlocation( 1 + random(9) );
	PutYlocation( 1 + random(9) );
	PutColour ( 1 + random(4) );
	PutSize ( 1 + random(9) );
	NumberOfPoints = 3 + random(3);
}
int shape::GetExistence(void)
{
	return( Exists );
}
void shape::SetExistence(int Setting)
{
	Exists = Setting;
}
void shape::ShowColour(void)
{
	switch( Colour )
	{
	case 1:
		printf("red ");
		break;
	case 2:
		printf("green ");
		break;
	case 3:
		printf("blue ");
		break;
	case 4:
		printf("yellow ");
		break;
	}
}
void shape::ShowShape(void)
{
	switch( NumberOfPoints )
	{
	case 3:
		printf("triangle.\n");
		break;
	case 4:
		printf("square.\n");
		break;
	case 5:
		printf("pentagon.\n");
		break;
	case 6:
		printf("hexagon.\n");
		break;
	}
}
void shape::ShowLocation(void)
{
	printf("\nLocation: (%d,%d)\n",Xlocation,Ylocation);
}
int shape::GetXlocation(void)
{
	return( Xlocation );
}
void shape::PutXlocation(int newXlocation)
{
	Xlocation = newXlocation;
}
int shape::GetYlocation(void)
{
	return( Ylocation );
}
void shape::PutYlocation(int newYlocation)
{
	Ylocation = newYlocation;
}
int shape::GetColour(void)
{
	return( Colour );
}
void shape::PutColour(int newcolour)
{
	Colour = newcolour;
}
float shape::GetSize(void)
{
	return( Size );
}
void shape::PutSize(int newsize)
{
	Size = newsize;
}
int shape::GetNumberOfPoints(void)
{
	return( NumberOfPoints );
}
void shape::PutNumberOfPoints(int newnumberofpoints)
{
	NumberOfPoints = newnumberofpoints;
}
float shape::GetArea(void)
{
 float Area;
	switch( NumberOfPoints )
	{
	case 3:
		Area = Size * Size * 0.324759;
		break;
	case 4:
		Area = Size * Size * 0.5;
		break;
	case 5:
		Area = Size * Size * 0.59441;
		break;
	case 6:
		Area = Size * Size * 0.649519;
		break;
	}
	return(Area);
}
void shape::PutArea(int Area)
{
	switch( NumberOfPoints )
	{
	case 3:
               	Size = sqrt( Area / 0.324759 );	
		break;
	case 4:
		Size = sqrt( Area / 0.5 );
		break;
	case 5:
		Size = sqrt( Area / 0.59441 );
		break;
	case 6:
		Size = sqrt( Area / 0.649519 );
		break;
	}
}
float shape::GetLateral(void)
{
 float Lateral;
	switch( NumberOfPoints )
	{
	case 3:
		Lateral = Size * 0.866025;
		break;
	case 4:
		Lateral = Size * 0.707107;
		break;
	case 5:
		Lateral = Size * 0.587785;
		break;
	case 6:
		Lateral = Size * 0.5;
		break;
	}
	return(Lateral);
}
void shape::PutLateral(int Lateral)
{
	switch( NumberOfPoints )
	{
	case 3:
		PutSize( Lateral * 1.1547 );
		break;
	case 4:
		PutSize( Lateral * 1.414213 );
		break;
	case 5:
		PutSize( Lateral * 1.701302 );
		break;
	case 6:
		PutSize( Lateral * 2 );
		break;
	}
}
float shape::GetPerimeter(void)
{
	return( NumberOfPoints * GetLateral() );
}
void shape::PutPerimeter(int Perimeter)
{
	PutLateral( Perimeter / NumberOfPoints );
}
int shape::GetAngleAtPoint(void)
{
int temp;
	temp = GetNumberOfPoints();
	return( (temp - 2) * 180 / temp );
}
//////////////////////////////////////////////////////////////////////////////
#define BEEP sound(300); delay(500); nosound();

////////////////////////////////////
void pause(void)
{
	printf("\n\nPress a key to continue ...\n" );
	while( kbhit() == 0 )
		;
	(void)getch();
}

////////////////////////////////////
void showmenu(void)
{
	clrscr();
	printf("Press...\n");
	printf("P ... Properties\n");
	printf("B ... Build\n");
	printf("D ... Destroy\n");
	printf("\nQ ... quit\n");
}

////////////////////////////////////
void showmenu2(int choice)
{
	printf("\nChange...\n");
	printf("X ... X-location\n");
	printf("Y ... Y-location\n");
	printf("C ... Colour\n");
	if (choice != 4 )
		printf("S ... Size\n");
	printf("P ... Points (shape)\n");
	printf("\nN ... no change\n");
}

////////////////////////////////////
int choices(int maxitem)
{
int kpress;
	printf("\n\nKey item number ... 1 to %d\n", maxitem);
	while(1)
	  {
	    kpress = getch();
	    if ( (kpress > 48) && (kpress < 49 + maxitem) )
	    {
	      break;
	    }
	    else
	    {
	      BEEP;
	    }
	  }
	kpress -= 48;
	printf("\n\nItem number %d ",kpress);
	return( kpress );
}
////////////////////////////////////
int actionStatus(int maxitem)
{
	clrscr();
	printf("Properties of items\n");
	return( choices(maxitem) );
}

////////////////////////////////////
int actionBuild(int maxitem)
{
	clrscr();
	printf("Build item ...\n");
	return( choices(maxitem) );
}

////////////////////////////////////
int actionDestroy(int maxitem)
{
	clrscr();
	printf("Destroy item ...\n");
	return( choices(maxitem) );
}

////////////////////////////////////
int GetNumber(void)
{
int num;
	printf("\nKey a number 1 to 9\n");
	while( 1 )
	{
		num = getch();
		if ( ( num > 48 ) && ( num < 58 ) )
		  return( num - 48 );
		BEEP;
	}
}
////////////////////////////////////
int GetRGBY(void)
{
int num;
	printf("\nKey: R(ed), G(reen), B(lue), Y(ellow)\n");
	while( 1 )
	{
		num = getch(); num = toupper(num);
		switch( num )
		{
		case 'R':
			num = 1;
			break;
		case 'G':
			num = 2;
			break;
		case 'B':
			num = 3;
			break;
		case 'Y':
			num = 4;
			break;
		default:
			num = 0;
			BEEP;
		}
		if (num > 0)
			return(num);
	}
}
////////////////////////////////////
int Get3456(void)
{
int num;
	printf("\nKey: T(riangle), S(quare), P(entagon), H(exagon)\n");
	while( 1 )
	{
		num = getch(); num = toupper(num);
		switch( num )
		{
		case 'T':
			num = 3;
			break;
		case 'S':
			num = 4;
			break;
		case 'P':
			num = 5;
			break;
		case 'H':
			num = 6;
			break;
		default:
			num = 0;
			BEEP;
		}
		if (num > 0)
			return(num);
	}
}
////////////////////////////////////
int main(void)
{
int kpress;
int choice;
int FullArea;
int i;

clrscr(); randomize(); printf("Randomising ..."); pause();

shape item[5];				// remember arrays include "0"
lastitem = 4;
item[lastitem].SetExistence( 1 );	// make sure last item exists

	while( 1 )
		{
		showmenu();
		kpress=getch();
		kpress=toupper(kpress);
		switch( kpress )
		{
		case 'P':
			choice = actionStatus(lastitem);
			if (item[choice].GetExistence() == 0)
			{
				printf("does not exist\n");
				pause();
				break;
			}
			clrscr();
			printf("Item %d is a ", choice);
			item[choice].ShowColour();
			item[choice].ShowShape();
			item[choice].ShowLocation();

			if (choice == lastitem)
			{
				FullArea = 200;
				for (i = 1; i < choice; i++)
				{
					if ( item[i].GetExistence() == 1)
					{
						FullArea -= item[i].GetArea();
					}
				}
				item[choice].PutArea( FullArea );
			}

			printf("Size:    %f\n", item[choice].GetSize() );
			printf("Area:    %f\n", item[choice].GetArea() );
			printf("Lateral: %f\n", item[choice].GetLateral() );
			printf("Perim:   %f\n", item[choice].GetPerimeter() );
			printf("Angle:   %d\n", item[choice].GetAngleAtPoint() );

			showmenu2(choice);
			while( 1 )
			{
			kpress=getch();
			kpress=toupper(kpress);
			if ( (kpress == 'S') && (choice == 4) )
			  kpress = 'Z';

			switch( kpress )
			{
			case 'X':
				item[choice].PutXlocation( GetNumber() );
				break;
 			case 'Y':
				item[choice].PutYlocation( GetNumber() );
				break;
			case 'C':
				item[choice].PutColour( GetRGBY() );
				break;
			case 'S':
				item[choice].PutSize( GetNumber() );
				break;
			case 'P':
				item[choice].PutNumberOfPoints( Get3456() );
				break;
			case 'N':
				break;
			default:
				kpress = 'Z';
				BEEP;
				break;
			}
			if(kpress != 'Z')
				break;
			}
			break;
		case 'B':
			choice = actionBuild(lastitem - 1);
			if (item[choice].GetExistence() == 0)
			{
				item[choice].SetExistence( 1 );
				printf("OK\n");
			}
			else
			{
				printf("already exists\n");
				BEEP;
			}
			pause();
			break;

		case 'D':
			choice = actionDestroy(lastitem - 1);
			if (item[choice].GetExistence() == 1)
			{
				item[choice].SetExistence( 0 );
				printf("OK\n");
			}
			else
			{
				printf("does not exist\n");
				BEEP;
			}
			pause();
			break;

		case 'Q':
			exit(0);

		default:
			BEEP
		}
	}
   }
;

