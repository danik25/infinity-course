/****************************************************************
*                <<<<<<<< DHCP >>>>>>>>                         *
* Related files: dhcp.c, dhcp_test.c                            *
* #Version: V 1.3                                              *
* Writer: Dani Benjamim                                         *   
* Reviewer: Ayala Rosel                                         *
* Last update: 18/06/19                                         *
****************************************************************/ 
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <math.h> /* pow */
#include <string.h> /* memcpy */

#include "dhcp.h"
#include "bit_array.h"
#include "dani_utilities.h"

#define BYTE_SIZE 8

enum CHILDREN {LEFT, RIGHT};
enum AVAILABLE {FREE, TAKEN};

enum ADR_STATUS {NOT_AVAILABLE = 2, WRONG_NETWORK = 3};

typedef struct DHCP_NODE
{
    char availability;
    struct DHCP_NODE *children[2];
    struct DHCP_NODE* parent;
}dhcp_node_t;

struct DHCP
{
	unsigned char subnet[IP_BYTES_SIZE];
    size_t bytes_num;
    dhcp_node_t *root;
    size_t count_free;
};


static dhcp_node_t * CreateNode(void);
static void FillNetWorkAndInput(unsigned char array[BYTE_SIZE], 
                    const unsigned char subnet[BYTE_SIZE], size_t bytes_num, 
                    unsigned char input);
static int CheckSubnet(unsigned char subnet[IP_BYTES_SIZE], 
                    unsigned char to_check[IP_BYTES_SIZE]);
static int IsValid(DHCP_t* dhcp, unsigned char to_check[IP_BYTES_SIZE]);
static int IsSame(unsigned char array1[], unsigned char array2[]);

/* conversion functions */
static unsigned long ConvertFromArray(unsigned char array[IP_BYTES_SIZE]);
static void ConvertToArray(unsigned long number, 
                    unsigned char array[IP_BYTES_SIZE]);

/* alloc assistance functions */
static unsigned long ChangeDesired(unsigned long desired, int index);
static int IsBothChildrenTaken(dhcp_node_t *node);

/* recursion functions */
static int RecAlloc(dhcp_node_t *runner, unsigned long desired, 
                    unsigned long* alloced, int index);
static dhcp_node_t * RecDestroy(dhcp_node_t * node);
static int RecFree(dhcp_node_t *runner, unsigned long ip, int index);

DHCP_t *DHCPCreate(const unsigned char subnet[IP_BYTES_SIZE], size_t bytes_num)
{
    DHCP_t * handle = NULL;
 
    unsigned char zero[IP_BYTES_SIZE] = {0};
    unsigned char max[IP_BYTES_SIZE] = {0};
    unsigned char max_minus_one[IP_BYTES_SIZE] = {0};

    unsigned char tmp[IP_BYTES_SIZE] = {0};

    FillNetWorkAndInput(zero, subnet, bytes_num, 0);
    FillNetWorkAndInput(max, subnet, bytes_num, 255);
    FillNetWorkAndInput(max_minus_one, subnet, bytes_num, 255);
    max_minus_one[IP_BYTES_SIZE - 1] = 254;

    assert(subnet);

    handle = (DHCP_t*)malloc(sizeof(DHCP_t));

    if(NULL == handle)
    {
        return (NULL);
    } 

    FillNetWorkAndInput(handle->subnet, subnet, bytes_num, 0);
    handle->bytes_num = bytes_num;
    handle->root = CreateNode();
    handle->count_free = pow(2, (IP_BYTES_SIZE - bytes_num) * BYTE_SIZE);

    if(FAIL == DHCPAllocIP(handle, zero, tmp))
    {
        return (NULL);
    }

    if(FAIL == DHCPAllocIP(handle, max, tmp))
    {
        return (NULL);
    }

    if(FAIL == DHCPAllocIP(handle, max_minus_one, tmp))
    {
        return (NULL);
    }

    return(handle);
}

void DHCPDestroy(DHCP_t *dhcp)
{
    assert(dhcp);

    RecDestroy(dhcp->root);

    free(dhcp);
    dhcp = NULL;   
}

int DHCPAllocIP(DHCP_t* dhcp, const unsigned char desired_ip[IP_BYTES_SIZE],
                 unsigned char alloced_ip[IP_BYTES_SIZE])
{
    int status = 0;
    size_t index = 0;
    unsigned long alloced_tmp = 0;
    unsigned long desired_tmp = 0;
    unsigned char desired_null[IP_BYTES_SIZE] = {0};

    assert(dhcp);
    assert(alloced_ip);

    if(NULL == desired_ip)
    {
        FillNetWorkAndInput(desired_null, dhcp->subnet, dhcp->bytes_num, 0);
        desired_tmp = ConvertFromArray(desired_null);
    }
    else
    {
        desired_tmp = ConvertFromArray((unsigned char*)desired_ip);

        /* checking if the subnet is correct */
        if(FAIL == CheckSubnet(dhcp->subnet, (unsigned char*)desired_ip))
        {
            return (WRONG_NETWORK);
        }
    } 

    /* filling the alloced with the network information */
    FillNetWorkAndInput(alloced_ip, dhcp->subnet, dhcp->bytes_num, 0);

    index = (IP_BYTES_SIZE - dhcp->bytes_num) * BYTE_SIZE - 1;
    alloced_tmp = ConvertFromArray(alloced_ip);  

    status = RecAlloc(dhcp->root, desired_tmp, &alloced_tmp, index);
    if(SUCCESS == status)
    {
        --dhcp->count_free;
        ConvertToArray(alloced_tmp, alloced_ip);
    }
    
    return (status);
}

int DHCPFreeIP(DHCP_t* dhcp, const unsigned char ip[IP_BYTES_SIZE])
{
    size_t index = 0;
    int status = 0;
    unsigned long ip_tmp = 0;

    assert(dhcp);
    assert(ip);

    ip_tmp = ConvertFromArray((unsigned char*)ip);

    if(!IsValid(dhcp, (unsigned char*)ip))
    {
        return (FAIL);
    }

    /* checking if the subnet is correct */
    if(FAIL == CheckSubnet(dhcp->subnet, (unsigned char*)ip)) 
    {
        return (WRONG_NETWORK);
    }

    index = (IP_BYTES_SIZE - dhcp->bytes_num) * BYTE_SIZE - 1;
    status = RecFree(dhcp->root, ip_tmp, index);
    if(SUCCESS == status)
    {
        ++dhcp->count_free;
    }
    return (status);
}

size_t DHCPCountFree(const DHCP_t *dhcp)
{
    assert(dhcp);

    return (dhcp->count_free);
}

/******************************************************************************/

static int CheckSubnet(unsigned char subnet[IP_BYTES_SIZE], 
                                unsigned char to_check[IP_BYTES_SIZE])
{   
    unsigned long converted = ConvertFromArray(subnet);
    if((converted & ConvertFromArray(to_check)) != converted) 
    {
        return (FAIL);
    }
    return (SUCCESS);
}

static int IsValid(DHCP_t* dhcp, unsigned char to_check[IP_BYTES_SIZE])
{
    unsigned char zero[IP_BYTES_SIZE] = {0};
    unsigned char max[IP_BYTES_SIZE] = {0};
    unsigned char max_minus_one[IP_BYTES_SIZE] = {0};

    FillNetWorkAndInput(zero, dhcp->subnet, dhcp->bytes_num, 0);
    FillNetWorkAndInput(max, dhcp->subnet, dhcp->bytes_num, 255);
    FillNetWorkAndInput(max_minus_one, dhcp->subnet, dhcp->bytes_num, 255);
    max_minus_one[IP_BYTES_SIZE - 1] = 254;

    if(IsSame(to_check, zero) || IsSame(to_check, max) || 
                                    IsSame(to_check, max_minus_one))
    {
        return (0);
    }
    return (1);
}

static int IsSame(unsigned char array1[], unsigned char array2[])
{
    size_t i = 0;
    for(i = 0; i < IP_BYTES_SIZE; ++i)
    {
        if(array1[i] != array2[i])
        {
            return (0);
        }
    }
    return (1);
}

static void FillNetWorkAndInput(unsigned char array[BYTE_SIZE], 
        const unsigned char subnet[BYTE_SIZE], size_t bytes_num, unsigned char input)
{
    size_t i = 0;
    for (i = 0; i < bytes_num; ++i)
    {
        array[i] = subnet[i];
    }

    for (i = bytes_num; i < IP_BYTES_SIZE; ++i)
    {
        array[i] = input;
    }
}

static dhcp_node_t * CreateNode()
{
    dhcp_node_t * node = (dhcp_node_t*)malloc(sizeof(dhcp_node_t));

    if(NULL == node)
    {
        return (NULL);
    }

    node->children[LEFT] = NULL;
    node->children[RIGHT] = NULL;
    node->availability = FREE;

    return (node);
}

/*~~~~~~~~~~~~~~~~~~~recursion assistance functions~~~~~~~~~~~~~~~~~~~*/

static int RecAlloc(dhcp_node_t *runner, unsigned long desired, 
                                unsigned long* alloced, int index)
{
    int status = NOT_AVAILABLE; 
    dhcp_node_t *child = NULL;

    /* if the desired direction is available */
    if(runner->availability == TAKEN)
    {
        return (NOT_AVAILABLE);
    }

    if(-1 == index)
    {
        runner->availability = TAKEN;        
        return (SUCCESS);
    }

    
    *alloced = SetBit(*alloced, index, IsOn(desired, index));

    child = runner->children[IsOn(desired, index)];

    /* if the node doesn't exists */
    if(NULL == child)
    {
        child = CreateNode();
        if(NULL == child)
        {
            return (FAIL);
        }

        runner->children[IsOn(desired, index)] = child;
    }

    status = RecAlloc(child, desired, alloced, index - 1);

    /* find the bigger path if the desired one does not exists */
    if(IsOff(desired, index) && status == NOT_AVAILABLE)
    {
        desired = ChangeDesired(desired, index);
        status = RecAlloc(runner, desired, alloced, index);
    }

    /* if the availability of the parent needs to be 
                                    changed after the allocation */
    else if(IsBothChildrenTaken(runner))
    {
        runner->availability = TAKEN;
    }

    return (status);
}

static int RecFree(dhcp_node_t *runner, unsigned long ip, int index)
{
    int status = FAIL; 
    dhcp_node_t *child = NULL;

    if(-1 == index)
    {
        if(runner->availability == FREE)
        {
            return (FAIL);
        }
        runner->availability = FREE;        
        return (SUCCESS);
    }

    child = runner->children[IsOn(ip, index)];

    /* if the node doesn't exists */
    if(NULL == child)
    {
        return (FAIL);
    }

    status = RecFree(child, ip, --index);

    /* if the availability of the parent needs to be 
                                    changed after the allocation */
    if(!IsBothChildrenTaken(runner))
    {
        runner->availability = FREE;
    }

    return (status);
}

static dhcp_node_t * RecDestroy(dhcp_node_t * node)
{
    if(NULL != node)
    {
        RecDestroy(node->children[LEFT]);    
        RecDestroy(node->children[RIGHT]);

        free(node);
    }

    return (node);   
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
                /* assistance for alloc */
static unsigned long ChangeDesired(unsigned long desired, int index)
{
    desired = SetOn(desired, index);
    --index;

    while(index > -1)
    {
        desired = SetOff(desired, index);
        --index;
    }

    return (desired);
}

static int IsBothChildrenTaken(dhcp_node_t *node)
{
    if(node->children[LEFT] == NULL || 
                    node->children[RIGHT] == NULL)
    {
        return (0);
    }
    return (node->children[LEFT]->availability == TAKEN && 
                    node->children[RIGHT]->availability == TAKEN);
}

/*===========================conversion functions===========================*/

static unsigned long ConvertFromArray(unsigned char array[IP_BYTES_SIZE])
{
    int i = 0;
    unsigned long ans = 0;

    for(i = 0; i < IP_BYTES_SIZE; ++i)
    {
        ans <<= BYTE_SIZE;
        ans += (unsigned long) array[i];
    }

    return (ans);
}

static void ConvertToArray(unsigned long number, 
                    unsigned char array[IP_BYTES_SIZE])
{
    int i = 0;

    for(i = IP_BYTES_SIZE -1; i >= 0; --i)
    {
        array[i] = (char)number;
        number >>= BYTE_SIZE;
    }
}

