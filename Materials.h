#pragma once

#include <variant>
#include <functional>

enum Material {
	red = 0,
	mirror = 1,
	checkerboard = 2,
	normal = 3,
	magenta = 4,
	cyan = 5,
	white = 6,
	glass = 7,
	red_glass = 8,
	reflective_blue = 9,
	white_light = 10
};

struct MaterialData
{
	std::variant<float3, std::function<float3(float3, float3)>> color; //it either is a static color or gets calculated with the location and normal
	float specularity; //1.0 = 100% reflective
	float transparent; // 1 if not transparent at all, 0 if completely transparent, this has to do with beers law
	float refractive_index; 
	bool isLight;
	MaterialData(
		std::variant<float3, std::function<float3(float3, float3)>> color, 
		float specularity,
		float transparent=1, 
		float refractive_index=0,
		bool isLight=false
	);

	float3 get_color(const float3& pos, const float3& norm) const;
};

const MaterialData materials[11] = {
	MaterialData(float3(1.f,0.f,0.f), 0.0f),
	MaterialData(float3(1.f,1.f,1.f), 1.0f),
	MaterialData([](const float3& pos, const float3& norm) {return (((int)pos.x + (int)pos.z) & 1) ? float3(0.5f,0.8f,0.8f) : float3(0.8f,0.8f,0.5f); }, 0.0f),
	MaterialData([](const float3& pos, const float3& norm) {return (norm+1)/2; } , 0.0f),
	MaterialData(float3(1.f,0.f,1.f), 0.1f),
	MaterialData(float3(0.f,1.f,1.f), 0.1f),
	MaterialData(float3(1.f,1.f,1.f), 0.0f),
	MaterialData(float3(1.f,1.f,1.f), 0.0f, 0.f, 1.5f), //glass
	MaterialData(float3(0.878f,0.066f,0.373f), 0.0f, 0.7f, 1.2f),
	MaterialData(float3(0.1f,0.6f,0.9f), 0.9f),
	MaterialData(float3(10.f,10.f,10.f), 0.0f, 1.f,0.f, true),
};