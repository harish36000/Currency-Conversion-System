// This function finds the trade bank with the given name and returns a pointer to it
ptr_trade_bank find_trade_bank(graph g, char *bank_name)
{
    long int hash_tb = compute_hash(g->table_size, bank_name); // compute the hash value of the bank name using the compute_hash() function
    ptr_trade_bank tb = NULL;
    ptr_trade_bank temp = g->list_trade_banks[hash_tb];

    // It may happen that more than 1 trade banks possess the same hash value, so traverse the separate chaining linked list of the computed
    // hash value whilst comparing the bank names with the specified bank name
    while (temp != NULL)
    {
        if (strcmp(temp->name_trade_bank, bank_name) == 0)
        {
            tb = temp;
            break;
        }
        else
        {
            temp = temp->next;
        }
    }
    // if the trade bank is not found even after traversing the entire separate chaining linked list, print an error message
    if (temp == NULL)
    {
        printf("Trade Bank not found\n");
        return NULL;
    }
    return tb;
}
