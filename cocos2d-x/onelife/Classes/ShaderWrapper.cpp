#include "ShaderWrapper.h"

ShaderWrapper::ShaderWrapper()
{
}

ShaderWrapper::ShaderWrapper(const string & fshFileName, Sprite * targetSprite)
{
	InitShaderWithSprite(fshFileName, targetSprite);
}

ShaderWrapper::~ShaderWrapper()
{
	mGLProgram = nullptr;
	mGLState = nullptr;
}

GLProgramState * ShaderWrapper::GetGLState()
{
	return mGLState;
}

void ShaderWrapper::SetFloat(const string & uniformName, const float& value)
{
	if (mGLState != nullptr)
	{
		mGLState->setUniformFloat(uniformName, value);
	}
}

void ShaderWrapper::SetVec3(const string & uniformName, const Vec3 & value)
{
	if (mGLState != nullptr)
	{
		mGLState->setUniformVec3(uniformName, value);
	}
}

void ShaderWrapper::InitShaderWithSprite(const string & fshFileName, Sprite * targetSprite)
{
	auto glCache = GLProgramCache::getInstance();

	if (glCache->getGLProgram(fshFileName) == nullptr)
	{
		auto glProg = GLProgram::createWithFilenames(
			"shader/ccPositionTextureColor_noMVP_vert.vsh", fshFileName);
		glCache->addGLProgram(glProg, fshFileName);
	}

	mGLState = GLProgramState::create(glCache->getGLProgram(fshFileName));
	targetSprite->setGLProgramState(mGLState);
}
