/* 运行时间：3ms 占用内存：344KB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LL_NODE_LEN            (1000)
#define MAX_INPUT_LL_NODE_VAL            (10000)
#define MIN_INPUT_LL_NODE_VAL            (0)
#define MAX_INPUT_STR_LEN                (6 * MAX_INPUT_LL_NODE_VAL)

// Link list node define
typedef struct ll_node{
    int node_value;
    struct ll_node *next;
}Node;

int check_if_node_val_in_range(int node_val)
{
    int ret = 0;
    
    if(node_val >= MIN_INPUT_LL_NODE_VAL && node_val <= MAX_INPUT_LL_NODE_VAL)
    {
        ret = 1;
    }
    
    return ret;
}

int check_char_range(char ch, char min, char max)
{
    int ret = 0;
    
    if(ch >= min && ch <= max)
    {
        ret = 1;
    }
    
    return ret;
}

int check_char_is_digi(char ch)
{
    return check_char_range(ch, '0', '9');
}

int check_char_is_space(char ch)
{
    return check_char_range(ch, ' ', ' ');
}

int check_if_only_contains_digi_and_space(char *str)
{
    int ret = 1;
    int index = 0;
    char tmp_ch;
    
    if(NULL == str)
    {
        // input is null, return ret
        ret = 0;
        return ret;
    }
    
    tmp_ch = str[index];
    while(tmp_ch != 0)
    {
        if(!check_char_is_digi(tmp_ch) 
           && !check_char_is_space(tmp_ch))
        {
            ret = 0;
            break;
        }
        index ++;
        tmp_ch = str[index];
    }
    
    return ret;
}

int insert_new_node_after_given_node_val(Node *node, int new_node_val,
                                        int given_node_val)
{
    int ret = 1;
    int node_found = 0;
    Node *tmp_node;
    Node *located_node;
    Node *insert_node;
    
    if(node == NULL)
    {
        ret = 0;
        return ret;
    }
    
    tmp_node = node;
    while(tmp_node != NULL)
    {
        if(given_node_val == tmp_node->node_value)
        {
            located_node = tmp_node;
            node_found = 1;
        }
        tmp_node = tmp_node->next;
    }
    
    if(!node_found)
    {
        ret = 0;
        return ret;
    }
    
    insert_node = (Node *)malloc(sizeof(Node));
    insert_node->node_value = new_node_val;
    insert_node->next = located_node->next;
    located_node->next = insert_node;  
    
    return ret;  
}

int delete_nodes_with_given_node_val(Node *node, int given_delete_node_val)
{
    int ret = 1;
    Node *tmp_node;
    Node *cur_node;
    
    if(node == NULL)
    {
        ret = 0;////
        return ret;
    }
    
    while(node->next != NULL)
    {
        cur_node = node;
        if(node->node_value == given_delete_node_val)
        {
            tmp_node = node;
            node = node->next;
            free(tmp_node);
        }
        else if(node->next->node_value == given_delete_node_val)
        {
            tmp_node = node->next;
            cur_node->next = tmp_node->next;
            free(tmp_node);
        }
        node = node->next;
    }
  
    return ret;
}

void print_nodes(Node *node)
{
    Node *tmp_node;
    
    tmp_node = node;
    while(tmp_node != NULL)
    {
        printf("%d", tmp_node->node_value);
        if(tmp_node->next != NULL)
        {
            printf(" ");
        }
        
        tmp_node = tmp_node->next;
    }
}

int free_nodes(Node *node)
{
    int ret = 1;
    Node *tmp_node;
    
    if(node == NULL)
    {
        ret = 0;
        return ret;
    }
    
    while(node != NULL)
    {
        tmp_node = node;
        node = node->next;
        free(tmp_node);
    }
    
    return ret;
}

int main(int argc, char *argv[])
{
    int ret = 0;
    int i = 0;
    int input_node_len = 0;
    int read_node_count = 0;
    int entry_node_val = 0;
    int insert_node_val = 0;
    int insert_after_node_val = 0;
    int required_deleted_node_val = 0;
    char input_str[MAX_INPUT_STR_LEN+2];
    char *tmp;
    Node *node_entry;
    
    
    if(fgets(input_str, MAX_INPUT_STR_LEN + 2, stdin) != NULL)
    {
        input_str[strlen(input_str) - 1] = '\0';
    }
    
    if(!check_if_only_contains_digi_and_space(input_str))
    {
        ret = -1;
        return ret;
    }

    // get input_node_len
    tmp = strtok(input_str, " ");

    if(tmp != NULL)
    {
        input_node_len = atoi(tmp);
    }

    //printf("input_node_len = %d\n", input_node_len);
    
    if(input_node_len < 0 || input_node_len > 1000)
    {
        ret = -1;
        return ret;
    }

    // get entry node value
    if(tmp != NULL)
    {
        tmp = strtok(NULL, " ");
    }
    entry_node_val = atoi(tmp);
    //printf("entry_node_val = %d\n", entry_node_val);
    
    //printf("%d\n", entry_node_val);
    if(!check_if_node_val_in_range(entry_node_val))
    {
        ret = -1;
        return ret;
    }
    
    // Initial entry node
    node_entry = (Node *)malloc(sizeof(Node));
    node_entry->node_value = entry_node_val;
    node_entry->next = NULL;
    read_node_count++;
    
    if(input_node_len > 1)
    {
        while(tmp != NULL)
        {
            tmp = strtok(NULL, " ");
            insert_node_val = atoi(tmp);
            tmp = strtok(NULL, " ");
            insert_after_node_val = atoi(tmp);

            //printf("insert_node_val = %d, insert_after_node_val = %d\n", insert_node_val, insert_after_node_val);
            if(!check_if_node_val_in_range(insert_node_val) || 
               !check_if_node_val_in_range(insert_after_node_val))
            {
                if(NULL != node_entry)
                {
                    free_nodes(node_entry);
                }
                ret = -1;
                return ret;
            }
            
            if(!insert_new_node_after_given_node_val(node_entry, insert_node_val,
                                                insert_after_node_val))
            {
                if(NULL != node_entry)
                {
                    free_nodes(node_entry);
                }
                ret = -1;
                return ret;
            }
            insert_node_val = 0;
            insert_after_node_val = 0;
            read_node_count++;
            if(read_node_count == input_node_len)
            {
                break;
            }
        }
        // print_nodes(node_entry);
        
        // Get the need to deleted node val

        tmp = strtok(NULL, " ");
        required_deleted_node_val = atoi(tmp);
        
        //printf("required_deleted_node_val: %d\n", required_deleted_node_val);
        
        if(!check_if_node_val_in_range(required_deleted_node_val))
        {
            if(NULL != node_entry)
            {
                free_nodes(node_entry);
            }
            ret = -1;
            return ret;
        }
        
        if(!delete_nodes_with_given_node_val(node_entry, 
                                             required_deleted_node_val))
        {
            if(NULL != node_entry)
            {
                free_nodes(node_entry);
            }
            ret = -1;
            return ret;
        }
        
        print_nodes(node_entry);
    }
    else
    {
        // only 1 node exist
        if(tmp != NULL)
        {
            tmp = strtok(NULL, " ");
        }
        required_deleted_node_val = atoi(tmp);
        if(!check_if_node_val_in_range(required_deleted_node_val) 
           || required_deleted_node_val != node_entry->node_value)
        {
            ret = -1;
            return ret;
        }
        
        // Just free the node and end this app
        free_nodes(node_entry);
    }
    
    return ret;
}