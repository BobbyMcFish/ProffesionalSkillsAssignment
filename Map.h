#ifndef _MAP
#define _MAP
#include <TL-Engine.h>
#include <fstream>
#include <vector>
using namespace tle;
extern I3DEngine* myEngine;

class CMap
{
private:
	char mapChar; // stores the map as an array of Chars
	float xMin, xMax, yMin, yMax;
	IModel* platform;
	IMesh* platformMesh;
public:
	CMap();
	~CMap();
	void MapLoading(IModel* ground);
	void setMinMax();
	bool collisionDetection(IModel* player, int in);
};
#endif