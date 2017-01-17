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
};

enum MeshBufferPositions
{
	POSITION_VB,
	TEXCOORD_VB,
	NORMAL_VB,
	INDEX_VB
};

class MeshData
{
public:
    MeshData(const std::string& fileName);

	void Draw();
	void increment() { counter++ ;}
	void decrement() { if(counter>0)counter-- ;}
	int getCount() { return counter ;}

	virtual ~MeshData();
protected:
private:
	static const unsigned int NUM_BUFFERS = 3;
	unsigned int counter;
	void operator=(const MeshData& mesh) {}
	MeshData(const MeshData& mesh) {}

    void LoadMesh(const std::string& filename);
	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
};
class Mesh
{
public:
    Mesh(const std::string& fileName);
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
