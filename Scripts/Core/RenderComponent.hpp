#pragma once

struct VertexData final
{
    glm::vec3 m_vertexPosition; glm::vec3 m_vertexColor;
};

class RenderComponent final
{
private:
    GLuint m_vertexArrayIdentifier; GLuint m_vertexBufferIdentifier; GLuint m_indexBufferIdentifier;
    
    std::vector<VertexData> m_meshVertexCollection; std::vector<GLuint> m_meshIndexCollection;
    
    GLvoid PrepareRenderComponent();
    
    GLvoid ReleaseRenderComponent();

public:
    RenderComponent() = delete;
    
    RenderComponent(const std::vector<VertexData>& meshVectorCollection, const std::vector<GLuint>& meshIndexCollection);
    
    ~RenderComponent();
    
    RenderComponent(const RenderComponent& otherRenderComponent) = delete;
    
    RenderComponent(RenderComponent&& otherRenderComponent) noexcept;
    
    RenderComponent& operator=(const RenderComponent& otherRenderComponent) = delete;
    
    RenderComponent& operator=(RenderComponent&& otherRenderComponent) noexcept;
    
    GLvoid DisplayRenderComponent() const;
};

RenderComponent::RenderComponent(const std::vector<VertexData>& meshVertexCollection, const std::vector<GLuint>& meshIndexCollection)
{
    m_vertexArrayIdentifier = 0; m_vertexBufferIdentifier = 0; m_indexBufferIdentifier = 0;
    
    m_meshVertexCollection = meshVertexCollection; m_meshIndexCollection = meshIndexCollection;
    
    PrepareRenderComponent();
}

RenderComponent::~RenderComponent()
{
    ReleaseRenderComponent();
}

RenderComponent::RenderComponent(RenderComponent&& otherRenderComponent) noexcept
{
    m_vertexArrayIdentifier = std::exchange(otherRenderComponent.m_vertexArrayIdentifier, 0);
    
    m_vertexBufferIdentifier = std::exchange(otherRenderComponent.m_vertexBufferIdentifier, 0);
    
    m_indexBufferIdentifier = std::exchange(otherRenderComponent.m_indexBufferIdentifier, 0);
    
    m_meshVertexCollection = std::exchange(otherRenderComponent.m_meshVertexCollection, {});
    
    m_meshIndexCollection = std::exchange(otherRenderComponent.m_meshIndexCollection, {});
}

RenderComponent& RenderComponent::operator=(RenderComponent&& otherRenderComponent) noexcept
{
    if (this == &otherRenderComponent) { return *this; }
    
    ReleaseRenderComponent();
    
    m_vertexArrayIdentifier = std::exchange(otherRenderComponent.m_vertexArrayIdentifier, 0);
    
    m_vertexBufferIdentifier = std::exchange(otherRenderComponent.m_vertexBufferIdentifier, 0);
    
    m_indexBufferIdentifier = std::exchange(otherRenderComponent.m_indexBufferIdentifier, 0);
    
    m_meshVertexCollection = std::exchange(otherRenderComponent.m_meshVertexCollection, {});
    
    m_meshIndexCollection = std::exchange(otherRenderComponent.m_meshIndexCollection, {});
    
    return *this;
}

GLvoid RenderComponent::PrepareRenderComponent()
{
    glGenVertexArrays(1, &m_vertexArrayIdentifier); glGenBuffers(1, &m_vertexBufferIdentifier); glGenBuffers(1, &m_indexBufferIdentifier);
    
    glBindVertexArray(m_vertexArrayIdentifier);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferIdentifier);
    glBufferData(GL_ARRAY_BUFFER, m_meshVertexCollection.size() * sizeof(VertexData), m_meshVertexCollection.data(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferIdentifier);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_meshIndexCollection.size() * sizeof(GLuint), m_meshIndexCollection.data(), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid*)offsetof(VertexData, m_vertexPosition));
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid*)offsetof(VertexData, m_vertexColor));
    
    glBindVertexArray(0); glBindBuffer(GL_ARRAY_BUFFER, 0); glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLvoid RenderComponent::DisplayRenderComponent() const
{
    glBindVertexArray(m_vertexArrayIdentifier); glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferIdentifier); glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferIdentifier);
    
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_meshIndexCollection.size()), GL_UNSIGNED_INT, (const GLvoid*)(0 * sizeof(GLuint)));
    
    glBindVertexArray(0); glBindBuffer(GL_ARRAY_BUFFER, 0); glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLvoid RenderComponent::ReleaseRenderComponent()
{
    if (m_vertexArrayIdentifier != 0) { glDeleteVertexArrays(1, &m_vertexArrayIdentifier); }
    
    if (m_vertexBufferIdentifier != 0) { glDeleteBuffers(1, &m_vertexBufferIdentifier); }
    
    if (m_indexBufferIdentifier != 0) { glDeleteBuffers(1, &m_indexBufferIdentifier); }
    
    m_meshVertexCollection.clear(); m_meshVertexCollection.shrink_to_fit();
    
    m_meshIndexCollection.clear(); m_meshIndexCollection.shrink_to_fit();
}
