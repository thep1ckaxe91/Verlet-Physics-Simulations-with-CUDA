#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP
#include "engine/math.hpp"

/**
 * @brief Vertex array that created vertices on device memory
 * 
 * When the array is create with max_size param, it will not create empty Vertex, instead it allocate the space for max_size element, so that when call push_back, it doesnt have to reallocate again
 * 
 * This does not meant to modify the vertices in the code, but preloaded/created from files
 * 
 * There's VertexArray::from_file function that allow load from file
 * 
 * The object itself can easily be modify, but that's for the editor, not for the game to modify
 * 
 * Maybe there'll be defect interaction, who know? 
 * 
 */
struct VertexArray
{
    Vertex *vertices;
    size_t max_size;
    size_t current_size;
    class Iterator
    {
    public:
        Iterator(VertexArray &va);

        Vertex &operator*() const;
        Vertex *operator->() const;

        Iterator &operator++();
        Iterator operator+(int x) const;
        Iterator operator++(int);

        bool operator==(const Iterator &other) const;
        bool operator!=(const Iterator &other) const;

        void advance(int n);

    private:
        Vertex *current;
    };
    VertexArray();
    VertexArray(const size_t max_size);
    VertexArray(VertexArray &&va);
    VertexArray(const VertexArray &other);

    /*TODO: make a function to load vertex from a
    .vex file contains many lines, each line have the following formular

    float float uint8 uint8 uint8 uint8 float float

    one line must have at least 2 float represent position
    next 4 uint8 is the info about color
    next 2 float is info about texture coordinate

    if file is not a .vex format or if file doesnt exist, it will throw an error

    file wrote in binary mode
    */
    static VertexArray from_file(const char *path);
    //This will call from_file(path.c_str())
    static VertexArray from_file(const std::string &path);
    //Get the pointer to the memory address, which is the vertex buffer itself
    Vertex *data() const;
    //Get the size of the vertex array
    size_t size() const;
    VertexArray &operator=(const VertexArray &other);
    VertexArray &operator=(VertexArray &&other);
    Vertex &operator[](const size_t i);
    
    /**
     * @brief add another vertex at the end of the array, if the array reach its max size, it will reallocate
     * 
     * @param v the vertex 
     */
    void push_back(const Vertex& v);
    void push_back(Vertex&& v);
    void pop_back();
    //Remove an vertex from the array, with specified index
    void pop(int index);
    Iterator begin();
    Iterator end();

    ~VertexArray();
};



#endif