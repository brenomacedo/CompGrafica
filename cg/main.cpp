#include <iostream>
#include <string>
#include <cmath>
#include "./include/CGI.h"

using std::string;

int main () {

    Mesh* mesh = new Mesh (5.0, new Vector(1,0.0,0.0));
    mesh->addVertex(
        new Vertex(
            new Vector(20, 20, -40)
        )
    );
    mesh->addVertex(
        new Vertex(
            new Vector(20, 20, -60)
        )
    );
    mesh->addVertex(
        new Vertex(
            new Vector(40, 20, -60)
        )
    );
    mesh->addVertex(
        new Vertex(
            new Vector(40, 20, -40)
        )
    );
    mesh->addVertex(
        new Vertex(
            new Vector(20, 40, -40)
        )
    );
    mesh->addVertex(
        new Vertex(
            new Vector(20, 40, -60)
        )
    );
    mesh->addVertex(
        new Vertex(
            new Vector(40, 40, -60)
        )
    );
    mesh->addVertex(
        new Vertex(
            new Vector(40, 40, -40)
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
    

    Light* light = new Light (
        new Vector (0.7, 0.7, 0.7),
        new Vector (0, 60, 0)
    );

    Sp<Scene> scene = new Scene (
        new Vector (0, 0, 0),
        60.0, 60.0,
        500, 500,
        30,
        new Color (100, 100, 100, 255)
    );

    scene->setEnvironmentLight (
        new Vector (0.3, 0.3, 0.3)
    );

    scene->addLightSource(light);
    scene->addObject(mesh);

    scene->render();

    return 0;
}
