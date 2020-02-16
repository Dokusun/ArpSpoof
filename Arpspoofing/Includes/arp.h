/*
** EPITECH PROJECT, 2018
** {Project name}
** File description:
** {file name}
*/

#ifndef NWP_MYARPSPOOF_2018_ARP_H
#define NWP_MYARPSPOOF_2018_ARP_H

#include <stdlib.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <linux/if_ether.h>
#include <stdio.h>
#include <linux/if.h>
#include <string.h>
#include <netinet/if_ether.h>
#include <sys/ioctl.h>
#include <zconf.h>
#include <errno.h>
#include <linux/ip.h>
#include <stdbool.h>

#define IPV4_LENGTH 4
#define HWADDR_len 6

typedef struct arp_s {
    uint32_t srcip;
    char *ifname;
    char mac[6];
    uint32_t destip;
    int sd;
    char victim_mac[6];
} arp_t;

struct hdr {
    struct ether_header ethhdr;
    struct ether_arp etherarphdr;
};

struct arp_header {
    unsigned short hardware_type;
    unsigned short protocol_type;
    unsigned char hardware_len;
    unsigned char protocol_len;
    unsigned short opcode;
    unsigned char sender_mac[ETH_ALEN];
    unsigned char sender_ip[IPV4_LENGTH];
    unsigned char target_mac[ETH_ALEN];
    unsigned char target_ip[IPV4_LENGTH];
};

void print_mac(const struct ether_addr *addr);
void print_hex(const void *data, size_t n);
struct hdr *build_request(const struct in_addr *src_ip,
    const struct ether_addr *src,
    const struct in_addr *dest_ip,
    const struct ether_addr *dest);
struct hdr *first_packet(arp_t *info);
void mac_eth0(char ret[6], const char *ifname);
struct hdr *receive();
arp_t *getinfo(char **av);
void convert_str_to_bytes(arp_t *info, char *str);
void print_broadcast(char **av);
void print_spoof(char **av);
void launch_attack(char **av);
void create_packet(struct hdr *hd, arp_t *info);
arp_t *basic_init(char **av);

#define CHECK_NULL(code) if (code == NULL) exit(84);
#define CHECK_ERR(code) if (code == -1) exit(84);
#define CHECK_COND(code, cond) if (code cond) exit(84);
#define IS_NB(c) (c <= '9' && c >= '0')
#define HWADDR_len 6

int parse_argv(int ac, char **av);

#endif //NWP_MYARPSPOOF_2018_ARP_H
