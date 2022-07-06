// This function deletes the conversion between 2 currencies in a specified trade bank if it exists
void delete_conversion(graph g, char *bank_name, char *currency_name_s, char *currency_name_d)
{
    long int hash_tb = compute_hash(g->table_size, bank_name); // find the required trade bank
    ptr_trade_bank tb = NULL, temp = g->list_trade_banks[hash_tb];

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
    if (temp == NULL)
    {
        // Print an error message if the trade bank is not found
        printf("Trade Bank not found\n");
        return;
    }

    long int hash_curr = compute_hash(tb->table_size, currency_name_s); // find the source currency
    ptr_currency curr = NULL;
    ptr_currency temp2 = tb->list_currency[hash_curr];

    while (temp2 != NULL)
    {
        if (strcmp(temp2->id, currency_name_s) == 0)
        {
            curr = temp2;
            break;
        }
        else
        {
            temp2 = temp2->next;
        }
    }
    if (temp2 == NULL)
    {
        // print an error message if the source currency is not found
        printf("Source Currency not found\n");
        return;
    }

    ptr_currency previous = curr;
    ptr_currency present = curr->adj_list;

    // Traverse through the adjacency list of the source currency and compare the currency names with the required destination currency name
    while (present != NULL)
    {
        // if the destination currency is found, delete the conversion (hence, remove that node from the adjacency list)
        if (strcmp(present->id, currency_name_d) == 0)
        {
            break;
        }
        previous = present;
        present = present->adj_list;
    }
    // if after traversing the entire list, you do not find the destination currency node, print an error message
    if (present == NULL)
    {
        printf("Conversion doesn't exist\n");
        return;
    }
    previous->adj_list = present->adj_list;
    free(present);
}
