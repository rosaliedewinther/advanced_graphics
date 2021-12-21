#pragma once
#include <vector>
#include "Triangle.h"


struct BVHNode {
	AABB bounds;
	int leftFirst;
	int count;
};

template<typename T>
class BVH
{
public:
	std::unique_ptr<uint[]> indices;
	std::unique_ptr<BVHNode[]> pool;
	std::vector<T> primitives;
	std::unique_ptr<float3[]> centers;
	uint concat_depth = 0;
	uint section_width = pow(2, concat_depth+1);

	BVH() = default;
	BVH(std::vector<T> primitives, bool use_SAH);

	void intersects(Ray& r) const;
private:
	void flatten(BVHNode* node);
	int count_depth(BVHNode* node) const;
	int count_nodes(BVHNode* node) const;
	void write_to_dot_file(std::string filename) const;
	void subdivide(BVHNode* parent, std::atomic<uint>& poolPtr, uint indices_start, bool use_SAH);
	int partition(const AABB& bb, uint start, uint count, bool use_SAH);
	int partition_shuffle(int axis, float pos, uint start, uint count);
	void instantiated_intersect(Ray& r) const;
	void intersect_internal(Ray& r, int node_index = 0) const;
	AABB CalculateBounds(uint first, uint amount) const;
};

struct TopBVHNode {
	BVH<Triangle>* obj;
	float3 pos;
};

using TopLevelBVH = BVH<TopBVHNode>;


void intersect_primitive(const TopBVHNode& node, Ray& ray);