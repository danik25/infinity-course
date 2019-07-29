#ifndef  _DHCP_H_  
#define  _DHCP_H_  


/****************************************************************
*                <<<<<<<< DHCP >>>>>>>>                         *
* Related files: dhcp.c, dhcp_test.c                            *
* #Version: V 1.3                                               *
* Writer: Dani Benjamim                                         *   
* Reviewer: Ayala Rosel                                                 *
* Last update: 18/06/19                                         *
****************************************************************/ 


#include <stddef.h> /* size_t */

#define IP_BYTES_SIZE 4

typedef struct DHCP DHCP_t;



/* API DESCRIPTION
 * A program for allocating ip adresses.
 * three Adresses are pre occupied and cannot be allocated:
 * X0...00 
 * X1...10
 * X1...11
 * where X is the network part of the ip address.        
 *
*/  



/* Description: Create a new DHCP ip manager
 *
 * Params: bytes_num - number of bytes of the network address
 *         subnet    - network IP 
 *        
 *               
 * Return Value: pointer to the new DHCP
 *       
 *        example
 *      ------------
 *      for bytes_num = 3
 *      and subnet = 192.168.142.0   
 *      the  program will allocate about 256 addresses 
 *      from 192.168.142.0 to 192.168.142.255 
 * 
 */
 DHCP_t *DHCPCreate(const unsigned char subnet[IP_BYTES_SIZE], size_t bytes_num);



 /* Description: free all allocated space and destroy the DHCP instance.
 *
 * Params: dhcp - pointer to the DHCP   
 *        
*/                 
 void DHCPDestroy(DHCP_t *dhcp);




/* Description: allocate an ip address. 
 *
 * Params: dhcp - pointer to the DHCP
 *         desired_ip - ip address the user desires in IP_BYTES_SIZE char array.
 *                      if the desired_ip is NULL then the minimal ip address
 *                      available will be allocated 
 *         alloced_ip - IP_BYTES_SIZE char array which is a container to the
 *                      actuall allocated ip. the allocated ip is guarantied
 *                      to be the minimal address available that is grater then 
 *                      the desired one, if no such address exists an error code 
 *                      (2) will be returned.   
 *        
 * Return Value: STATUS -  0 - SUCCESS, 
 *                         1 - allocation memory FAIL, 
 *                         2 - no address available,
 *                         3 - the desired ip is not compatible 
 *                              with the network address as specified 
 *                              in subnet argument of create   
 *         
 */
 int DHCPAllocIP(DHCP_t* dhcp,
                 const unsigned char desired_ip[IP_BYTES_SIZE],
                 unsigned char alloced_ip[IP_BYTES_SIZE]); 



/* Description: free an ip address.
 *
 * Params: dhcp - pointer to the DHCP
 *         ip - IP_BYTES_SIZE bytes array containing the address to be freed.
 *        
 *        
 * Return Value: STATUS - 0 - SUCCESS  , 1 - FAIL
 *         
*/
int DHCPFreeIP(DHCP_t* dhcp, const unsigned char ip[IP_BYTES_SIZE]);



/* Description: count the number of available ip addresses.
 *
 * Params: dhcp - pointer to the DHCP
 *        
 *        
 * Return Value: the number of available address
 *         
*/
size_t DHCPCountFree(const DHCP_t *dhcp);





#endif /* _DHCP_H_ */
