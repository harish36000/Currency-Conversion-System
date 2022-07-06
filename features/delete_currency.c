void delete_currency(graph g, char *bank_name, char *currency_name)
{
    int found = 0;
    long int bank_name_hash = compute_hash(g->table_size, bank_name);

    //Iterating through all trade banks with Hash Value: bank_name_hash to check if trade bank with Name: "bank_name" exists
    ptr_trade_bank read_trade_bank = g->list_trade_banks[bank_name_hash];
    while (read_trade_bank)
    {
        if (strcmp(read_trade_bank->name_trade_bank, bank_name) == 0)
        {
            found = 1;
            break;
        }
        read_trade_bank = read_trade_bank->next;
    }
    if (found) //Trade bank with Name: "bank_name" exists
    {
        found = 0;
        long int currency_name_hash = compute_hash(g->table_size, currency_name);

        //Iterating through all currencies with Hash Value: currency_name_hash to check if currency with Name: "currency_name" exists
        ptr_currency read_currency = read_trade_bank->list_currency[currency_name_hash];
        ptr_currency prev_read_currency = read_currency;
        if (read_currency)
        {
            while (read_currency)
            {
                if (strcmp(read_currency->id, currency_name) == 0)
                {
                    found = 1;
                    break;
                }
                prev_read_currency = read_currency;
                read_currency = read_currency->next;
            }
        }
        if (found) //Currency with Name: "currency_name" exists
        {
            if (read_currency->adj_list != NULL)
            {
                //Step 1: Iterate through check array
                //        For every currency that can be converted to "currency_name", remove "currency_name" from their adjacency list
                for (long int i = 0; i < read_trade_bank->last_index; i++)
                {
                    //Go to currency list of index stored in check
                    long int hash_val = read_trade_bank->check[i];
                    ptr_currency check_currency = read_trade_bank->list_currency[hash_val];

                    while (check_currency)
                    {
                        //Check if "currency_name" present in their adjacency list
                        ptr_currency temp = check_currency->adj_list;
                        ptr_currency temp_prev = check_currency;
                        while (temp)
                        {
                            if (strcmp(temp->id, currency_name) == 0)
                            {
                                temp_prev->adj_list = temp->adj_list;
                                free(temp);
                                break;
                            }
                            temp_prev = temp;
                            temp = temp->adj_list;
                        }
                        check_currency = check_currency->next;
                    }
                }

                //Step 2: Delete all currencies connected to "currency_name"
                ptr_currency del_ptr = read_currency->adj_list;
                read_currency->adj_list = NULL;
                while (del_ptr)
                {
                    ptr_currency temp_del_ptr = del_ptr;
                    del_ptr = del_ptr->adj_list;
                    free(temp_del_ptr);
                }
            }
            if (read_currency == prev_read_currency)
                read_trade_bank->list_currency[currency_name_hash] = read_currency->next;
            else
                prev_read_currency->next = read_currency->next;

            free(read_currency);
            read_currency = NULL;
        }
        else
        {
            printf("Currency Not Found\n");
            return;
        }
    }
    else
    {
        printf("Trade Bank Not Found\n");
        return;
    }
}
