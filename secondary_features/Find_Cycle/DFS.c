// This function performs DFS on the currency nodes and takes the help of the Union() and find() functions to update the parameters
// king and rank which detect cycles
length DFS(graph g, ptr_trade_bank bank, ptr_currency currency_src, length pVisited[], char stack[][50], subsets A[], length nfilled)
{
    pVisited[currency_src->vertex_id] = 1;             // for the current node which is being visited, set the corresponding pVisited value to 1
    strcpy(stack[nfilled++], currency_src->id);        // add the name of the current node in the stack array and increment the index pointer
    A[currency_src->vertex_id].position = nfilled - 1; // update the position parameter in the subset array to point at the current position
                                                       // which is filled in the stack array

    ptr_currency temp_adj = currency_src->adj_list;
    while (temp_adj != NULL) // recursively call the DFS() function for all the nodes in the adjacency list of the current node
    {
        length x = find(A, currency_src->vertex_id); // call find function for the src and dest currencies
        length y = find(A, temp_adj->vertex_id);
        if (x == y) // if the kings are the same for src and destination, it means a cycle has been detected
        {
            length start = A[temp_adj->vertex_id].position;
            print_stack(stack, nfilled, start); // call print_stack() function to print the detected cycle
            return 1;                           // return 1 if a cycle is detected
        }

        if (pVisited[temp_adj->vertex_id] != 1) // if the destination node has not already been visited, call DFS() recursively for the dest node
        {
            Union(A, x, y); // call the Union function to update the king and rank of the src and dest currencies
            ptr_currency new = find_currency(g, bank, temp_adj->id);
            if (DFS(g, bank, new, pVisited, stack, A, nfilled) == 1)
            {
                return 1;
            }
        }
        temp_adj = temp_adj->adj_list;
    }
    nfilled--;                                                 // pop the current vertex from the cycle stack when you return from the DFS()
    A[currency_src->vertex_id].king = currency_src->vertex_id; // reset the king of the vertex as the vertexId while returning from DFS
    return 0;                                                  // return 0 if a cycle is not detected
}
