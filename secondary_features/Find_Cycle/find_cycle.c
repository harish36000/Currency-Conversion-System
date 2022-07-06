//checks whether there is a cycle in the given trade bank
void Find_cycle(graph g, char *bank_name)
{
    length flag = 0;
    //bank points to the required tradebank
    ptr_trade_bank bank = find_trade_bank(g, bank_name);
    //checks if bank exists
    if (bank == NULL)
    {
        return;
    }

    //used to detect and print a cycle
    subsets A[bank->nvertices];
    //stores the currency names. useful while printing a cycle
    char stack[bank->nvertices][50];
    //stores whether a vertex is visited or not in the rest of the function
    length pVisited[bank->nvertices];
    //stores the number of currency names stored in the 2D stack array
    length nfilled = 0;
    //forloop initializes the subsets array(A) and pVisited
    for (int i = 0; i < bank->nvertices; i++)
    {
        A[i].king = i;
        A[i].rank = 0;
        pVisited[i] = 0;
    }
    //traverses through all the currency nodes
    for (int i = 0; i < bank->last_index; i++)
    {
        //current points to the separate chaining of the currency hashtable in the check[i] index
        ptr_currency current = bank->list_currency[bank->check[i]];
        //traverses through the separate chaining
        while (current != NULL)
        {
            //checks whether the currency node is already visited
            if (pVisited[current->vertex_id] != 1)
            {
                //this does DFS for this currency node
                //DFS will detect a cycle if it exists and will print one cycle
                //returns 1 if there is a cycle
                //else returns 0
                flag = DFS(g, bank, current, pVisited, stack, A, nfilled);
                //checks whether the cycle is detected
                if (flag == 1)
                {
                    return;
                }
            }
            //traversal of separate chaining
            current = current->next;
        }
    }
    //checks whether there is no cycle in whole tradebank graph
    if (flag == 0)
    {
        printf("There is no cycle available in the given trade bank\n");
    }
}
