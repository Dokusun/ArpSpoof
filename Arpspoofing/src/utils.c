/*
** EPITECH PROJECT, 2018
** ARP spoof
** File description:
** utils.c
*/

#include <stdio.h>
#include "arp.h"

void print_mac(const struct ether_addr *addr)
{
    for (size_t i = 0 ; i < 6 ; i++) {
        printf("%02X", ((const unsigned char *)addr->ether_addr_octet)[i]);
        if (i != 5)
            printf(":");
    }
}

void mac_eth0(char ret[6], const char *ifname)
{
    int s;
    struct ifreq ifret;

    s = socket(AF_INET, SOCK_DGRAM, 0);
    memcpy(ifret.ifr_name, ifname, strlen(ifname));
    ifret.ifr_name[strlen(ifname)] = 0;
    if (ioctl(s, SIOCGIFHWADDR, &ifret) == -1) {
        printf("bug ioctl\n");
        exit(84);
    }
    memcpy(ret, ifret.ifr_hwaddr.sa_data, ETH_ALEN);
    close(s);
}

struct hdr *build_request(const struct in_addr *src_ip,
    const struct ether_addr *src,
    const struct in_addr *dest_ip,
    const struct ether_addr *dest)
{
    struct hdr *packet = malloc(sizeof(struct hdr));

    packet->ethhdr.ether_type = htons(ETHERTYPE_ARP);
    memcpy(packet->ethhdr.ether_shost, src, ETH_ALEN);
    memcpy(packet->ethhdr.ether_dhost, dest, ETH_ALEN);
    packet->etherarphdr.ea_hdr = (struct arphdr){
        .ar_hrd = htons(ARPHRD_ETHER), .ar_pro = htons(ETHERTYPE_IP),
        .ar_hln = ETH_ALEN, .ar_pln = 4,
        .ar_op = htons(ARPOP_REQUEST),
    };
    memcpy(packet->etherarphdr.arp_spa, src_ip, sizeof(*src_ip));
    memcpy(packet->etherarphdr.arp_tpa, dest_ip, sizeof(*dest_ip));
    memcpy(packet->etherarphdr.arp_sha, src, sizeof(*src));
    memcpy(packet->etherarphdr.arp_tha, &(struct ether_addr)
        {{0xff, 0xff, 0xff, 0xff, 0xff, 0xff}}, sizeof(*dest));
    return (packet);
}

void print_hex(const void *data, size_t n)
{
    for (size_t i = 0 ; i < n ; i++) {
        printf("%02x", ((const unsigned char *)data)[i]);
        if (i != n - 1)
            printf(" ");
    }
    printf("\n");
}