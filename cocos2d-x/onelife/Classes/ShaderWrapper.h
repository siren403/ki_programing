#ifndef __SHADERWRAPPER_H__
#define __SHADERWRAPPER_H__

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class ShaderWrapper
{
public:
	ShaderWrapper();
	ShaderWrapper(const string& fshFileName,Sprite * targetSprite);
	virtual ~ShaderWrapper();

	GLProgramState * GetGLState();
	void SetFloat(const string& uniformName,const float& value);
	void SetVec3(const string& uniformName, const Vec3& value);
protected:
	GLProgram * mGLProgram = nullptr;
	GLProgramState * mGLState = nullptr;
	void InitShaderWithSprite(const string& fshFileName, Sprite * targetSprite);
};

#endif // !__SHADERWRAPPER_H__
