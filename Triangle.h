#pragma once
#include "Materials.h"
#include "Ray.h"

class Triangle
{
	float3 p0;
	float3 p1;
	float3 p2;
	float3 normal;
public:
	Material m;
	Triangle(float3 p0, float3 p1, float3 p2, float3 normal, Material material);
	void intersects(Ray& ray) const;
	float3 get_normal() const;
};

std::vector<Triangle> get_mesh_from_file(const std::string& filename, float scalefactor, float3 position, Material material);