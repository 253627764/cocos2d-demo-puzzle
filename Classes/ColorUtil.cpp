#include "ColorUtil.h"  
#include "cocos2d.h"  
using namespace cocos2d;
void ColorUtil::addGray(Sprite* sp)
{
	do
	{
		GLProgram* pProgram = ShaderCache::sharedShaderCache()->programForKey("ssdf");
		sp->setShaderProgram(pProgram);
		CHECK_GL_ERROR_DEBUG();

		sp->getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
		sp->getShaderProgram()->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
		sp->getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
		CHECK_GL_ERROR_DEBUG();

		sp->getShaderProgram()->link();
		CHECK_GL_ERROR_DEBUG();

		sp->getShaderProgram()->updateUniforms();
		CHECK_GL_ERROR_DEBUG();
	} while (0);
}
void ColorUtil::removeGray(Sprite* sp)
{
	do
	{
		GLProgram* pProgram = ShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor);
		sp->setShaderProgram(pProgram);
		CHECK_GL_ERROR_DEBUG();

		sp->getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
		sp->getShaderProgram()->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
		sp->getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
		CHECK_GL_ERROR_DEBUG();

		sp->getShaderProgram()->link();
		CHECK_GL_ERROR_DEBUG();

		sp->getShaderProgram()->updateUniforms();
		CHECK_GL_ERROR_DEBUG();
	} while (0);
}