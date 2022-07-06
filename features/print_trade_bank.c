//this prints all the currencies and the conversions present in the given bank
void print_trade_bank(graph g, char *bank)
{
    //computes the stringhash of the bank name
    long int bank_hash = compute_hash(g->table_size, bank);
    //making current point to the separate chaining of the bank with same hashvalue
    ptr_trade_bank current = g->list_trade_banks[bank_hash];
    //while loop traverses through the separate chaining
    while (current != NULL)
    {
        //checks whether the bank exist in the separate chaining
        if (strcmp(current->name_trade_bank, bank) == 0)
        {
            //breaks from the while loop when we finally traversed to the given bank
            //current will point to our desired bank struct
            break;
        }
        //traversal of separate chaining
        current = current->next;
    }
    //checks whether the bank exists
    if (current == NULL)
    {

        printf("the given trade bank doesn't exist.\n");
        return;
    }
    //prints tradebank name
    printf("Trade Bank : %s\n\n", current->name_trade_bank);

    //for loop traverses through every filled index in the currency hashtable of the given bank
    for (int i = 0; i < current->last_index; i++)
    {
        //presentcurrency points to the separate chaining of the index in the hashtable which is equal to check[i] in the bank struct
        ptr_currency presentcurrency = current->list_currency[current->check[i]];
        //traversal through the separate chaining presentcurrency
        while (presentcurrency != NULL)
        {
            //prints a currency name
            printf("%s\n", presentcurrency->id);
            //edge points to a linked list of all outgoing conversions from presentcurrency node
            ptr_currency edge = presentcurrency->adj_list;
            //while loop traverses through the linkedlist of outgoing edges
            while (edge != NULL)
            {
                //prints the outgoing conversion with destination currency name and conversion rate
                printf("\t\tTo currency %s with conversion rate %ld.\n", edge->id, edge->dest_wt);
                //traversal of the linkedlist
                edge = edge->adj_list;
            }
            //traversal of separate chaining of currency hashtable
            presentcurrency = presentcurrency->next;
        }
    }
}
