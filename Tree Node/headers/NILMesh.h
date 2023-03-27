#ifndef NILMESH_H
#define NILMESH_H

#include <stdio.h>
#include <string.h>
#include <vector>
#include <SDFArchive.h>

struct NILMeshVector3
{
	float x = -69.69f, y = -69.69f, z = -69.69f, w = 1.0f;
};
struct NILMeshVectori3
{
	int x = -69; int y = -69; int z = -69;
};
struct NILFace
{
	NILMeshVectori3 Data[3];
};
struct NILTri
{
	NILMeshVector3 Triangle[3];
};
struct NILMeshVector2
{
	float x, y;
};
struct NILMesh
{
	std::vector<NILMeshVector3> Vertexes;
	std::vector<NILMeshVector3> Normals;
	std::vector<NILMeshVector2> TextureCoordinates;
	std::vector<NILMeshVectori3> Faces;
	NILMeshVector3 Min;
	NILMeshVector3 Max;
	bool Empty(){return !Vertexes.empty(); }
	~NILMesh(){Vertexes.clear(); Normals.clear(); TextureCoordinates.clear(); Faces.clear(); }
	float AbsMax;
};
struct NILTriMesh
{
	std::vector<NILTri> Triangles;
	NILMeshVector3 Min;
	NILMeshVector3 Max;
};
inline int NILGetMesh(const char* src, NILMesh& Mesh)
{
	int SRCLength = strlen(src);
	char EXT[4] = { src[SRCLength - 3], src[SRCLength - 2], src[SRCLength - 1], '\0'};
	if (strcmp(EXT, "obj")) { return 0; }
	FILE* ObjectFile = NULL;
	errno_t badFile = fopen_s(&ObjectFile, src, "r");
	if (badFile != 0 || ObjectFile == NULL) { return 0; }
	char EndBuffer[255];
	NILMeshVector3 Min = { 2147483647.0f, 2147483647.0f, 2147483647.0f };
	NILMeshVector3 Max = { -2147483647.0f, -2147483647.0f, -2147483647.0f};
	fpos_t closePos = -69;
	while (fgets(EndBuffer, 255, ObjectFile))
	{
		//char* token = strtok(EndBuffer, " \t\r\n");
		char twotoken[3] = {EndBuffer[0], EndBuffer[1], '\0'};
		if(strcmp(twotoken, "v ") == 0)
		{
			NILMeshVector3 Vectoid;
			sscanf(EndBuffer, "v %f %f %f", &Vectoid.x, &Vectoid.y, &Vectoid.z);
			Min = { (Min.x * !(Vectoid.x < Min.x)) + Vectoid.x * (Vectoid.x < Min.x), (Min.y * !(Vectoid.y < Min.y)) + Vectoid.y * (Vectoid.y < Min.y), (Min.z * !(Vectoid.z < Min.z)) + Vectoid.z * (Vectoid.z < Min.z) };

			Max = { (Max.x * !(Vectoid.x > Max.x)) + Vectoid.x * (Vectoid.x > Max.x), (Max.y * !(Vectoid.y > Max.y)) + Vectoid.y * (Vectoid.y > Max.y),(Max.z * !(Vectoid.z > Max.z)) + Vectoid.z * (Vectoid.z > Max.z) };
			float x1 = abs(Vectoid.x), y1 = abs(Vectoid.y), y3 = abs(Vectoid.z);
			x1 = (x1 > y1) ? x1 : y1;
			y1 = (x1 > y3) ? x1 : y3;
			Mesh.AbsMax = (Mesh.AbsMax > y1) ? Mesh.AbsMax : y1;
			Mesh.Vertexes.push_back(Vectoid);
		}
		else if (strcmp(twotoken,"vt") == 0)
		{
			NILMeshVector2 Vectoid;
			sscanf(EndBuffer, "vt %f %f", &Vectoid.x, &Vectoid.y);
			Mesh.TextureCoordinates.push_back(Vectoid);
		}
		else if (strcmp(twotoken,"vn") == 0)
		{
			NILMeshVector3 Vectoid;
			sscanf(EndBuffer, "vn %f %f %f", &Vectoid.x, &Vectoid.y, &Vectoid.z);
			Mesh.Normals.push_back(Vectoid);
		}
		else if (strcmp(twotoken, "f ") == 0)
		{
			NILMeshVectori3 Vectoid;
			char* looking = EndBuffer;
			looking+=2;
			
			int skip = 0;
			while (looking != nullptr)
			{
				int scan = sscanf(looking, "%d/%d/%d", &Vectoid.x, &Vectoid.y, &Vectoid.z);
				looking = strchr(looking, ' ');
				if(looking){ looking++; }
				Mesh.Faces.push_back(Vectoid);
				
			}
			
			
		}
	}

	fclose(ObjectFile);
	Mesh.Min = Min;
	Mesh.Max = Max;
	return 1;
	
}



inline float NILGetMax(NILMeshVector3 Min, NILMeshVector3 Max)
{

	float x1 = abs(Min.x);
	float x2 = abs(Max.x);
	float y1 = abs(Min.y);
	float y2 = abs(Max.y);
	float z1 = abs(Min.z);
	float z2 = abs(Max.z);

	float x3 = (x1 > x2) ? x1 : x2;
	float y3 = (y1 > y2) ? y1 : y2;
	float z3 = (z1 > z2) ? z1 : z2;

	float xy = (x3 > y3) ? x3 : y3;
	float xz = (xy > z3) ? xy : z3;
	return xz;
}

inline int SDFComposeMesh(const NILMesh& ReferenceMesh, SDFMesh& NewMesh)
{
	float Mag = 0;
	SDFFace TemporaryFace;
	int CurrentCycle = 0;
	for (int i = 0; i < ReferenceMesh.Faces.size(); i++)
	{
		NILMeshVectori3 Index = ReferenceMesh.Faces[i];
		Index.x--; Index.y--; Index.z--;
		if (Index.z < ReferenceMesh.Normals.size() && CurrentCycle == 0)
		{
			//TemporaryFace.Normal = {ReferenceMesh.Normals[Index.z].x, ReferenceMesh.Normals[Index.z].y, ReferenceMesh.Normals[Index.z].z} ;
		}
		if (Index.x < ReferenceMesh.Vertexes.size())
		{

			if(CurrentCycle == 0)
				TemporaryFace.v0 = {ReferenceMesh.Vertexes[Index.x].x, ReferenceMesh.Vertexes[Index.x].y, ReferenceMesh.Vertexes[Index.x].z};
			if(CurrentCycle == 1) 
				TemporaryFace.v1 = {ReferenceMesh.Vertexes[Index.x].x, ReferenceMesh.Vertexes[Index.x].y, ReferenceMesh.Vertexes[Index.x].z};
			if(CurrentCycle == 2)
				TemporaryFace.v2 = {ReferenceMesh.Vertexes[Index.x].x, ReferenceMesh.Vertexes[Index.x].y, ReferenceMesh.Vertexes[Index.x].z};
			CurrentCycle++;
		}
		if(CurrentCycle > 2)
		{
			NewMesh.faces.push_back(TemporaryFace);
			CurrentCycle = 0;
		}
		
	}
	return 1;
}

inline NILMesh NILComposeMesh(const NILMesh& ReferenceMesh)
{
	NILMesh NewMesh;
	float Mag = 0;

	for (int i = 0; i < ReferenceMesh.Faces.size(); i++)
	{
		NILMeshVectori3 Index = ReferenceMesh.Faces[i];
		Index.x--; Index.y--; Index.z--;
		if (Index.x < ReferenceMesh.Vertexes.size())
		{
			NILMeshVector3 Vertex = ReferenceMesh.Vertexes[Index.x];
			//Vertex.x /= ReferenceMesh.AbsMax;
			//Vertex.y /= ReferenceMesh.AbsMax;
			//Vertex.z /= ReferenceMesh.AbsMax;
			NewMesh.Vertexes.push_back(Vertex);
		}
		if (Index.y < ReferenceMesh.TextureCoordinates.size())
		{
			NILMeshVector2 VT = ReferenceMesh.TextureCoordinates[Index.y];
			NewMesh.TextureCoordinates.push_back(VT);
		}
		if (Index.z < ReferenceMesh.Normals.size())
		{
			NILMeshVector3 VN = ReferenceMesh.Normals[Index.z];
			NewMesh.Normals.push_back(VN);
		}
	}
	return NewMesh;
}

inline NILMesh GetComposedMesh(const char* src)
{
    NILMesh ReturnMesh;
    NILGetMesh(src, ReturnMesh);
    ReturnMesh = NILComposeMesh(ReturnMesh);
    return ReturnMesh;
}
inline int SDFComposedMesh(const char* src, SDFMesh& OutputMesh, SDFBoundingVolume& OutputVolume)
{
	NILMesh ReturnMesh;
    int MeshStatus = NILGetMesh(src, ReturnMesh);
	OutputVolume.BottomRightBack = {ReturnMesh.Max.x, ReturnMesh.Min.y, ReturnMesh.Max.z};
	OutputVolume.TopLeftFront = {ReturnMesh.Min.x, ReturnMesh.Max.y, ReturnMesh.Min.z};
	if(!MeshStatus){return 0;}
	return SDFComposeMesh(ReturnMesh, OutputMesh);
}
inline double NILGaussian(double r, double epsilon)
{
	return exp(-epsilon * r * r);
}
inline NILMeshVector3 Substract(NILMeshVector3 A, NILMeshVector3 B)
{
	return { A.x - B.x, A.y - B.y, A.z - B.z };
}
inline double Magnitude(NILMeshVector3 A)
{
	return sqrt((A.x * A.x) + (A.y * A.y) + (A.z * A.z));
}
inline double NILRBF(const std::vector<NILMeshVector3>& Mesh, const std::vector<double>& coeffs, const std::vector<NILMeshVector3>& centers, double epsilon)
{
	double sum = 0;
	for (int i = 0; i < centers.size(); ++i)
	{
		NILMeshVector3 dXYZ = Substract(Mesh[i], centers[i]);
		double r = Magnitude(dXYZ);
		sum += coeffs[i] * NILGaussian(r, epsilon);
	}
	return sum;
}
inline std::vector<double> FindCoefficients(const std::vector<NILMeshVector3>& samplePoints, const std::vector<double>& sampleValues, const std::vector<NILMeshVector3>& centers, double epsilon)
{
	int numSamplePoints = samplePoints.size();
	int numCenters = centers.size();

	std::vector<std::vector<double>> A(numSamplePoints, std::vector<double>(numCenters));
	std::vector<double> b(numSamplePoints);

	for (int i = 0; i < numSamplePoints; ++i)
	{
		for (int j = 0; j < numCenters; ++j)
		{
			NILMeshVector3 dXYZ = Substract(samplePoints[i], centers[j]);
			double r = Magnitude(dXYZ);
			A[i][j] = NILGaussian(r, epsilon);
		}
		b[i] = sampleValues[i];
	}

	std::vector<double> x(numCenters);
	for (int i = 0; i < numCenters; ++i)
	{
		double pivot = A[i][i];
		for (int j = i + 1; j < numSamplePoints; ++j)
		{
			double scale = A[j][i] / pivot;
			for (int k = i + 1; k < numCenters; ++k)
			{
				A[j][k] -= scale * A[i][k];
			}
			b[j] -= scale * b[i];
		}
	}

	for (int i = numCenters - 1; i >= 0; --i)
	{
		double sum = 0;
		for (int j = i + 1; j < numCenters; ++j)
		{
			sum += A[i][j] * x[j];
		}
		x[i] = (b[i] - sum) / A[i][i];
	}

	return x;
}



#endif
