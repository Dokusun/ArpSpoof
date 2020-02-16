/*
** EPITECH PROJECT, 2018
** my_arpspoofing
** File description:
** main source file
*/

#include "arp.h"

struct hdr *receive(void)
{
    bool test;
    int sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    struct hdr *hd;
    uint8_t *ether_frame = calloc(sizeof(uint8_t), 65535);

    if (sock < 0) {
        printf("socket bug %d\n", sock);
        return (NULL);
    }
    do {
        recv(sock, ether_frame, 65535, 0);
        hd = (struct hdr *)ether_frame;
        test = (ntohs(hd->etherarphdr.ea_hdr.ar_op) == ARPOP_REPLY) &&
            (ether_frame[12] << 8) + ether_frame[13] == ETH_P_ARP;
    } while (test == false);
    close(sock);
    return (hd);
}

struct hdr *first_packet(arp_t *info)
{
    struct hdr *test = build_request((const struct in_addr *)&info->srcip,
        (const struct ether_addr *)&info->mac,
        (const struct in_addr *)&info->destip,
        &(const struct ether_addr){{
            0xff, 0xff, 0xff, 0xff, 0xff, 0xff
        }});
    return (test);
}

int main(int ac, char **av)
{
    return (parse_argv(ac, av));
}