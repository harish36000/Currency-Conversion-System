//This function is used to add a trade bank in the data structure
//this will be added in the tradebank hashtable in the index equal to the string hash of bank name
void add_trade_bank(graph g, char *bank_name)
{
    //computes the string hash of the bank name
    long int bank_hash = compute_hash(g->table_size, bank_name);
    //position will point to the seperate chaining of the banks which have the same hash value
    ptr_trade_bank position = g->list_trade_banks[bank_hash];
    //this while loop will traverse through the whole seperate chaining
    while (position != NULL)
    {
        //checks whether the given bank already exists
        if (strcmp(position->name_trade_bank, bank_name) == 0)
        {
            printf("Trade Bank already exists\n");
            return;
        }
        //traversal of separate chaining
        position = position->next;
    }
    //checks whether there is no bank available earlier with same hash value
    if (g->list_trade_banks[bank_hash] == NULL)
    {
        //updates the check array which stores the filled indices of the hashtable
        //adds the current hashvalue to the check array as the last element
        //as there is no bank stored with this hashvalue earlier
        g->check[g->last_index] = bank_hash;
        //increases the size of the check array as we added an extra element
        g->last_index++;
    }
    //allocation of space to a new trade bank to insert it
    ptr_trade_bank new = (ptr_trade_bank)malloc(sizeof(trade_bank));
    assert(new != NULL); // throws an error if memory not available
    //initalizes the hashtable size of the currencies in this bank
    new->table_size = hash_table_size;
    //nvertices denotes to number of currencies added
    //as there is no currency in the bank initially it's value is zero
    new->nvertices = 0;
    //sets the name of the bank in the tradebank struct to the given bankname
    strcpy(new->name_trade_bank, bank_name);
    //allocates memory to the hashtable of the currencies
    new->list_currency = (ptr_currency *)malloc(hash_table_size * sizeof(ptr_currency));
    assert(new->list_currency != NULL); // throws an error if memory not available
    //allocates memory to the check array which stores the filled indices of the currency hashtable in this bank
    new->check = (length *)calloc(new->table_size, sizeof(length));
    assert(new->check != NULL); // throws an error if memory not available
    //initiates the number of indices filled in the check array(last_index) to zero
    new->last_index = 0;
    //makes the next pointer of this bank to point to the bank where hashtable with same hashvalue points to
    new->next = g->list_trade_banks[bank_hash];
    //makes the hashvalue index in the hashtable to point to this new bank
    //this will insert this new bank at the start of the separate chaining
    g->list_trade_banks[bank_hash] = new;
}
