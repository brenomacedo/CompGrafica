#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include "../include/mesh.h"

using std::ifstream;

Vector* MeshIntersectionResult::getNormal() {
    return this->normal;
}

void MeshIntersectionResult::setNormal(Vector* normal) {
    this->normal = normal;
}

MeshIntersectionResult::MeshIntersectionResult() {}

MeshIntersectionResult::MeshIntersectionResult(Vector* normal) {
    this->normal = normal;
}

MeshIntersectionResult::~MeshIntersectionResult() {
    delete this->getNormal();
}

Face::Face() {}

Face::Face(int edge1, int edge2, int edge3) {
    this->edge1Id = edge1;
    this->edge2Id = edge2;
    this->edge3Id = edge3;
}

Edge::Edge() {}

Edge::Edge(int vertex1Id, int vertex2Id) {
    this->vertex1Id = vertex1Id;
    this->vertex2Id = vertex2Id;
}

Vertex::Vertex() {}

Vertex::Vertex(Vector* point, Vector* normal) {
    this->point = point;
    this->normal = normal;
}

Vertex::~Vertex() {
    delete this->point;
    delete this->normal;
}

ObjectType Mesh::getObjectType() {
    return this->type;
}

VertexesArray Mesh::getVertexesArray() {
    return this->vertexesArray;
}

EdgesArray Mesh::getEdgesArray() {
    return this->edgesArray;
}

FacesArray Mesh::getFacesArray() {
    return this->facesArray;
}

void Mesh::addVertex(Vertex* vertex) {
    this->vertexesArray.push_back(vertex);
}

void Mesh::addEdge(Edge* edge) {
    this->edgesArray.push_back(edge);
}

void Mesh::addFace(Face* face) {
    this->facesArray.push_back(face);
}

Mesh::Mesh() {}

Mesh::Mesh(double shininess, Vector* reflectivity) {
    this->shininess = shininess;
    this->reflectivity = reflectivity;
}

Mesh::~Mesh() {
    for (Face* face : this->getFacesArray()) {
        delete face;
    }

    for (Edge* edge : this->getEdgesArray()) {
        delete edge;
    }

    for (Vertex* vertex: this->getVertexesArray()) {
        delete vertex;
    }
}

void Mesh::applyScale(double sx, double sy, double sz) {
    for (Vertex* vertex : this->getVertexesArray()) {
        *vertex->point = scale(
            *vertex->point,
            sx, sy, sz
        );
    }
}

void Mesh::applyTranslate(double x, double y, double z) {
    for (Vertex* vertex : this->getVertexesArray()) {
        *vertex->point = translate(
            *vertex->point,
            x, y, z
        );
    }
}

void Mesh::applyRotateX(double angle) {
    for (Vertex* vertex : this->getVertexesArray()) {
        *vertex->point = rotateX(
            *vertex->point,
            angle
        );
    }
}

void Mesh::applyRotateY(double angle) {
    for (Vertex* vertex : this->getVertexesArray()) {
        *vertex->point = rotateY(
            *vertex->point,
            angle
        );
    }
}

void Mesh::applyRotateZ(double angle) {
    for (Vertex* vertex : this->getVertexesArray()) {
        *vertex->point = rotateZ(
            *vertex->point,
            angle
        );
    }
}

void Mesh::applyShearXY(double angle) {
    for (Vertex* vertex : this->getVertexesArray()) {
        *vertex->point = shearXY(
            *vertex->point,
            angle
        );
    }
}

void Mesh::applyShearYX(double angle) {
    for (Vertex* vertex : this->getVertexesArray()) {
        *vertex->point = shearYX(
            *vertex->point,
            angle
        );
    }
}

void Mesh::applyShearZX(double angle) {
    for (Vertex* vertex : this->getVertexesArray()) {
        *vertex->point = shearZX(
            *vertex->point,
            angle
        );
    }
}

void Mesh::applyShearXZ(double angle) {
    for (Vertex* vertex : this->getVertexesArray()) {
        *vertex->point = shearXZ(
            *vertex->point,
            angle
        );
    }
}

void Mesh::applyShearYZ(double angle) {
    for (Vertex* vertex : this->getVertexesArray()) {
        *vertex->point = shearYZ(
            *vertex->point,
            angle
        );
    }
}

void Mesh::applyShearZY(double angle) {
    for (Vertex* vertex : this->getVertexesArray()) {
        *vertex->point = shearZY(
            *vertex->point,
            angle
        );
    }
}

void Mesh::applyWorldToCanvasConversion(LookAt* lookAt) {
    for (Vertex* vertex : this->getVertexesArray()) {
        *vertex->point = lookAt->convertWorldVectorToCanvas(
            *vertex->point
        );
    }
}

IntersectionResult* Mesh::getIntersectionResult (Line* line) {
    MeshIntersectionResult* result = new MeshIntersectionResult ();
    result->setObjectRegion(ObjectRegion::PLAN);
    result->setHasIntersection(false);
    
    Vector* intersectionPoint = new Vector();
    Vector* meshNormal = new Vector();

    for (Face* meshFace : this->getFacesArray()) {
        int edge1Id = meshFace->edge1Id;
        int edge2Id = meshFace->edge2Id;

        int vertex11Id = this->getEdgesArray()[edge1Id]->vertex1Id;
        int vertex12Id = this->getEdgesArray()[edge1Id]->vertex2Id;

        int vertex21Id = this->getEdgesArray()[edge2Id]->vertex1Id;
        int vertex22Id = this->getEdgesArray()[edge2Id]->vertex2Id;

        int v1, v2, v3;

        int n1 = (vertex11Id + 1) * (vertex12Id + 1);
        int n = n1 / (vertex21Id + 1);

        if (n == (vertex11Id + 1) || n == (vertex12Id + 1)) {
            v1 = vertex21Id;
            v2 = vertex22Id;
            v3 = n - 1;
        } else {
            v1 = vertex22Id;
            v2 = vertex21Id;
            v3 = (n1/(v1 + 1)) - 1;
        }

        Vector P1 = *this->getVertexesArray()[v1]->point;
        Vector P2 = *this->getVertexesArray()[v2]->point;
        Vector P3 = *this->getVertexesArray()[v3]->point;

        Vector r1 = P2 - P1;
        Vector r2 = P3 - P1;

        Vector normal = vectorProduct(r1, r2);
        Vector unitaryNormal = normal / normal.getMagnitude();

        Vector w = *(line->P0) - P1;

        double dirScalarN = scalarProduct (*line->dir, unitaryNormal);
        double t;

        if (dirScalarN != 0 && (t = (-scalarProduct (w, unitaryNormal)) / dirScalarN) > 0) {

            Vector supposedIntersectionPoint = *line->P0 + *line->dir * t;

            Vector distanceVector = (supposedIntersectionPoint) - (*line->P0);
            double distanceFromP0 = distanceVector.getMagnitude();

            Vector v = supposedIntersectionPoint - P1;

            double c1 = scalarProduct(vectorProduct(v, r2), unitaryNormal) / scalarProduct(vectorProduct(r1, r2), unitaryNormal);
            double c2 = scalarProduct(vectorProduct(r1, v), unitaryNormal) / scalarProduct(vectorProduct(r1, r2), unitaryNormal);
            double c3 = 1 - c1 - c2;

            if (c1 >= 0 && c2 >= 0 && c3 >= 0 && (!result->getHasIntersection() || result->getDistanceFromP0() > distanceFromP0)) {
                result->setHasIntersection(true);
                result->setDistanceFromP0(distanceFromP0);
                *intersectionPoint = supposedIntersectionPoint;
                *meshNormal = unitaryNormal;
            }
        }
        
    }

    result->setIntersectionPoint(intersectionPoint);
    result->setNormal(meshNormal);

    return result;
}

Color* Mesh::getColorToBePainted (
    IntersectionResult* intersectionResult,
    LightsArray lightsArray,
    ObjectsArray objectsArray,
    Line* line,
    Vector* environmentLight
) {
    MeshIntersectionResult* meshIntersectionResult = (MeshIntersectionResult*) intersectionResult;

    return this->calculateColorToBePainted(
        intersectionResult,
        lightsArray,
        objectsArray,
        line,
        environmentLight,
        meshIntersectionResult->getNormal(),
        this->getReflectivity(),
        this->getShininess()
    );
}
