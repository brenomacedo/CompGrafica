#include "../include/cup.h"

Mesh* Cup::createWithBorderInCenaryCenter(Vector* reflectivity, double shininness) {
    Mesh* mesh = new Mesh (shininness, reflectivity);
    mesh->addVertex(
        new Vertex(
            new Vector(
                0, 0, 10
            )
        )
    ); // 0
    mesh->addVertex(
        new Vertex(
            new Vector(
                10, 0, 10
            )
        )
    ); // 1
    mesh->addVertex(
        new Vertex(
            new Vector(
                0, 0, 0
            )
        )
    ); // 2
    mesh->addVertex(
        new Vertex(
            new Vector(
                10, 0, 0
            )
        )
    ); // 3
    mesh->addVertex(
        new Vertex(
            new Vector(
                0, 10, 10
            )
        )
    ); // 4
    mesh->addVertex(
        new Vertex(
            new Vector(
                10, 10, 10
            )
        )
    ); // 5
    mesh->addVertex(
        new Vertex(
            new Vector(
                0, 10, 0
            )
        )
    ); // 6
    mesh->addVertex(
        new Vertex(
            new Vector(
                10, 10, 0
            )
        )
    ); // 7
    mesh->addVertex(
        new Vertex(
            new Vector(
                2, 2, 8
            )
        )
    ); // 8
    mesh->addVertex(
        new Vertex(
            new Vector(
                8, 2, 8
            )
        )
    ); // 9
    mesh->addVertex(
        new Vertex(
            new Vector(
                2, 2, 2
            )
        )
    ); // 10
    mesh->addVertex(
        new Vertex(
            new Vector(
                8, 2, 2
            )
        )
    ); // 11
    mesh->addVertex(
        new Vertex(
            new Vector(
                2, 10, 8
            )
        )
    ); // 12
    mesh->addVertex(
        new Vertex(
            new Vector(
                8, 10, 8
            )
        )
    ); // 13
    mesh->addVertex(
        new Vertex(
            new Vector(
                2, 10, 2
            )
        )
    ); // 14
    mesh->addVertex(
        new Vertex(
            new Vector(
                8, 10, 2
            )
        )
    ); // 15


    // -----------------------------------------------

    mesh->addEdge(
        new Edge(
            0, 1
        )
    ); // 0
    mesh->addEdge(
        new Edge(
            1, 3
        )
    ); // 1
    mesh->addEdge(
        new Edge(
            3, 0
        )
    ); // 2
    mesh->addEdge(
        new Edge(
            0, 2
        )
    ); // 3
    mesh->addEdge(
        new Edge(
            2, 3
        )
    ); // 4
    mesh->addEdge(
        new Edge(
            0, 4
        )
    ); // 5
    mesh->addEdge(
        new Edge(
            4, 5
        )
    ); // 6
    mesh->addEdge(
        new Edge(
            5, 1
        )
    ); // 7
    mesh->addEdge(
        new Edge(
            5, 0
        )
    ); // 8
    mesh->addEdge(
        new Edge(
            3, 7
        )
    ); // 9
    mesh->addEdge(
        new Edge(
            7, 5
        )
    ); // 10
    mesh->addEdge(
        new Edge(
            7, 1
        )
    ); // 11
    mesh->addEdge(
        new Edge(
            2, 6
        )
    ); // 12
    mesh->addEdge(
        new Edge(
            6, 7
        )
    ); // 13
    mesh->addEdge(
        new Edge(
            6, 3
        )
    ); // 14
    mesh->addEdge(
        new Edge(
            0, 4
        )
    ); // 15
    mesh->addEdge(
        new Edge(
            4, 6
        )
    ); // 16
    mesh->addEdge(
        new Edge(
            4, 2
        )
    ); // 17

    // --------------------------------------------------------

    mesh->addEdge(
        new Edge(
            8, 9
        )
    ); // 18
    mesh->addEdge(
        new Edge(
            9, 11
        )
    ); // 19
    mesh->addEdge(
        new Edge(
            11, 8
        )
    ); // 20
    mesh->addEdge(
        new Edge(
            8, 10
        )
    ); // 21
    mesh->addEdge(
        new Edge(
            10, 11
        )
    ); // 22
    mesh->addEdge(
        new Edge(
            8, 12
        )
    ); // 23
    mesh->addEdge(
        new Edge(
            12, 13
        )
    ); // 24
    mesh->addEdge(
        new Edge(
            13, 9
        )
    ); // 25
    mesh->addEdge(
        new Edge(
            13, 8
        )
    ); // 26
    mesh->addEdge(
        new Edge(
            11, 15
        )
    ); // 27
    mesh->addEdge(
        new Edge(
            15, 13
        )
    ); // 28
    mesh->addEdge(
        new Edge(
            15, 9
        )
    ); // 29
    mesh->addEdge(
        new Edge(
            10, 14
        )
    ); // 30
    mesh->addEdge(
        new Edge(
            14, 15
        )
    ); // 31
    mesh->addEdge(
        new Edge(
            14, 11
        )
    ); // 32
    mesh->addEdge(
        new Edge(
            8, 12
        )
    ); // 33
    mesh->addEdge(
        new Edge(
            12, 14
        )
    ); // 34
    mesh->addEdge(
        new Edge(
            12, 10
        )
    ); // 35

    // -----------------------------------------------------

    mesh->addEdge(
        new Edge(
            12, 13
        )
    ); // 36
    mesh->addEdge(
        new Edge(
            13, 15
        )
    ); // 37
    mesh->addEdge(
        new Edge(
            15, 14
        )
    ); // 38
    mesh->addEdge(
        new Edge(
            14, 12
        )
    ); // 39
    
    mesh->addEdge(
        new Edge(
            5, 13
        )
    ); // 40
    mesh->addEdge(
        new Edge(
            7, 15
        )
    ); // 41
    mesh->addEdge(
        new Edge(
            6, 14
        )
    ); // 42
    mesh->addEdge(
        new Edge(
            4, 12
        )
    ); // 43

    mesh->addEdge(
        new Edge(
            4, 13
        )
    ); // 44
    mesh->addEdge(
        new Edge(
            5, 15
        )
    ); // 45
    mesh->addEdge(
        new Edge(
            7, 14
        )
    ); // 46
    mesh->addEdge(
        new Edge(
            6, 12
        )
    ); // 47

    // -------------------------- FACES ---------------------

    mesh->addFace(
        new Face(
            0, 2, 1
        )
    );
    mesh->addFace(
        new Face(
            2, 3, 4
        )
    );
    mesh->addFace(
        new Face(
            8, 6, 5
        )
    );
    mesh->addFace(
        new Face(
            7, 8, 0
        )
    );
    mesh->addFace(
        new Face(
            10, 7, 11
        )
    );
    mesh->addFace(
        new Face(
            1, 9, 11
        )
    );
    mesh->addFace(
        new Face(
            14, 13, 9
        )
    );
    mesh->addFace(
        new Face(
            14, 4, 12
        )
    );
    mesh->addFace(
        new Face(
            17, 16, 12
        )
    );
    mesh->addFace(
        new Face(
            17, 3, 5
        )
    );

    // ----------------------------------------------------------------

    mesh->addFace(
        new Face(
            18, 20, 19
        )
    );
    mesh->addFace(
        new Face(
            20, 21, 22
        )
    );
    mesh->addFace(
        new Face(
            23, 24, 26
        )
    );
    mesh->addFace(
        new Face(
            18, 26, 25
        )
    );
    mesh->addFace(
        new Face(
            29, 25, 28
        )
    );
    mesh->addFace(
        new Face(
            29, 27, 19
        )
    );
    mesh->addFace(
        new Face(
            27, 31, 32
        )
    );
    mesh->addFace(
        new Face(
            30, 22, 32
        )
    );
    mesh->addFace(
        new Face(
            30, 34, 35
        )
    );
    mesh->addFace(
        new Face(
            23, 21, 35
        )
    );

    // --------------------------------------------------------------------------

    mesh->addFace(
        new Face(
            6, 40, 44
        )
    );
    mesh->addFace(
        new Face(
            44, 24, 43
        )
    );
    mesh->addFace(
        new Face(
            45, 37, 40
        )
    );
    mesh->addFace(
        new Face(
            45, 10, 41
        )
    );
    mesh->addFace(
        new Face(
            31, 41, 46
        )
    );
    mesh->addFace(
        new Face(
            46, 13, 42
        )
    );
    mesh->addFace(
        new Face(
            47, 34, 42
        )
    );
    mesh->addFace(
        new Face(
            47, 16, 43
        )
    );

    return mesh;
}