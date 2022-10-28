#pragma once

#include <string>
#include <vector>
#include "./CG.h"

using std::string;

enum class MeshType { MANUAL, BLENDER };
enum class Shadow { FLAT, SMOOTH };

class Face;
class Edge;
class Vertex;

using VertexesArray = std::vector<Vertex*>;
using EdgesArray = std::vector<Edge*>;
using FacesArray = std::vector<Face*>;

class MeshIntersectionResult : public IntersectionResult {
    private:
        Vector* normal = nullptr;

    public:
        Vector* getNormal();
        void setNormal(Vector* normal);

        MeshIntersectionResult();
        MeshIntersectionResult(Vector* normal);
        ~MeshIntersectionResult();
};

class Face {
    public:
        int edge1Id;
        int edge2Id;
        int edge3Id;

        Face();
        Face(int edge1, int edge2, int edge3);
};

class Edge {
    public:
        int vertex1Id;
        int vertex2Id;

        Edge();
        Edge(int vertex1Id, int vertex2Id);
};

class Vertex {
    public:
        Vector* point = nullptr;
        Vector* normal = nullptr;

        Vertex();
        Vertex(Vector* point, Vector* normal = nullptr);
        ~Vertex();
};

class Mesh : public Object {

    private:
        ObjectType type = ObjectType::MESH;

        VertexesArray vertexesArray;
        EdgesArray edgesArray;
        FacesArray facesArray;

    public:
        ObjectType getObjectType();
        
        VertexesArray getVertexesArray ();
        EdgesArray getEdgesArray();
        FacesArray getFacesArray();

        void addVertex(Vertex* vertex);
        void addEdge(Edge* edge);
        void addFace(Face* face);

        void applyScale(double sx, double sy, double sz);
        void applyTranslate(double x, double y, double z);
        void applyRotateX(double angle);
        void applyRotateY(double angle);
        void applyRotateZ(double angle);
        void applyShearXY(double angle);
        void applyShearYX(double angle);
        void applyShearZX(double angle);
        void applyShearXZ(double angle);
        void applyShearYZ(double angle);
        void applyShearZY(double angle);

        void applyWorldToCanvasConversion(LookAt* lookAt);

        IntersectionResult* getIntersectionResult (Line* line);
        Color* getColorToBePainted (
            IntersectionResult* intersectionResult,
            LightsArray lightsArray,
            ObjectsArray objectsArray,
            Line* line,
            Vector* environmentLight
        );

        Mesh();
        Mesh(double shininess, Vector* reflectivity);
        Mesh(double shininess, Vector* reflectivity, string file);
        ~Mesh();

};
