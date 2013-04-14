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

void CMap::MapLoading(IModel* ground)
{
	ifstream inp;
	inp.open("Level1.txt");
	int index = 0;
	CMap temp;
	vector <CMap*> tmp;

	while(!inp.eof())
	{
		inp >> temp.mapChar; 
		tmp.push_back(new CMap());
		tmp[index]->mapChar = temp.mapChar;
		index++;
	}
	inp.close();

	float y = 120.0f;
	float x = 1500.0f;
	float z = -20.0f;
	int in = 0;
	int SIZE = tmp.size();
	for(int i = 0; i < SIZE; i++)
	{
		if(tmp[i]->mapChar == ';')
		{
			y -= 40.0f;
			x = -1500.0f;
		}
		else if(tmp[i]->mapChar == '1')
		{
			map.push_back(new CMap());
			map[in]->platform = platformMesh->CreateModel(x, y, z);
			map[in]->platform->AttachToParent(ground);
			in++;
		}
		x += 100.0f;
	}
}

void CMap::setMinMax()
{
	int SIZE = map.size();
	float platformX;
	float platformY;
	for (int i = 0; i < SIZE; i++)
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
	float playerY = 10.0f - radius;
	float playerX = 0.0f;

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
	return false;
}