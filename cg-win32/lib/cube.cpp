#include "../include/cube.h"

Mesh* Cube::create(Vector* baseCenter, double edgeSize, Vector* reflectivity, double shininness) {
    Mesh* mesh = new Mesh (shininness, reflectivity);
    mesh->addVertex(
        new Vertex(
            new Vector(
                (*baseCenter)[0] - (edgeSize/2),
                (*baseCenter)[1],
                (*baseCenter)[2] - (edgeSize/2)
            )
        )
    );
    mesh->addVertex(
        new Vertex(
            new Vector(
                (*baseCenter)[0] - (edgeSize/2),
                (*baseCenter)[1],
                (*baseCenter)[2] + (edgeSize/2)
            )
        )
    );
    mesh->addVertex(
        new Vertex(
            new Vector(
                (*baseCenter)[0] + (edgeSize/2),
                (*baseCenter)[1],
                (*baseCenter)[2] + (edgeSize/2)
            )
        )
    );
    mesh->addVertex(
        new Vertex(
            new Vector(
                (*baseCenter)[0] + (edgeSize/2),
                (*baseCenter)[1],
                (*baseCenter)[2] - (edgeSize/2)
            )
        )
    );
    mesh->addVertex(
        new Vertex(
            new Vector(
                (*baseCenter)[0] - (edgeSize/2),
                (*baseCenter)[1] + edgeSize,
                (*baseCenter)[2] - (edgeSize/2)
            )
        )
    );
    mesh->addVertex(
        new Vertex(
            new Vector(
                (*baseCenter)[0] - (edgeSize/2),
                (*baseCenter)[1] + edgeSize,
                (*baseCenter)[2] + (edgeSize/2)
            )
        )
    );
    mesh->addVertex(
        new Vertex(
            new Vector(
                (*baseCenter)[0] + (edgeSize/2),
                (*baseCenter)[1] + edgeSize,
                (*baseCenter)[2] + (edgeSize/2)
            )
        )
    );
    mesh->addVertex(
        new Vertex(
            new Vector(
                (*baseCenter)[0] + (edgeSize/2),
                (*baseCenter)[1] + edgeSize,
                (*baseCenter)[2] - (edgeSize/2)
            )
        )
    );

    delete baseCenter;

    mesh->addEdge(
        new Edge(0, 1)
    );
    mesh->addEdge(
        new Edge(1, 2)
    );
    mesh->addEdge(
        new Edge(2, 3)
    );
    mesh->addEdge(
        new Edge(3, 0)
    );
    mesh->addEdge(
        new Edge(4, 5)
    );
    mesh->addEdge(
        new Edge(5, 6)
    );
    mesh->addEdge(
        new Edge(6, 7)
    );
    mesh->addEdge(
        new Edge(7, 4)
    );
    mesh->addEdge(
        new Edge(0, 4)
    );
    mesh->addEdge(
        new Edge(1, 5)
    );
    mesh->addEdge(
        new Edge(2, 6)
    );
    mesh->addEdge(
        new Edge(3, 7)
    );
    mesh->addEdge(
        new Edge(2, 7)
    );
    mesh->addEdge(
        new Edge(5, 7)
    );
    mesh->addEdge(
        new Edge(5, 2)
    );
    mesh->addEdge(
        new Edge(1, 4)
    );
    mesh->addEdge(
        new Edge(1, 3)
    );
    mesh->addEdge(
        new Edge(3, 4)
    );
    mesh->addFace(
        new Face(6, 10, 12)
    );
    mesh->addFace(
        new Face(12, 2, 11)
    );
    mesh->addFace(
        new Face(7, 4, 13)
    );
    mesh->addFace(
        new Face(13, 5, 6)
    );
    mesh->addFace(
        new Face(5, 14, 10)
    );
    mesh->addFace(
        new Face(9, 1, 14)
    );
    mesh->addFace(
        new Face(4, 15, 9)
    );
    mesh->addFace(
        new Face(8, 0, 15)
    );
    mesh->addFace(
        new Face(1, 16, 2)
    );
    mesh->addFace(
        new Face(3, 16, 10)
    );
    mesh->addFace(
        new Face(11, 17, 7)
    );
    mesh->addFace(
        new Face(3, 8, 17)
    );

    return mesh;
}

Mesh* Cube::createUnitaryWithBorderInCenaryCenter(Vector* reflectivity, double shininness) {
    Mesh* mesh = new Mesh (shininness, reflectivity);
    mesh->addVertex(
        new Vertex(
            new Vector(0, 0, 0)
        )
    );
    mesh->addVertex(
        new Vertex(
            new Vector(0, 0, 1)
        )
    );
    mesh->addVertex(
        new Vertex(
            new Vector(1, 0, 1)
        )
    );
    mesh->addVertex(
        new Vertex(
            new Vector(1, 0, 0)
        )
    );
    mesh->addVertex(
        new Vertex(
            new Vector(0, 1, 0)
        )
    );
    mesh->addVertex(
        new Vertex(
            new Vector(0, 1, 1)
        )
    );
    mesh->addVertex(
        new Vertex(
            new Vector(1, 1, 1)
        )
    );
    mesh->addVertex(
        new Vertex(
            new Vector(1, 1, 0)
        )
    );

    mesh->addEdge(
        new Edge(0, 1)
    );
    mesh->addEdge(
        new Edge(1, 2)
    );
    mesh->addEdge(
        new Edge(2, 3)
    );
    mesh->addEdge(
        new Edge(3, 0)
    );
    mesh->addEdge(
        new Edge(4, 5)
    );
    mesh->addEdge(
        new Edge(5, 6)
    );
    mesh->addEdge(
        new Edge(6, 7)
    );
    mesh->addEdge(
        new Edge(7, 4)
    );
    mesh->addEdge(
        new Edge(0, 4)
    );
    mesh->addEdge(
        new Edge(1, 5)
    );
    mesh->addEdge(
        new Edge(2, 6)
    );
    mesh->addEdge(
        new Edge(3, 7)
    );
    mesh->addEdge(
        new Edge(2, 7)
    );
    mesh->addEdge(
        new Edge(5, 7)
    );
    mesh->addEdge(
        new Edge(5, 2)
    );
    mesh->addEdge(
        new Edge(1, 4)
    );
    mesh->addEdge(
        new Edge(1, 3)
    );
    mesh->addEdge(
        new Edge(3, 4)
    );
    mesh->addFace(
        new Face(6, 10, 12)
    );
    mesh->addFace(
        new Face(12, 2, 11)
    );
    mesh->addFace(
        new Face(7, 4, 13)
    );
    mesh->addFace(
        new Face(13, 5, 6)
    );
    mesh->addFace(
        new Face(5, 14, 10)
    );
    mesh->addFace(
        new Face(9, 1, 14)
    );
    mesh->addFace(
        new Face(4, 15, 9)
    );
    mesh->addFace(
        new Face(8, 0, 15)
    );
    mesh->addFace(
        new Face(1, 16, 2)
    );
    mesh->addFace(
        new Face(3, 16, 10)
    );
    mesh->addFace(
        new Face(11, 17, 7)
    );
    mesh->addFace(
        new Face(3, 8, 17)
    );

    return mesh;
}

Mesh* Cube::createWithTexture(Vector* baseCenter, double edgeSize, Image* image, double shininness) {
    Mesh* mesh = new MeshWithTexture (image, shininness);
    mesh->addVertex(
        new Vertex(
            new Vector(
                (*baseCenter)[0] - (edgeSize/2),
                (*baseCenter)[1],
                (*baseCenter)[2] - (edgeSize/2)
            )
        )
    );
    mesh->addVertex(
        new Vertex(
            new Vector(
                (*baseCenter)[0] - (edgeSize/2),
                (*baseCenter)[1],
                (*baseCenter)[2] + (edgeSize/2)
            )
        )
    );
    mesh->addVertex(
        new Vertex(
            new Vector(
                (*baseCenter)[0] + (edgeSize/2),
                (*baseCenter)[1],
                (*baseCenter)[2] + (edgeSize/2)
            )
        )
    );
    mesh->addVertex(
        new Vertex(
            new Vector(
                (*baseCenter)[0] + (edgeSize/2),
                (*baseCenter)[1],
                (*baseCenter)[2] - (edgeSize/2)
            )
        )
    );
    mesh->addVertex(
        new Vertex(
            new Vector(
                (*baseCenter)[0] - (edgeSize/2),
                (*baseCenter)[1] + edgeSize,
                (*baseCenter)[2] - (edgeSize/2)
            )
        )
    );
    mesh->addVertex(
        new Vertex(
            new Vector(
                (*baseCenter)[0] - (edgeSize/2),
                (*baseCenter)[1] + edgeSize,
                (*baseCenter)[2] + (edgeSize/2)
            )
        )
    );
    mesh->addVertex(
        new Vertex(
            new Vector(
                (*baseCenter)[0] + (edgeSize/2),
                (*baseCenter)[1] + edgeSize,
                (*baseCenter)[2] + (edgeSize/2)
            )
        )
    );
    mesh->addVertex(
        new Vertex(
            new Vector(
                (*baseCenter)[0] + (edgeSize/2),
                (*baseCenter)[1] + edgeSize,
                (*baseCenter)[2] - (edgeSize/2)
            )
        )
    );

    delete baseCenter;

    mesh->addEdge(
        new Edge(0, 1)
    );
    mesh->addEdge(
        new Edge(1, 2)
    );
    mesh->addEdge(
        new Edge(2, 3)
    );
    mesh->addEdge(
        new Edge(3, 0)
    );
    mesh->addEdge(
        new Edge(4, 5)
    );
    mesh->addEdge(
        new Edge(5, 6)
    );
    mesh->addEdge(
        new Edge(6, 7)
    );
    mesh->addEdge(
        new Edge(7, 4)
    );
    mesh->addEdge(
        new Edge(0, 4)
    );
    mesh->addEdge(
        new Edge(1, 5)
    );
    mesh->addEdge(
        new Edge(2, 6)
    );
    mesh->addEdge(
        new Edge(3, 7)
    );
    mesh->addEdge(
        new Edge(2, 7)
    );
    mesh->addEdge(
        new Edge(5, 7)
    );
    mesh->addEdge(
        new Edge(5, 2)
    );
    mesh->addEdge(
        new Edge(1, 4)
    );
    mesh->addEdge(
        new Edge(1, 3)
    );
    mesh->addEdge(
        new Edge(3, 4)
    );
    mesh->addFace(
        new Face(6, 10, 12)
    );
    mesh->addFace(
        new Face(12, 2, 11)
    );
    mesh->addFace(
        new Face(7, 4, 13)
    );
    mesh->addFace(
        new Face(13, 5, 6)
    );
    mesh->addFace(
        new Face(5, 14, 10)
    );
    mesh->addFace(
        new Face(9, 1, 14)
    );
    mesh->addFace(
        new Face(4, 15, 9)
    );
    mesh->addFace(
        new Face(8, 0, 15)
    );
    mesh->addFace(
        new Face(1, 16, 2)
    );
    mesh->addFace(
        new Face(3, 16, 10)
    );
    mesh->addFace(
        new Face(11, 17, 7)
    );
    mesh->addFace(
        new Face(3, 8, 17)
    );

    return mesh;
}