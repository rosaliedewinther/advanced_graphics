#include "precomp.h"
#include "RayHelper.h"



Material get_material_hitptr(const Ray& r) {
	switch (r.p) {
	case Primitive::triangle: return ((Triangle*)r.hitptr)->m;
	case Primitive::sphere: return ((Sphere*)r.hitptr)->m;
	case Primitive::plane: return ((Plane*)r.hitptr)->m;
	}
}

float3 get_normal_hitptr(const Ray& r, const float3& pos) {
	switch (r.p) {
	case Primitive::triangle: return ((Triangle*)r.hitptr)->get_normal();
	case Primitive::sphere: return ((Sphere*)r.hitptr)->get_normal(pos);
	case Primitive::plane: return ((Plane*)r.hitptr)->get_normal();
	}
}