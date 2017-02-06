#include "Glow.h"

bool Glow::init()
{
	if (!Node::init())
	{
		return false;
	}

	/*auto tHelloTex = TextureCache::getInstance()->addImage("HelloWorld.png");
	Size tHelloTexSize = tHelloTex->getContentSize();
	float tIncreaseSize = 10;
	auto sprite = Sprite::createWithTexture(tHelloTex,
	Rect(-tIncreaseSize, -tIncreaseSize,
	tHelloTexSize.width + tIncreaseSize * 2, tHelloTexSize.height + tIncreaseSize * 2));*/

	mSprite = Sprite::create("HelloWorld_1.png");
	this->addChild(mSprite);

	Vec4 color(0.5f, 0.5f, 0.5f, 1.0f);
	m_ctime = 0.01f;  // メンバ変数
	GLfloat gtime = 1.0f;
	GLfloat radius = 5.0f;

	//auto fileUtiles = FileUtils::getInstance();
	//auto fragmentFullPath = fileUtiles->fullPathForFilename("glow.fsh");
	//auto fragSource = fileUtiles->getStringFromFile(fragmentFullPath);

	//auto glprogram = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
	auto glprogram = GLProgram::createWithFilenames("shader/glow.vsh", "shader/glow.fsh");
	auto glProgramState = GLProgramState::getOrCreateWithGLProgram(glprogram);

	glProgramState->setUniformVec4("u_outlineColor", color);
	glProgramState->setUniformFloat("u_ctime", m_ctime);
	glProgramState->setUniformFloat("u_threshold", gtime);
	glProgramState->setUniformFloat("u_radius", radius);

	mSprite->setGLProgramState(glProgramState);

	glProgramState->setUniformCallback("u_ctime", CC_CALLBACK_2(Glow::callbackColor, this));

	return true;
}
Sprite * Glow::GetSprite()
{
	return mSprite;
}
void Glow::callbackColor(GLProgram* glProgram, Uniform* uniform)
{
	m_ctime += 0.05f;
	glProgram->setUniformLocationWith1f(uniform->location, (sin(m_ctime) + 1) / 2);
}