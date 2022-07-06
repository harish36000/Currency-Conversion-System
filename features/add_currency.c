void add_currency(graph g, char *bank_name, char *currency_name)
{
    long int bank_name_hash = compute_hash(g->table_size, bank_name);

    //Checking if Trade Bank named "bank_name" exists
    if (g->list_trade_banks[bank_name_hash] != NULL) //Trade Bank exists
    {
        //Creating New Currency Node
        ptr_currency new_currency = malloc(sizeof(currency));
        assert(new_currency != NULL); // throws an error if memory not available
        strcpy(new_currency->id, currency_name);
        new_currency->adj_list = NULL;
        new_currency->next = NULL;
        new_currency->dest_wt = 0;

        //Iterating through all trade banks with Hash Value: bank_name_hash to find the trade bank with Name: "bank_name"
        ptr_trade_bank read_trade_bank = g->list_trade_banks[bank_name_hash];
        while (read_trade_bank)
        {
            if (strcmp(read_trade_bank->name_trade_bank, bank_name) == 0)
                break;
            read_trade_bank = read_trade_bank->next;
        }
        if (read_trade_bank == NULL)
        {
            printf("Trade Bank not found\n");
            return;
        }

        //Iterating through all currencies with Hash Value: currency_name_hash to check if currency with Name: "currency_name" already exists
        long int currency_name_hash = compute_hash(read_trade_bank->table_size, currency_name);
        ptr_currency read_currency = read_trade_bank->list_currency[currency_name_hash];
        while (read_currency != NULL)
        {
            if (strcmp(read_currency->id, currency_name) == 0)
            {
                printf("Currency already exists\n");
                return;
            }
            read_currency = read_currency->next;
        }

        if (read_trade_bank->list_currency[currency_name_hash] == NULL)
        {
            read_trade_bank->check[read_trade_bank->last_index] = currency_name_hash;
            read_trade_bank->last_index++;
        }
        new_currency->vertex_id = read_trade_bank->nvertices; // assigning vertex id to the new currency
        read_trade_bank->nvertices++;                         // increments the number of currencies in the trade bank

        //Adding New Currency (to the front of the list) by separate chaining
        new_currency->next = read_trade_bank->list_currency[currency_name_hash];
        read_trade_bank->list_currency[currency_name_hash] = new_currency;
    }
    else
        printf("Trade Bank Not Found\n");
}
