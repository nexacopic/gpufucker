#pragma once
class FuckerConfig
{
public:
	bool VertexCorruptTimer = true;
	float VertexCorruptMax = 0.1f;
	float VertexCorruptTimerTimeout = 5.0f;
	float ConstantBufferCorruptMax = 0.00001f;

	int FuckedCount = 0;
};