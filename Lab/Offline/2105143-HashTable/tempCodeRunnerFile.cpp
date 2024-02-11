for (int i = 0; i < size; ++i)
        {
            Node *cur = table[i];
            while (cur != NULL)
            {
                Node *next = cur->next;
                delete cur;
                cur = next;
            }
        }