// This function prints the currency nodes present in the adjacency list of the given currency in the specified trade bank along
// with the conversion rates
void print_currency(graph g, char *TradeBank_name, char *Currency_name, length table_size)
{

    length hash_value = compute_hash(table_size, TradeBank_name); // find the required trade bank
    if (g->list_trade_banks[hash_value] == NULL)
    {
        // throw an error message if the hash value computed in the last step points to NULL
        printf("THERE IS NO TRADEBANK WITH NAME %s\n", TradeBank_name); 
        return;
    }

    ptr_trade_bank Trade_bank = g->list_trade_banks[hash_value];
    // It may so happen that more than 1 trade banks are stored at the same hash value (since we have used separate chaining), in that case
    // traverse the linked list at the computed hash value whilst comparing the names with the name of the given trade bank
    while (Trade_bank != NULL)
    {

        if (strcmp(Trade_bank->name_trade_bank, TradeBank_name) == 0)
        {
            break;
        }
        Trade_bank = Trade_bank->next;
    }
    if (Trade_bank == NULL)
    {
        // if the linked list ends but the trade bank is not found, print an error message
        printf("THERE IS NO TRADEBANK WITH NAME %s\n", TradeBank_name);
        return;
    }
    length hash_value1 = compute_hash(table_size, Currency_name); // compute the hash value of the required currency node
    ptr_currency Currency = Trade_bank->list_currency[hash_value1];
    if (Currency == NULL)
    {
        // if the hash table cell at the computed hash value points to NULL, then print an error message
        printf("THERE IS NO CURRECNY WITH NAME %s IN THIS TRADEBANK\n", Currency_name);
        return;
    }

    // It may so happen that more than 1 currencies are stored at the same hash value (since we have used separate chaining), in that case
    // traverse the linked list at the computed hash value whilst comparing the names with the name of the given currency 
    while (Currency != NULL)
    {

        if (strcmp(Currency->id, Currency_name) == 0)
        {
            break;
        }
        Currency = Currency->next;
    }
    if (Currency == NULL)
    {
        // if the linked list ends but the currency is not found, print an error message
        printf("THERE IS NO CURRENCY WITH NAME %s IN THIS TRADEBANK\n", TradeBank_name);
        return;
    }

    ptr_currency current = Currency;
    printf("Name of currency is %s\n", current->id);
    // if the currency is found, traverse through its adjacency list and print the currency names and the conversion rates for the currency nodes 
    // present in the adjacency list
    while (current->adj_list != NULL)
    {
        current = current->adj_list;
        printf("%s->%s : Conversion_Rate->%ld\n", Currency->id, current->id, current->dest_wt);
    }

    return;
}
