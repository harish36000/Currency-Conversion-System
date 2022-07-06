//this function is used to delete a whole tradebank
//it also frees memory allocated to all currency nodes in the trade bank

void delete_trade_bank(graph g, char *bank_name)
{
    //compurtes the stringhash of bank name
    length hash_value = compute_hash(g->table_size, bank_name);
    //checks whether there is a separate chaining for the same hashvalue
    if (g->list_trade_banks[hash_value] == NULL)
    {

        printf("THERE IS NO TRADEBANK WITH NAME %s\n", bank_name);
        return;
    }

    else
    {
        //Trade_bank points to the seperate chaining in the hashvalue index
        ptr_trade_bank Trade_bank = g->list_trade_banks[hash_value];
        //prev_bank stores the bank stored at the front of our bank
        ptr_trade_bank prev_bank = Trade_bank;

        //traverses through the separate chaining
        while (Trade_bank != NULL)
        {
            //checks whether Trade_bank pointer contains the required bank
            if (strcmp(Trade_bank->name_trade_bank, bank_name) == 0)
            {
                //breaks when Trade_bank points to the desired bank
                //and prev_bank will point to the previous bank in the separate chaining
                break;
            }
            //updates the previous bank
            prev_bank = Trade_bank;
            //traversal through separate chaining
            Trade_bank = Trade_bank->next;
        }
        //checks if given tradebank does not exist
        if (Trade_bank == NULL)
        {

            printf("THERE IS NO TRADEBANK WITH NAME %s\n", bank_name);
            return;
        }
        //traverses through all the filled indices of the currency hashtable
        for (int i = 0; i < Trade_bank->last_index; i++)
        {
            //current points to the separate chain in the check[i] index of hashtable
            ptr_currency current = Trade_bank->list_currency[Trade_bank->check[i]];
            ptr_currency temp_next = current;
            //traverses through the separate chaining of currency hashtable
            while (temp_next != NULL)
            {
                //temp_adj points to adjacency list of the temp_next currency node
                ptr_currency temp_adj = temp_next->adj_list;
                //traverses through the adjacency list of temp_next currency node
                while (temp_adj != NULL)
                {
                    //stores the present node in the del_adj
                    ptr_currency del_adj = temp_adj;
                    //traversal through the adjacency list
                    temp_adj = temp_adj->adj_list;
                    //frees the memory allocated to a node in the adjacency list
                    free(del_adj);
                }
                //stores the present currency in del_next
                ptr_currency del_next = temp_next;
                //travesal through separate chaining of the currency hashtable
                temp_next = temp_next->next;
                //frees a currency node in the separate chaining
                free(del_next);
            }
        }
        //check if prev_bank and Trade_bank points to same tradebank node
        //this happens when the required tradebank is at the start of the separate chaining
        if (prev_bank == Trade_bank)
        {
            //making the hashtable point to the next bank in the separate chaining
            //as we are deleting the first tradebank node in the separate chaining
            g->list_trade_banks[hash_value] = prev_bank->next;
        }
        else
        {
            //making the prevbank's next pointer to the bank which is next to the given trade bank
            //i.e, removing the given tradebank in the separate chaining
            prev_bank->next = Trade_bank->next;
        }
        //frees the memory allocated to given trade bank
        free(Trade_bank);
        Trade_bank = NULL;
    }
    return;
}

