// This function compares the kings of 2 given nodes and updates the values of the parameters king and rank
void Union(subsets A[], length src, length dest)
{
    length kingofsrc = find(A, src); // find the king of the 2 given nodes using the find() function
    length kingofdest = find(A, dest);

    if (A[kingofsrc].rank < A[kingofdest].rank) // update the king of the node whose rank is smaller
    {
        A[kingofsrc].king = kingofdest;
    }
    else if (A[kingofsrc].rank > A[kingofdest].rank)
    {
        A[kingofdest].king = kingofsrc;
    }
    else // if A[kingofsrc].rank = A[kingofdest].rank, update the king of one of them and increment the rank of the other
    {
        A[kingofdest].king = kingofsrc;
        A[kingofsrc].rank++;
    }
}