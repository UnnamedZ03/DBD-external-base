#pragma once
#include "global.h"
#include "offset.h"
#include "d3dx9.h"

typedef struct _EntityList
{
	uintptr_t instance;
	uintptr_t mesh;
	uintptr_t root_component;
	uintptr_t instigator;
	uintptr_t PlayerState;
	uintptr_t Pawn;
	Vector3 TopLocation;
	Vector3 bone_origin;
	std::string name;
	Vector3 origin;
	float health;
	float dist;
	int objectId;
	int team;     
}EntityList;

std::vector<EntityList> entityList;

struct FMinimalViewInfo
{
	Vector3 Location; // 0x00(0x0c)
	Vector3 Rotation; // 0x0c(0x0c)
	float FOV; // 0x18(0x04)
};
struct FCameraCacheEntry
{
	float Timestamp; // 0x00(0x04)
	char pad_4[0xc]; // 0x04(0x0c)
	FMinimalViewInfo POV; // 0x10(0x5e0)
};

class UPlayer {
private:
public:
	uintptr_t instance;
	uintptr_t mesh;
	uintptr_t root_component;
	uintptr_t OutlineComponent;
	uintptr_t instigator;
	uintptr_t PlayerState;
	uintptr_t Pawn;
	Vector3 TopLocation;
	std::string name;
	int objectId;
	Vector3 origin;
	float health;
	float dist;
	int team;
};

D3DMATRIX MatrixMultiplication(D3DMATRIX pM1, D3DMATRIX pM2)
{
	D3DMATRIX pOut;
	pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
	pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
	pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
	pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
	pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
	pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
	pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
	pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
	pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
	pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
	pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
	pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
	pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
	pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
	pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
	pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;

	return pOut;
}

struct FTransform
{
	Vector4 rot;
	Vector3 translation;
	char pad[4];
	Vector3 scale;
	char pad1[4];

	D3DMATRIX ToMatrixWithScale()
	{
		D3DMATRIX m;
		m._41 = translation.x;
		m._42 = translation.y;
		m._43 = translation.z;

		float x2 = rot.x + rot.x;
		float y2 = rot.y + rot.y;
		float z2 = rot.z + rot.z;

		float xx2 = rot.x * x2;
		float yy2 = rot.y * y2;
		float zz2 = rot.z * z2;
		m._11 = (1.0f - (yy2 + zz2)) * scale.x;
		m._22 = (1.0f - (xx2 + zz2)) * scale.y;
		m._33 = (1.0f - (xx2 + yy2)) * scale.z;

		float yz2 = rot.y * z2;
		float wx2 = rot.w * x2;
		m._32 = (yz2 - wx2) * scale.z;
		m._23 = (yz2 + wx2) * scale.y;

		float xy2 = rot.x * y2;
		float wz2 = rot.w * z2;
		m._21 = (xy2 - wz2) * scale.y;
		m._12 = (xy2 + wz2) * scale.x;

		float xz2 = rot.x * z2;
		float wy2 = rot.w * y2;
		m._31 = (xz2 + wy2) * scale.z;
		m._13 = (xz2 - wy2) * scale.x;

		m._14 = 0.0f;
		m._24 = 0.0f;
		m._34 = 0.0f;
		m._44 = 1.0f;

		return m;
	}
};

static D3DMATRIX CreateMatrix(Vector3 rot, Vector3 origin) {
	const float DEG_TO_RAD = static_cast<float>(3.14159265358979323846) / 180.f;
	const float radPitch = rot.x * DEG_TO_RAD;
	const float radYaw = rot.y * DEG_TO_RAD;
	const float radRoll = rot.z * DEG_TO_RAD;

	const float SP = sinf(radPitch);
	const float CP = cosf(radPitch);
	const float SY = sinf(radYaw);
	const float CY = cosf(radYaw);
	const float SR = sinf(radRoll);
	const float CR = cosf(radRoll);

	D3DMATRIX matrix;
	matrix.m[0][0] = CP * CY;
	matrix.m[0][1] = CP * SY;
	matrix.m[0][2] = SP;
	matrix.m[0][3] = 0.f;

	matrix.m[1][0] = SR * SP * CY - CR * SY;
	matrix.m[1][1] = SR * SP * SY + CR * CY;
	matrix.m[1][2] = -SR * CP;
	matrix.m[1][3] = 0.f;

	matrix.m[2][0] = -(CR * SP * CY + SR * SY);
	matrix.m[2][1] = CY * SR - CR * SP * SY;
	matrix.m[2][2] = CR * CP;
	matrix.m[2][3] = 0.f;

	matrix.m[3][0] = origin.x;
	matrix.m[3][1] = origin.y;
	matrix.m[3][2] = origin.z;
	matrix.m[3][3] = 1.f;

	return matrix;
}

static Vector3 WorldToScreen(FMinimalViewInfo camera, Vector3 WorldLocation) 
{
	Vector3 Screenlocation(0, 0, 0);
	const D3DMATRIX tempMatrix = CreateMatrix(camera.Rotation, Vector3(0, 0, 0));

	Vector3 vAxisX(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	Vector3 vAxisY(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	Vector3 vAxisZ(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

	Vector3 vDelta = WorldLocation - camera.Location;
	Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

	if (vTransformed.z < 1.f)
		vTransformed.z = 1.f;

	const float FOV_DEG_TO_RAD = static_cast<float>(3.14159265358979323846) / 360.f;

	Screenlocation.x = ScreenCenterX + vTransformed.x * (ScreenCenterX / tanf(
		camera.FOV * FOV_DEG_TO_RAD)) / vTransformed.z;
	Screenlocation.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / tanf(
		camera.FOV * FOV_DEG_TO_RAD)) / vTransformed.z;

	return Screenlocation;
}

static std::string GetNameById(uint32_t actor_id) 
{
	char pNameBuffer[256];
	int TableLocation = (unsigned int)(actor_id >> 0x10);
	uint16_t RowLocation = (unsigned __int16)actor_id;
	uint64_t GNameTable = process_base + offsets::GNames;

	uint64_t TableLocationAddress = DBD->rpm<uint64_t>(GNameTable + 0x10 + TableLocation * 0x8) + (unsigned __int32)(4 * RowLocation);

	uint64_t sLength = (unsigned __int64)(DBD->rpm<uint16_t>(TableLocationAddress + 4)) >> 1;

	if (sLength < 128)
	{
		DBD->ReadRaw((TableLocationAddress + 6), pNameBuffer, sLength);
		return std::string(pNameBuffer);
	}
	return std::string("NULL");
}