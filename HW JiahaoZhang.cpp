#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>       /* sin cos */
#include <string>

using namespace std;

#define PI 3.14159265

class Point{
public :
	double x, y, z;
	Point(double x, double y, double z){
		this->x = x;
		this->y = y;
		this->z = z;
	
	}
	friend inline ostream & operator << (ostream & os, Point &a)
	{
		os << a.x << " " << a.y << " " << a.z;
		return os;
	}
};
  

class Cylinder {
private:
	/*double x,y,z,r, h;
	int facets;*/
	vector<Point> facetsData;
	void push_vertex(Point a1, Point a2, Point a3, Point a4 )
	{
		facetsData.push_back(a1);
		facetsData.push_back(a2);
		facetsData.push_back(a3);
		facetsData.push_back(a4);
	}
public:
	Cylinder(double x, double y, double z, double r, double h, int facets)  {
	/*	this->x = x;		this->r = r;
		this->y = y;		this->h = h;
		this->z = z;		this->facets = facets;*/

			//slice the circle to how many facets? => sin theta, cos theta, theta = 360/facets
		//deal with top and bottom first
		//top
		for (int i = 0; i < facets; i++) {
			Point a1( 0, 0, 1);
			Point a2(x + r * sin(360 / facets * i * PI / 180), y + r * cos(360 / facets * i * PI / 180), z + h);
			Point a3(x + r * sin(360 / facets * (i + 1) * PI / 180), y + r * cos(360 / facets * (i + 1) * PI / 180), z + h);
			Point a4(x, y, z + h);
			push_vertex(a1, a2, a3, a4);
		}
		//bottom
		for (int i = 0; i < facets; i++) {
			Point a1(0, 0, -1);
			Point a2(x + r * sin(360 / facets * i * PI / 180), y + r * cos(360 / facets * i * PI / 180), z);
			Point a3(x, y, z);
			Point a4(x + r * sin(360 / facets * (i + 1) * PI / 180), y + r * cos(360 / facets * (i + 1) * PI / 180), z);
			push_vertex(a1, a2, a3, a4);
		}
		//side, theta/2
		for (int i = 0; i < facets; i++) {
			Point a1(sin(360 / 2 / facets * i * PI / 180), cos(360 / 2 / facets * i * PI / 180), 0);
			Point a2(x + r * sin(360 / facets * i * PI / 180), y + r * cos(360 / facets * i * PI / 180), z + h);
			Point a3(x + r * sin(360 / facets * i * PI / 180), y + r * cos(360 / facets * i * PI / 180), z);
			Point a4(x + r * sin(360 / facets * (i + 1) * PI / 180), y + r * cos(360 / facets * (i + 1) * PI / 180), z + h);
			push_vertex(a1, a2, a3, a4);
			Point a5(sin(360 / 2 / facets * i * PI / 180), cos(360 / 2 / facets * i * PI / 180), 0);
			Point a6(x + r * sin(360 / facets * i * PI / 180), y + r * cos(360 / facets * i * PI / 180), z);
			Point a7(x + r * sin(360 / facets * (i + 1) * PI / 180), y + r * cos(360 / facets * (i + 1) * PI / 180), z);
			Point a8(x + r * sin(360 / facets * (i + 1) * PI / 180), y + r * cos(360 / facets * (i + 1) * PI / 180), z + h);
			push_vertex(a5, a6, a7, a8);
		}
	}

	vector<Point> getFacetsData() {
		return facetsData;
	}
};

class Cube  {
private:
	//double size;
	//double x, y, z;
	vector<Point> facetsData;
	void push_vertex(Point a1, Point a2, Point a3, Point a4)
	{
		facetsData.push_back(a1);
		facetsData.push_back(a2);
		facetsData.push_back(a3);
		facetsData.push_back(a4);
	}
public:
	Cube(double x, double y, double z, double size)  {
		/*this->size = size;		this->y = y;
	this->x = x;				this->z = y;*/
		// six facets, just iterate all of them, can't find easier solution
		// 0 0 1
		{
			Point a1(0, 0, 1);
			Point a2(x, y + size, z + size);
			Point a3(x + size, y + size, z + size);
			Point a4(x + size, y, z + size);
			push_vertex(a1, a2, a3, a4);
		}
		{
		Point a1(0, 0, 1);
		Point a2(x, y + size, z + size);
		Point a3(x + size, y, z + size);
		Point a4(x, y, z + size);
		push_vertex(a1, a2, a3, a4);
	}
		{	// 0 0 -1
			Point a1(0, 0, -1);
			Point a2(x, y + size, z);
			Point a3(x + size, y, z);
			Point a4(x + size, y + size, z);
			push_vertex(a1, a2, a3, a4);
		}
		{
			Point a1(0, 0, -1);
			Point a2(x, y + size, z);
			Point a3(x, y, z);
			Point a4(x + size, y, z);
			push_vertex(a1, a2, a3, a4);
		}
		{
			// 0 1 0
			Point a1(0, 1, 0);
			Point a2(x, y + size, z + size);
			Point a3(x, y + size, z);
			Point a4(x + size, y + size, z);
			push_vertex(a1, a2, a3, a4);
		}
		{
			Point a1(0, 1, 0);
			Point a2(x, y + size, z + size);
			Point a3(x + size, y + size, z);
			Point a4(x + size, y + size, z + size);
			push_vertex(a1, a2, a3, a4);
		}
		{
			// 0 -1 0
			Point a1(0, -1, 0);
			Point a2(x, y, z + size);
			Point a3(x + size, y, z);
			Point a4(x, y, z);
			push_vertex(a1, a2, a3, a4);
		}
		{
			Point a1(0, -1, 0);
			Point a2(x, y, z + size);
			Point a3(x + size, y, z + size);
			Point a4(x + size, y, z);
			push_vertex(a1, a2, a3, a4);
		}
		{
			// 1 0 0
			Point a1(1, 0, 0);
			Point a2(x + size, y + size, z);
			Point a3(x + size, y, z);
			Point a4(x + size, y, z + size);
			push_vertex(a1, a2, a3, a4);
		}
		{
			Point a1(1, 0, 0);
			Point a2(x + size, y + size, z + size);
			Point a3(x + size, y + size, z);
			Point a4(x + size, y, z + size);
			push_vertex(a1, a2, a3, a4);
		}
		{
			// -1 0 0
			Point a1(-1, 0, 0);
			Point a2(x, y + size, z);
			Point a3(x, y, z + size);
			Point a4(x, y, z);
			push_vertex(a1, a2, a3, a4);
		}
		{
			Point a1(-1, 0, 0);
			Point a2(x, y + size, z + size);
			Point a3(x, y, z + size);
			Point a4(x, y + size, z);
			push_vertex(a1, a2, a3, a4);
		}	
	}
	vector<Point> getFacetsData() {
		return facetsData;
	}
};


class CAD {
private:
	vector<Point> facetsData;
public:

	void add(Cylinder temp) {
		vector<Point> temp_Data = temp.getFacetsData();
		//if (facetsData.empty())
		//	facetsData = temp_Data;
	//	else
			facetsData.insert(facetsData.end(), temp_Data.begin(), temp_Data.end());
	}
	void add(Cube temp) {
		vector<Point> temp_Data = temp.getFacetsData();
	//	if (facetsData.empty())
	//		facetsData = temp_Data;
	//	else
			facetsData.insert(facetsData.end(), temp_Data.begin(), temp_Data.end());
	}

	void write(string fileName) {
		ofstream myfile(fileName);
		//myfile.open(fileName);
		myfile << "solid test_model" << endl;
		
			int size = facetsData.size();
			for (int i = 0; i < size; i += 4) {
				myfile << "  facet normal " << facetsData[i] << endl;
				myfile << "    outer loop" << endl;
				myfile << "      vertex " << facetsData[i + 1]  << endl;
				myfile << "      vertex " << facetsData[i + 2] << endl;
				myfile << "      vertex " << facetsData[i + 3] << endl;
				myfile << "    endloop" << endl;
				myfile << "  endfacet" << endl;
			}
		myfile << "endsolid test_model" << endl;
		myfile.close();
	}
};
int main()
{
	CAD c;
	c.add(Cube(0, 0, 0, 100));
	c.add(Cylinder(100, 100, 0, 30, 100, 10));
	c.write("test.stl");
	
}

