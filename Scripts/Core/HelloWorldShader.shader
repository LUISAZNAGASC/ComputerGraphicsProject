>>>>>>>>>>>>>>>>>>>> VERTEX_SHADER >>>>>>>>>>>>>>>>>>>>

#version 330 core

layout (location = 0) in vec3 l_l_vertexPosition;

layout (location = 1) in vec3 l_l_vertexColor;

out vec3 g_l_vertexColor;

uniform mat4 m_projectionTransform;

uniform mat4 m_cameraTransform;

uniform mat4 m_entityTransform;

void main()
{
	gl_Position = vec4(l_l_vertexPosition.x, l_l_vertexPosition.y, l_l_vertexPosition.z, 1.0);
	gl_Position = m_projectionTransform * m_cameraTransform * m_entityTransform * gl_Position;

	g_l_vertexColor = vec3(l_l_vertexColor.r, l_l_vertexColor.g, l_l_vertexColor.b);
}

<<<<<<<<<<<<<<<<<<<< VERTEX_SHADER <<<<<<<<<<<<<<<<<<<<

>>>>>>>>>>>>>>>>>>>> FRAGMENT_SHADER >>>>>>>>>>>>>>>>>>>>

#version 330 core

out vec4 g_l_fragmentColor;

in vec3 g_l_vertexColor;

void main()
{
	g_l_fragmentColor = vec4(g_l_vertexColor.r, g_l_vertexColor.g, g_l_vertexColor.b, 1.0);
}

<<<<<<<<<<<<<<<<<<<< FRAGMENT_SHADER <<<<<<<<<<<<<<<<<<<<