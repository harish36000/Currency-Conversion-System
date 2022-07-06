// This function prints the nodes that constitue a cycle in the trade bank
void print_stack(char stack[][50], length nfilled, length start)
{
    printf("The cycle is:");
    for (int i = start; i < nfilled; i++)
    {
        printf(" %s", stack[i]);
    }
    printf("\n");
}