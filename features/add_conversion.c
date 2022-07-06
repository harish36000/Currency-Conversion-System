// This function adds a weighted edge between 2 specified currencies in the specified trade bank
void add_conversion(graph g, char *bank_name, char *currency_name_s, char *currency_name_d, weight wt)
{
    long int hash_tb = compute_hash(g->table_size, bank_name); // find the required trade bank
    ptr_trade_bank tb = NULL;
    ptr_trade_bank temp = g->list_trade_banks[hash_tb];

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
        // Print an error message if the specified trade bank is not found
        printf("Trade Bank not found\n");
        return;
    }

    long int hash_curr = compute_hash(tb->table_size, currency_name_s); // find the source currency in the trade bank
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
        // print an error message if the source currency is not found in the trade bank
        printf("Source Currency not found\n");
        return;
    }

    long int hash_curr_2 = compute_hash(tb->table_size, currency_name_d); // find the destination currency
    ptr_currency curr2 = NULL;
    ptr_currency temp3 = tb->list_currency[hash_curr_2];

    while (temp3 != NULL)
    {
        if (strcmp(temp3->id, currency_name_d) == 0)
        {
            curr2 = temp3;
            break;
        }
        else
        {
            temp3 = temp3->next;
        }
    }
    if (temp3 == NULL)
    {
        // print an error message if the destination currency is not found in the trade bank
        printf("Destination Currency not found\n");
        return;
    }
    ptr_currency position = temp2->adj_list;
    // traverse through the adjacency list of the source currency to check if there already exists a conversion between the
    // specified source and destination currencies. If it already exists, update the cost of the conversion to the new value
    while (position != NULL)
    {
        if (strcmp(position->id, currency_name_d) == 0)
        {
            position->dest_wt = wt;
            return;
        }
        position = position->adj_list;
    }

    // if the conversion does not exist already, then create a new currency node and add it in the adjacency list of the source
    // currency with the appropriate conversion cost
    ptr_currency dest_curr = (ptr_currency)malloc(sizeof(currency));
    assert(dest_curr != NULL); // throws an error if memory not available

    dest_curr->adj_list = curr->adj_list;
    dest_curr->next = NULL;
    dest_curr->vertex_id = temp3->vertex_id;
    strcpy(dest_curr->id, currency_name_d);
    dest_curr->dest_wt = wt;
    curr->adj_list = dest_curr;
}
