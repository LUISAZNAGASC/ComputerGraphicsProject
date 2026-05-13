#ifndef _SHADER_COMPONENT_HPP_
#define _SHADER_COMPONENT_HPP_

#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

#pragma once
class ShaderComponent
{
private:
	GLuint shaderProgramIdentifier;

	const std::string AnalizeShaderDocument(const std::string& shaderDocumentLocation) const;

	const std::string ExtractShaderSegment(const std::string& shaderDocumentSource, const std::string& shaderSegmentName) const;

	const GLint GetShaderUniformLocation(const std::string& shaderUniformIdentifier) const;

protected:

public:
	ShaderComponent(const std::string& shaderProgramLocation);

	~ShaderComponent();

	ShaderComponent(const ShaderComponent& otherShaderComponent) = delete;

	ShaderComponent& operator=(const ShaderComponent& otherShaderComponent) = delete;

	const void HandleActivateOperation() const;

	const void HandleDeactivateOperation() const;

	const void HandleDestroyOperation() const;

	const void SetShaderBooleanUniform(const std::string& shaderUniformIdentifier, const bool shaderUniformValue) const;

	const void SetShaderIntegerUniform(const std::string& shaderUniformIdentifier, const int shaderUniformValue) const;

	const void SetShaderDecimalUniform(const std::string& shaderUniformIdentifier, const float shaderUniformValue) const;

	const void SetShaderVector2Uniform(const std::string& shaderUniformIdentifier, const glm::vec2 shaderUniformValue) const;

	const void SetShaderVector3Uniform(const std::string& shaderUniformIdentifier, const glm::vec3 shaderUniformValue) const;

	const void SetShaderVector4Uniform(const std::string& shaderUniformIdentifier, const glm::vec4 shaderUniformValue) const;

	const void SetShaderMatrix2Uniform(const std::string& shaderUniformIdentifier, const glm::mat2 shaderUniformValue) const;

	const void SetShaderMatrix3Uniform(const std::string& shaderUniformIdentifier, const glm::mat3 shaderUniformValue) const;

	const void SetShaderMatrix4Uniform(const std::string& shaderUniformIdentifier, const glm::mat4 shaderUniformValue) const;

	const GLuint GetShaderProgramIdentifier() const;
};

#endif