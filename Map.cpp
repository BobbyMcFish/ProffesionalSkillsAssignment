#include "Map.h"
extern vector <CMap*> map;
CMap::CMap()
{
	mapChar = NULL;
    yMin = 0;
	yMax = 0;
	xMin = 0;
	xMax = 0;
	platform = NULL;
	platformMesh = myEngine->LoadMesh("Platform.x");;
}

CMap::~CMap()
{

}

void CMap::MapLoading(IModel* ground)
{
	ifstream inp;
	inp.open("test.txt");
	int index = 0;
	CMap temp;
	while(!inp.eof())
	{
		inp >> temp.mapChar; 
		map.push_back(new CMap());
		map[index]->mapChar = temp.mapChar;
		index++;
	}
	inp.close();

	float y = 120.0f;
	float x = -1500.0f;
	float z = -20.0f;
	int SIZE = map.size();
	for(int i = 0; i < SIZE; i++)
	{
		if(map[i]->mapChar != '0')
		{
			map[i]->platform = platformMesh->CreateModel(x, y, z);
			map[i]->platform->AttachToParent(ground);
		}
		x += 150.0f;

		if( i % 10 == 0 && i != 0)
		{
			y -= 40.0f;
			x = -1500.0f;
		}
	}
}

void CMap::setMinMax()
{
	int SIZE = map.size();
	float platformX;
	float platformY;
	for (int i = 0; i < SIZE; i++)
	{
		if(map[i]->mapChar != '0')
		{
			platformX = map[i]->platform->GetX();
			platformY = map[i]->platform->GetY();
			//yMin equals bottom of the platforms
			map[i]->yMin = platformY - 5.0f;
			//yMax equals the top of the platforms
			map[i]->yMax = platformY + 5.0f;
			//xMin equals the left of the platforms
			map[i]->xMin = platformX -95.0f  ;
			//xMax equals the right of the platforms
			map[i]->xMax = platformX + -5.0f;
		}
	}
}

bool CMap::collisionDetection(IModel* player, int in)
{
	/*point to box collsion*/
		
	//X > XMin && X < XMax &&
	//Y > YMin && Y < YMax &&
	//Z > ZMin && Z < ZMax
	
	/*sphere to box*/

	//Expand the bounding box outwards by the sphere’s radius, i.e. XMin becomes XMin – Radius, XMax becomes XMax + Radius etc.
	//Shrink the sphere’s radius down to 0, i.e. assume it is a point.
	//Now we simply have the point-box collision situation again, and we can use the formula above.
	//This method won’t be accurate around the corners of the box, but using approximations like this is perfectly appropriate in some situations.

	//returns true or false depending on whether their has been a collsion or not
	float radius = 13.0f;
	float playerY = 5.0f - radius;
	float playerX = 0.0f;

	if(map[in]->mapChar != '0')
	{
		if(playerX > map[in]->xMin - radius && playerX < map[in]->xMax  + radius && playerY > map[in]->yMin && playerY < map[in]->yMax)
		{
			if(map[in]->yMax - playerY  < playerY - map[in]->yMin)
			{
				return true;
			}
		}
		else
		{
			return false;
		}
	}
	return false;
}