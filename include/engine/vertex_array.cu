#include "assert.h"
#include "engine/vertex_array.hpp"
#include "cuda_runtime.h"
VertexArray::Iterator VertexArray::begin()
{
    return VertexArray::Iterator(*this);
}
VertexArray::Iterator VertexArray::end()
{
    return VertexArray::Iterator(*this) + this->size();
}

VertexArray::Iterator VertexArray::Iterator::operator++(int)
{
    Iterator temp = *this;
    ++current;
    return temp;
}
VertexArray::Iterator &VertexArray::Iterator::operator++()
{
    ++current;
    return *this;
}

VertexArray::Iterator VertexArray::Iterator::operator+(int x) const
{
    Iterator temp = *this;
    temp.advance(x);
    return temp;
}

void VertexArray::Iterator::advance(int n)
{
    current += n;
}

VertexArray::Iterator::Iterator(VertexArray &va) : current(va.vertices) {}
Vertex &VertexArray::Iterator::operator*() const { return *current; }
Vertex *VertexArray::Iterator::operator->() const { return current; }

bool VertexArray::Iterator::operator==(const Iterator &other) const
{
    return current == other.current;
}
bool VertexArray::Iterator::operator!=(const Iterator &other) const
{
    return current != other.current;
}

VertexArray::VertexArray()
    : vertices(nullptr),
      max_size(0),
      current_size(0) {}
VertexArray::VertexArray(const size_t max_size = 3)
    : max_size(max_size),
      current_size(0)
{
    assert(max_size > 0 && "Max size must be positive");
    if (cudaMallocManaged<Vertex>(&vertices, max_size, cudaMemAttachHost) != cudaSuccess)
    {
        throw std::runtime_error("Failed to allocate memory while copying vertex array");
    }
}
VertexArray::VertexArray(VertexArray &&va)
    : max_size(va.max_size),
      current_size(va.current_size),
      vertices(va.vertices)
{
    va.vertices = nullptr;
}
VertexArray::VertexArray(const VertexArray &other)
    : max_size(other.max_size),
      current_size(other.current_size)
{
    if (cudaMallocManaged<Vertex>(&vertices, max_size, cudaMemAttachHost) != cudaSuccess)
    {
        throw std::runtime_error("Failed to allocate memory while copying vertex array");
    }
    if (cudaMemcpy(vertices, other.vertices, sizeof(Vertex) * current_size, cudaMemcpyDeviceToDevice) != cudaSuccess)
    {
        throw std::runtime_error("Failed to copy vertex array");
    }
}
VertexArray::~VertexArray()
{
    if (vertices != nullptr)
    {
        cudaFree(vertices);
        vertices = nullptr;
    }
}

VertexArray &VertexArray::operator=(const VertexArray &other)
{
    if (vertices != nullptr)
        cudaFree(vertices);

    max_size = other.max_size;
    current_size = other.current_size;
    if (cudaMallocManaged<Vertex>(&vertices, max_size, cudaMemAttachHost) != cudaSuccess)
    {
        throw std::runtime_error("Failed to allocate memory while copying vertex array");
    }
    if (cudaMemcpy(vertices, other.vertices, sizeof(Vertex) * current_size, cudaMemcpyDeviceToDevice) != cudaSuccess)
    {
        throw std::runtime_error("Failed to copy vertex array");
    }
}
VertexArray &VertexArray::operator=(VertexArray &&other)
{
    if (vertices != nullptr)
        cudaFree(vertices);
    vertices = other.vertices;
    other.vertices = nullptr;
    max_size = other.max_size;
    current_size = other.current_size;
}

void VertexArray::push_back(const Vertex &v)
{
    current_size++;
    if (current_size > max_size)
    {
        Vertex *old = vertices;
        if (cudaMallocManaged<Vertex>(&vertices, current_size, cudaMemAttachHost) != cudaSuccess)
        {
            throw std::runtime_error("Can't alloc memory for push back Vertex");
        }
        if (cudaMemcpy(vertices, old, max_size, cudaMemcpyHostToHost) != cudaSuccess)
        {
            throw std::runtime_error("Can't copy memory for push back Vertex");
        }
    }
    else
    {
        vertices[current_size-1] = v;//copy
    }
}

void VertexArray::push_back(Vertex &&v)
{
}
void VertexArray::pop_back()
{
}
// Remove an vertex from the array, with specified index
void VertexArray::pop(int index)
{
}