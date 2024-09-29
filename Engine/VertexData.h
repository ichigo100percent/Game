#pragma once

struct VertexData
{
	Vector3 position = { 0, 0, 0 };
};

struct VertexTextureData
{
	Vector3 position = { 0, 0, 0 };
	Vector2 uv = { 0, 0 };
};

struct VertexColorData
{
	Vector3 position = { 0, 0, 0 };
	Color color = { 0, 0, 0, 0 };
};

struct VertexTextureNormalData
{
	Vector3 position = { 0, 0, 0 };
	Vector2 uv = { 0, 0 };
	Vector3 normal = { 0, 0, 0 };
};

struct VertexTextureNormalTangentData
{
	Vector3 position = { 0, 0, 0 };
	Vector2 uv = { 0, 0 };
	Vector3 normal = { 0, 0, 0 };
	Vector3 tangent = { 0, 0, 0 };
};