// This function checks if the vertexId of the destination node is equal to the king of the source node and traverses the
// subset array till such a node is found whilst updating the kings of the other nodes
length find(subsets A[], length index)
{
    if (A[index].king != index)
    {
        A[index].king = find(A, A[index].king);
    }
    return A[index].king;
}