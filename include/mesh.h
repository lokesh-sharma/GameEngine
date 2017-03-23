#ifndef MESH_INCLUDED_H
#define MESH_INCLUDED_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include<map>

struct Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal)
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	glm::vec3* GetPos() { return &pos; }
	glm::vec2* GetTexCoord() { return &texCoord; }
	glm::vec3* GetNormal() { return &normal; }

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
	glm::vec3 tangent;
};

enum MeshBufferPositions
{
	POSITION_VB,
	TEXCOORD_VB,
	NORMAL_VB,
	TANGENT_VB,
	INDEX_VB,
	NUM_BUFFERS
};

class MeshData
{
public:
    MeshData(const std::string& fileName);

	void Draw();
	void increment() { counter++ ;}
	void decrement() { if(counter>0)counter-- ;}
	int getCount() { return counter ;}
	const std::vector<glm::vec3>& getVerts() { return m_verts;}

	virtual ~MeshData();
protected:
private:
	unsigned int counter;
	void operator=(const MeshData& mesh) {}
	MeshData(const MeshData& mesh) {}

    void LoadMesh(const std::string& filename);
	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
	int m_numIndices;
	std::vector<glm::vec3>m_verts;
};
class Mesh
{
public:
    Mesh(const std::string& fileName);
    MeshData* getMeshData() { return m_meshData ;}
    void Draw();
    void remove();
private:
    static std::map<std::string , MeshData*> meshResource;
    MeshData* m_meshData;
    std::string m_fileName;
    void operator=(const Mesh& mesh) {}
	Mesh(const Mesh& mesh) {}

};

#endif
