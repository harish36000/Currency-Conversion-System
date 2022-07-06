// This function finds the currency with the specified name and returns a pointer to it
ptr_currency find_currency(graph g, ptr_trade_bank tb, char *currency_name)
{
    long int hash_curr = compute_hash(tb->table_size, currency_name); // compute the hash value of the given currency name using the
                                                                      // compute_hash() function
    ptr_currency curr = NULL;
    ptr_currency temp = tb->list_currency[hash_curr];

    // It may happen that more than 1 currencies possess the same hash value, so traverse the separate chaining linked list of the computed
    // hash value whilst comparing the currency names with the specified currency name
    while (temp != NULL)
    {
        if (strcmp(temp->id, currency_name) == 0)
        {
            curr = temp;
            break;
        }
        else
        {
            temp = temp->next;
        }
    }
    // if the currency is not found even after traversing the entire separate chaining linked list, return NULL
    // (this block can also be used to print an error message, but that prints unnecessary lines in the output, so we have commented the printf)
    if (temp == NULL)
    {
        // printf("Currency not found\n");
        return NULL;
    }
    return curr;
}
